# WebSocket and WebTransport Networking Plan

Status: proposed
Last reviewed: 2026-08-30

## Objective

Extend PDG networking so that:

1. A standalone PDG server can keep its existing TCP/UDP listener and optionally host WebSocket and/or WebTransport listeners at the same time.
2. An Emscripten client uses the existing `NetClient`, `NetConnection`, and message APIs, prefers WebTransport when the browser and server support it, and falls back to WebSocket during initial connection establishment.
3. Existing native clients and servers remain wire-compatible and require no application changes unless an application wants to configure the new transports explicitly.

This is transport work, not a new game protocol. PDG serialization, connection authentication, protocol-version negotiation, reservations, callbacks, and the reliable/unreliable message distinction should remain above the transport layer.

### Emscripten is client-only

Emscripten must never host a PDG server or listen for an incoming network connection. The browser build will expose `NetClient` and client-side `NetConnection` behavior only. It will not expose `NetServer`, embed standalone listener implementations, accept WebSocket upgrades, accept WebTransport sessions, or contain server TLS/private-key handling. All browser integration tests connect outward to a separately running standalone PDG server.

## Current State

- `src/js/netclient.js`, `netserver.js`, and `netconnection.js` are directly coupled to Node's `net`, `dgram`, and `Buffer` APIs.
- The standalone executable embeds those JavaScript sources through `tools/js2c.py` and `src/bindings/node/pdg_natives.h`.
- The Emscripten build defines `PDG_NO_NETWORK`; `src/bindings/javascript/pdg.js` consequently does not expose the JavaScript networking classes in a browser.
- The current reliable protocol is a framed byte stream. A data frame is `A`, a four-byte big-endian length, and a serialized payload. Handshake commands use a one-byte command plus a two-byte length.
- `sendDgram()` sends the serialized payload without the reliable-stream frame and falls back to `send()` when datagrams are unavailable.
- WebTransport is still a working draft and Node does not currently provide a WebTransport server API. Experimental Node QUIC/HTTP/3 support is insufficient by itself, so PDG must isolate its server implementation behind a backend interface.

## Compatibility and Non-goals

- Do not replace or remove native TCP/UDP networking.
- Do not require a Node plugin for Emscripten or any other browser target.
- Do not compile POSIX socket networking into Wasm. Browser networking will be implemented in JavaScript using browser APIs while the C++ Wasm build can continue to use `PDG_NO_NETWORK`.
- Do not expose `NetServer` in Emscripten. Server construction and listening are standalone-only capabilities.
- Do not embed server adapters or hosting dependencies in Emscripten artifacts.
- Do not fall back from WebTransport to WebSocket after a PDG session has connected, authenticated, or begun exchanging application data. Reconnection remains an application decision.
- Do not invent a WebTransport-over-WebSocket emulation protocol. WebSocket is a separate PDG transport and carries the normal PDG reliable framing.
- Do not expose experimental Node `node:quic` APIs directly through the public PDG API.
- Do not manually edit generated bindings or embedded-source headers. Change source inputs and regenerate derived files through the existing generators.

## Proposed Public API

### Server configuration

Keep the current native listener enabled by default. Add optional web listener configuration:

```javascript
const server = new pdg.NetServer({
    serverAddr: "0.0.0.0",
    serverPort: 5000,

    webSocket: true,
    webTransport: true,
    webPort: 5443,
    webPath: "/pdg",

    tls: {
        certFile: "certs/server.crt",
        keyFile: "certs/server.key"
    }
});

server.onError(handleServerError).listen(handleConnection);
await server.ready();
```

Boolean options use the shared `webPort`, `webPath`, and `tls` settings. An object form permits transport-specific overrides:

```javascript
new pdg.NetServer({
    native: true,
    webSocket: { port: 5443, path: "/pdg", secure: true },
    webTransport: { port: 5443, path: "/pdg" },
    tls: { certFile, keyFile }
});
```

WebSocket uses TCP and WebTransport/QUIC uses UDP, so they may use the same numeric web port. A raw PDG TCP listener and a WebSocket listener cannot use the same address and TCP port. Validate this before binding and report a useful configuration error.

Add these observable properties without changing the existing connection callback:

- `server.ready()` resolves when every requested listener is ready and reports their bound addresses. This matters for port `0` in tests.
- `server.listeners` reports native, WebSocket, and WebTransport listener state separately.
- Errors include `transport`, `code`, `host`, and `port` fields.
- Startup is atomic by default: if a requested listener fails, close the listeners started by that call and reject `ready()`. An explicit `allowPartialListen` option may permit partial service.
- `shutdown()` stops every listener and optionally closes connections exactly as it does today.

Preserve the existing `serverPort`, `fixedPort`, `noDatagram`, reservation, and handshake options. Normalize the older `port` spelling as an alias if existing applications depend on it.

### Client configuration

Existing native usage remains valid:

```javascript
client.connect({ host: "game.example.com", port: 5000 }, onConnect, clientKey);
```

For an Emscripten client, the default policy is `auto`:

```javascript
client.connect({
    host: "game.example.com",
    webPort: 5443,
    webPath: "/pdg"
}, onConnect, clientKey);
```

The browser derives these endpoints unless explicit URLs are supplied:

```text
WebTransport: https://game.example.com:5443/pdg
WebSocket:    wss://game.example.com:5443/pdg
```

Support explicit deployment URLs for reverse proxies, CDNs, and separate hosts:

```javascript
client.connect({
    webTransportUrl: "https://wt.example.com/pdg",
    webSocketUrl: "wss://ws.example.com/pdg",
    transportPolicy: "auto"
}, onConnect, clientKey);
```

Transport policies:

- `auto`: in a browser, try WebTransport and then WebSocket; in standalone/native PDG, preserve the current native TCP/UDP default.
- `webtransport-required`: fail rather than downgrade.
- `websocket-only`: skip the WebTransport attempt.
- `native-only`: use existing TCP/UDP and reject this policy in a browser with a clear error.

Add read-only connection metadata:

- `connection.transport`: `"native"`, `"websocket"`, or `"webtransport"`.
- `connection.secure`: whether the selected transport is protected by TLS.
- `connection.hasDgram`: retain its current meaning.
- `connection.localAddr`, `localPort`, `remoteAddr`, and `remotePort`: populate when the platform exposes them; use documented empty/zero values when browsers do not.

For callback compatibility, the third `onMessage` argument should remain `"tcp"` for reliable delivery and `"udp"` for unreliable delivery. Applications that need the actual carrier can inspect `connection.transport`.

Expose capability flags that distinguish the two halves of networking:

- `pdg.hasNetwork`: true when the runtime has any PDG networking capability, retained as the broad compatibility flag.
- `pdg.hasNetworkClient`: true when `NetClient` is available.
- `pdg.hasNetworkServer`: true when `NetServer` and listener hosting are available.

For Emscripten these values are `true`, `true`, and `false`, respectively, and `pdg.NetServer` remains undefined. Standalone PDG reports all three as true. Tests and applications that need to host must check `hasNetworkServer` rather than infer hosting from `hasNetwork`.

## Transport Architecture

### 1. Extract a byte-oriented adapter

Refactor `NetConnection` so that it owns PDG framing, serialization, handshake state, reservations, and callbacks but no longer knows about Node sockets directly. Give it a transport adapter with this conceptual contract:

```javascript
class ConnectionTransport {
    start(handlers) {}             // open, reliableData, datagram, drain, error, close
    write(bytes) {}                // reliable ordered bytes
    writeDatagram(bytes) {}        // boolean/promise indicating acceptance
    close({ force, code, reason }) {}
    getInfo() {}                   // transport name and available endpoint metadata
    get supportsDatagrams() {}
}
```

Standalone server listeners produce connected adapters and pass them through the same `NetConnection._serverInit()` path. `NetClient` selects and creates a client adapter, then passes it through `_clientInit()`. Emscripten includes only the latter path.

Suggested source layout:

```text
src/js/net/
    bytes.js
    connection_transport.js
    native_transport.js
    websocket_client_transport.js
    websocket_server_transport.js
    webtransport_client_transport.js
    webtransport_server_transport.js
    transport_selector.js
```

Keep the three public files at their current module names so existing `require('netclient')`, `require('netserver')`, and `require('netconnection')` calls continue to work.

Keep client and server transport modules in separate files and separate build-source lists. The Emscripten build embeds `bytes.js`, the base client contract, both browser client adapters, the selector, `netclient.js`, and the client portion of `netconnection.js`; it does not embed `netserver.js` or either server adapter.

### 2. Make byte handling runtime-neutral

Move framing operations to helpers based on `Uint8Array` and `DataView`. In Node, accept and return `Buffer` where the public API currently promises a Buffer; in browsers, use `Uint8Array` and `MemBlock` without installing a global Buffer shim.

The helpers must cover:

- concatenating partial reliable reads;
- big-endian 16- and 32-bit values;
- binary-string/MemBlock conversion without UTF-8 corruption;
- preserving all existing serialized message tags;
- maximum frame and incoming-packet limits before allocation.

This refactor should land with the native TCP/UDP tests still passing before adding either web transport.

### 3. Native TCP/UDP adapter

Move the present `net` and `dgram` behavior into `native_transport.js`. This is the compatibility reference implementation. It must preserve:

- TCP framing and handshake behavior;
- UDP setup and `sendDgram()` fallback;
- keepalive, close, timeout, and drain behavior;
- connection reservations and IP/key checks;
- existing error codes and callback ordering.

### 4. WebSocket adapter and host

Emscripten/browser client behavior:

- Construct a browser `WebSocket`, set `binaryType = "arraybuffer"`, and accept only binary data.
- Send each PDG reliable frame as one binary WebSocket message. Continue parsing it as a byte stream so batching or future adapters cannot change semantics.
- Report backpressure using `bufferedAmount` with a bounded high-water mark; do not grow an unbounded JavaScript queue.
- `writeDatagram()` is unsupported, so `sendDgram()` automatically uses the reliable path.
- Negotiate a PDG WebSocket subprotocol such as `pdg-net-v1` and reject unexpected text messages or subprotocols.

Standalone server behavior:

- Add a WebSocket host backed by a maintained implementation that supports upgrade validation, binary frames, TLS, payload limits, ping/pong, close codes, and backpressure.
- Bundle or statically package the selected implementation with standalone releases; do not rely on an undeclared application `node_modules` installation.
- Convert each accepted WebSocket into the common connection adapter and run the normal PDG key/version handshake before invoking the application's connection callback.
- Apply origin allowlists and connection/rate limits before allocating a full `NetConnection`.

The initial dependency candidate is the established `ws` package, bundled into the standalone build. The dependency spike must also compare a small native implementation if bundling `ws` conflicts with the embedded module loader or release packaging.

### 5. WebTransport adapter and host

Emscripten/browser client behavior:

- Feature-detect `globalThis.WebTransport`; do not use user-agent strings.
- Construct a WebTransport session and wait for `ready` with a bounded establishment timeout.
- Open one bidirectional stream for the reliable PDG byte stream and retain it for the lifetime of the connection.
- Use WebTransport session datagrams for `sendDgram()` only after datagram support is confirmed.
- Respect the implementation's maximum datagram size. Oversized or rejected datagrams use the reliable stream, matching current PDG behavior.
- Cancel stream readers/writers and close the session exactly once on failure or shutdown.

Standalone server behavior:

- Accept WebTransport-over-HTTP/3 sessions on the configured path and application protocol.
- Treat the first accepted client bidirectional stream as the connection's reliable PDG stream. Reject or ignore additional streams for protocol version 1 rather than accidentally creating extra PDG connections.
- Map session datagrams to the adapter's datagram callback.
- Enforce per-session stream, datagram, idle-timeout, handshake-timeout, memory, and connection limits.
- Integrate polling and callbacks with the standalone event loop without blocking the PDG frame/timer loop.

Do not base the production implementation directly on Node's experimental QUIC module. Begin with a time-boxed backend spike. A backend qualifies only if it provides an interoperable browser-facing WebTransport-over-HTTP/3 server, streams and datagrams, TLS/certificate rotation, clean shutdown, and supported builds for PDG's macOS, Linux, and Windows targets.

Evaluate at least:

1. `@fails-components/webtransport` plus its native HTTP/3 transport as a fast integration prototype. It currently offers a Node-style server and prebuilt binaries, but its own documentation characterizes parts of the implementation as provisional, so it must pass PDG stress and packaging tests before adoption.
2. A native HTTP/3/WebTransport stack exposed to the embedded JavaScript layer through a narrow PDG-owned bridge. Raw QUIC libraries such as MsQuic are not sufficient by themselves because PDG also needs HTTP/3 extended CONNECT and WebTransport session semantics.
3. Revisit Node's native implementation only when it exposes a supported WebTransport server API, not merely QUIC and HTTP/3 primitives.

Record the selection, pinned version/commit, licenses, transitive native dependencies, binary sizes, supported architectures, CVE/update process, and rejected alternatives in a short architecture decision record before production implementation.

## Automatic WebTransport-to-WebSocket Fallback

Use one explicit state machine in `transport_selector.js`:

```text
idle
  -> trying-webtransport
       -> connected-webtransport
       -> trying-websocket
            -> connected-websocket
            -> failed
```

Rules:

1. If `WebTransport` is absent, start WebSocket immediately.
2. If it exists, try the configured WebTransport endpoint and wait for `ready`, the reliable stream, and the PDG handshake within separate bounded timeouts.
3. Fall back only when WebTransport is unavailable, the endpoint cannot establish a session, or the server explicitly reports that the PDG WebTransport protocol/path is unsupported.
4. Do not fall back after a bad certificate/pin, rejected client key, incompatible PDG protocol version, application rejection, or completed PDG handshake. These are not evidence that WebTransport is unsupported, and treating them as such can create a security downgrade or consume a single-use reservation twice.
5. Browser error reporting may be opaque. Where an error cannot be classified, default `auto` may fall back only before any PDG authentication bytes are accepted; log the original failure with `transport: "webtransport"`. `webtransport-required` never falls back.
6. Tear down the losing attempt before starting WebSocket. A generation token must prevent late WebTransport promises from firing callbacks after fallback.
7. Invoke the application connect callback at most once and the final error callback at most once.
8. Use one overall connection deadline. Give each attempt a documented sub-deadline so an unsupported or UDP-blocked WebTransport endpoint does not make WebSocket connections take many seconds.
9. Cache a failed WebTransport capability result per origin for a short, configurable TTL. Clear it after configuration changes and never persist it as permanent server capability.
10. Never downgrade `https:`/`wss:` configuration to an insecure `ws:` URL. Development `ws://localhost` support must be explicit.

Sequential fallback is the first implementation. Do not race both transports initially: racing can create duplicate authenticated sessions and consume single-use client reservations. A later happy-eyeballs mode would require a server-issued attempt ID and explicit duplicate suppression.

## TLS, Certificates, and Deployment

- Production WebSocket endpoints used by HTTPS pages must use `wss:`. WebTransport uses HTTP/3 over QUIC and requires a secure server endpoint.
- Support normal Web PKI certificates as the production default. The same certificate/key may be configured for WSS and WebTransport even though the listeners use separate protocol stacks.
- Optionally support WebTransport `serverCertificateHashes` for local development and private deployments. This is not a replacement for client authentication, and current WebTransport rules impose special certificate requirements, including a short validity period.
- Keep the private key in server configuration only. The browser receives an optional certificate hash through trusted bootstrap configuration, never from the endpoint it is meant to authenticate.
- Document UDP firewall/NAT requirements for the WebTransport port and TCP requirements for WSS.
- Document reverse-proxy constraints: the proxy must explicitly support WebSocket upgrades; WebTransport requires end-to-end WebTransport/HTTP/3 support and cannot be assumed to pass through an ordinary HTTP reverse proxy.
- Add graceful certificate reload where the chosen server backend supports it; otherwise document restart behavior.
- Default to origin rejection unless the server is configured with allowed origins. An opt-in development wildcard may be allowed with a warning.

## Wire Protocol Decisions

Version the carrier separately from the existing PDG handshake:

- WebSocket subprotocol: `pdg-net-v1`.
- WebTransport application protocol, where browser/backend support permits negotiation: `pdg-net-v1`.
- Endpoint path default: `/pdg`.
- Reliable carrier: existing PDG framed byte stream unchanged.
- Unreliable carrier: existing serialized datagram payload unchanged.

The first implementation uses exactly one reliable stream per connection. This avoids exposing WebTransport multiplexing to game code and keeps behavior consistent with TCP. A future PDG protocol version can add multiple ordered channels without changing the transport adapter contract.

Add explicit limits and validate them before allocation:

- maximum reliable frame size;
- maximum serialized datagram size based on the selected transport;
- maximum pending reliable bytes;
- maximum sessions per IP/origin;
- maximum incomplete handshakes;
- handshake and idle timeouts.

## Implementation Phases

### Phase 0: Backend and interoperability spike

- Build a minimal standalone WebTransport echo host using the leading backend candidate.
- Connect to it from the same browser versions used by the Emscripten lanes.
- Verify a bidirectional stream, datagrams, clean close, TLS validation, certificate rotation, IPv4/IPv6, and repeated start/stop.
- Verify macOS, Linux, and Windows build/package viability.
- Measure dependency size and confirm license compatibility.
- Write the backend decision record. Do not begin broad API changes until there is a viable server backend.

Exit criterion: a browser-to-standalone echo test passes reliably on all supported desktop server platforms.

### Phase 1: Transport-neutral `NetConnection`

- Introduce byte helpers and the connection adapter contract.
- Move Node TCP/UDP behavior into the native adapter.
- Refactor `NetClient`, `NetServer`, and `NetConnection` around adapters without changing public behavior.
- Add fake-adapter unit tests for partial frames, combined frames, errors, close races, backpressure, handshake timeouts, and datagram fallback.
- Run the complete existing native client suite and lanes.

Exit criterion: no observable native networking regression and no web code yet required at runtime.

### Phase 2: WebSocket end to end

- Add separate Emscripten client and standalone server WebSocket adapters.
- Add server options, listener lifecycle, TLS, subprotocol/origin validation, and packaging.
- Load and expose only `NetClient` and the client-side `NetConnection` API in `src/bindings/javascript/pdg.js` for browser builds. `pdg.NetServer` must remain undefined.
- Embed only client networking modules through `tools/pdg-js.mak`; add an artifact-content test that fails if `netserver` or a server adapter enters the Wasm bundle.
- Leave native Wasm networking disabled; set `pdg.hasNetwork` and `pdg.hasNetworkClient` from availability of browser client transports, and set `pdg.hasNetworkServer = false` independently of the C++ `PDG_NO_NETWORK` define.
- Run the Emscripten networking integration suite against a standalone WSS server.

Exit criterion: Emscripten `NetClient` connects, authenticates, sends every supported message type, receives broadcasts, handles close/error, and reliably falls back for `sendDgram()` over WebSocket.

### Phase 3: WebTransport end to end

- Integrate the selected standalone WebTransport backend behind the listener adapter.
- Add the Emscripten client WebTransport adapter with a reliable stream and session datagrams. Do not add a browser listener or server path.
- Add server/client transport metadata and limits.
- Verify native TCP, native UDP, WSS, WebTransport reliable, and WebTransport datagram clients can coexist on one server process.

Exit criterion: WebTransport passes the same semantic tests as native networking, including unreliable delivery capability where supported.

### Phase 4: Automatic selection and fallback

- Implement the selector state machine, deadlines, cleanup generation, error aggregation, and short capability cache.
- Test absent browser API, UDP blocked, server without WebTransport, wrong WebTransport path, WSS unavailable, handshake rejection, certificate failure, and late promise completion.
- Verify that authentication and protocol failures do not silently downgrade.

Exit criterion: `transportPolicy: "auto"` deterministically selects WebTransport when viable and otherwise establishes exactly one WebSocket connection.

### Phase 5: Hardening, documentation, and lanes

- Add load, reconnect, leak, malformed-frame, oversized-frame, slow-client, and denial-of-service tests.
- Test browser backgrounding, network transitions, server shutdown, and stalled readers/writers.
- Add configuration/API documentation and runnable secure server/client examples.
- Add lane metadata for the selected transport and fallback result.
- Package all server dependencies and license notices in release artifacts.

Exit criterion: all native and Emscripten suites pass, release packages work without undeclared dependencies, and lanes retain artifacts sufficient to diagnose transport selection and failure.

## Test Plan

### Unit tests

- Byte conversion and framing at zero, boundary, maximum, and rejected sizes.
- Every current serialization tag over a fake reliable adapter and fake datagram adapter.
- Fragmented/coalesced reliable input.
- Handshake and client-key behavior independent of carrier.
- State-machine callback exactly-once guarantees.
- WebSocket text-frame rejection and binary-frame acceptance.
- WebTransport extra-stream behavior and datagram-size fallback.
- Listener partial-start rollback and idempotent shutdown.

### Integration matrix

| Client | Server listener | Reliable | Datagram | Expected result |
| --- | --- | ---: | ---: | --- |
| Standalone | Native TCP/UDP | Yes | Yes | Existing behavior |
| Standalone | Native TCP only | Yes | Falls back | Existing behavior |
| Emscripten | WSS | Yes | Reliable fallback | Pass |
| Emscripten with WebTransport | WebTransport | Yes | Yes when negotiated | Preferred |
| Emscripten without WebTransport API | WSS | Yes | Reliable fallback | Immediate fallback |
| Emscripten with UDP blocked | WSS fallback | Yes | Reliable fallback | Bounded fallback |
| Emscripten | Both web listeners | Yes | Yes | WebTransport selected |
| Emscripten, required policy | WSS only | No | No | Clear WebTransport error |

Run message tests for strings, JSON objects, `MemBlock`, byte arrays/Buffers as applicable, registered `ISerializable` objects, maximum legal frames, broadcasts, close/error callbacks, reservations, and protocol-version negotiation.

### Browser automation

- Extend `test/client` so the native harness starts a standalone secure test host and allocates ports. The Emscripten runner only receives the resulting client endpoint/certificate hash and drives outbound connections; it never starts or implements a server in the browser.
- Keep transport integration specs separate from pure unit specs so browser lanes can report whether a failure is build, browser initialization, TLS, listener startup, selection, handshake, reliable data, or datagrams.
- Test at least the supported Chromium lane plus every browser lane where `WebTransport` is available. Browsers without WebTransport must still pass the WebSocket fallback suite.
- Record browser name/version, `typeof WebTransport`, requested policy, attempted transports, chosen transport, attempt durations, endpoint, secure mode, datagram availability, and final error code in lane JSON.
- Add an Emscripten API test asserting `pdg.hasNetworkClient === true`, `pdg.hasNetworkServer === false`, and `pdg.NetServer === undefined`.

### Stress and security tests

- Thousands of connect/close cycles without growing handles or Wasm/JS/native memory.
- Slow readers, large `bufferedAmount`, flow-control stalls, and server backpressure.
- Malformed lengths, oversized frames, unexpected text, extra WebTransport streams, invalid commands, and incomplete handshakes.
- Invalid origin, certificate, path, subprotocol, reservation key, and protocol version.
- Simulated UDP loss/blocking and TCP availability to prove bounded fallback.
- Shutdown during each connection state and repeated listener start/stop.

## Expected Source and Build Changes

Likely source areas:

- `src/js/netclient.js`
- `src/js/netserver.js`
- `src/js/netconnection.js`
- new transport modules under `src/js/net/`
- `src/bindings/javascript/pdg.js`
- client-only Emscripten module embedding in `tools/pdg-js.mak`
- standalone embedded-JavaScript source lists in `src/CMakeLists.txt`
- a narrow native server bridge and build dependency only if required by the selected WebTransport backend
- `test/spec/net*.spec.js` plus new transport-focused unit and browser integration specs
- `test/emscripten/` runners and `test/lanes.json`
- release packaging scripts and third-party license manifests

Regenerate `src/bindings/node/pdg_natives.h` from the changed JavaScript sources. If a native bridge adds public binding methods, edit the binding sources/generator inputs and regenerate outputs; do not patch `src/bindings/generated/` by hand.

## Risks and Mitigations

- **WebTransport server maturity:** gate the implementation on Phase 0 and hide the backend behind a PDG-owned interface.
- **Protocol/API churn:** pin the backend and carrier version; test real browsers in lanes; avoid exposing backend-specific types publicly.
- **Fallback latency:** use bounded attempt deadlines and a short negative capability cache.
- **Security downgrade:** provide required/only policies and prohibit fallback after authentication or protocol rejection.
- **Duplicate sessions:** use sequential attempts and exactly-once state transitions.
- **Binary-data incompatibility:** make byte conversion a separately tested foundation before web transports.
- **Backpressure and memory growth:** enforce queue/frame/session limits and test stalled peers.
- **Certificate friction in development:** provide a certificate-generation helper and optional certificate-hash configuration, with production Web PKI documented as the default.
- **Release size/cross-platform native builds:** measure in Phase 0 and package deterministic binaries/sources with license notices.

## Definition of Done

- A standalone server can enable native, WebSocket, and WebTransport listeners independently or together.
- Requested listener startup and shutdown are deterministic and observable.
- Existing native networking applications and tests continue to pass unchanged.
- The Emscripten build exposes `NetClient` and client-side `NetConnection` without POSIX sockets in Wasm.
- The Emscripten build does not expose `NetServer`, contain listener code, or host incoming connections under any configuration.
- Browser clients prefer WebTransport and use its datagrams where available.
- Unsupported/unreachable WebTransport falls back to secure WebSocket within a bounded time and creates only one accepted PDG connection.
- Authentication, certificate, and PDG protocol failures do not silently downgrade.
- All supported message types, connection callbacks, reservations, broadcasts, size limits, and close/error paths pass over each carrier.
- Browser lanes report attempted/chosen transport and datagram capability.
- Standalone release artifacts contain all runtime dependencies and required license notices.

## References

- [W3C WebTransport Working Draft](https://www.w3.org/TR/webtransport/)
- [Node.js experimental QUIC option](https://github.com/nodejs/node/blob/main/doc/api/cli.md#--experimental-quic)
- [Node.js QUIC implementation status](https://github.com/nodejs/nodejs.org/blob/main/apps/site/pages/en/blog/events/nodejs-interactive-2026.md#quic-and-http3-are-taking-shape-in-nodejs)
- [`@fails-components/webtransport`](https://github.com/fails-components/webtransport)
- [MsQuic FAQ: QUIC does not include an HTTP/3 implementation](https://github.com/microsoft/msquic/blob/main/docs/FAQ.md#why-isnt-there-an-http3-implementation-along-with-msquic)
