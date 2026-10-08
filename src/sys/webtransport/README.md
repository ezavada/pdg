# Native WebTransport backend

PDG uses C picoquic/picohttp for QUIC and HTTP/3 WebTransport, C Picotls/Mbed TLS,
and a C++17 owned-buffer bridge. No Rust runtime is required. CMakeLists.txt pins
all dependency commits, including upstream Picotls submodules. Network access
and CMake are required for the first build unless source overrides are supplied.
Nothing is downloaded at application runtime.

The standalone desktop CMake build uses an isolated dependency build and links
one static archive. The Node package builds the same archive before node-gyp,
outside its cleanup directory. Xcode builds SDK/architecture/configuration
specific archives through tools/build-webtransport-ios.sh. Browser builds use
the browser WebTransport API and contain neither this backend nor listener or
private-key modules. iOS exposes clients only.

The native C ABI accepts owned JSON requests and returns owned JSON results.
JavaScript polls bounded event queues on its own thread. One transport worker
serializes QUIC/TLS operations; a separate resolver prevents DNS lookups from
stalling live sessions. Establishment deadlines include DNS time. Each handle
bounds incoming and outgoing bytes and queued events/writes. Reliable output
remains budgeted until acknowledged. Graceful close drains queued output with a
bounded deadline; cancellation and remote close are idempotent. App backgrounding
closes iOS sessions and reports ERR_NETWORK_BACKGROUND after foreground dispatch.

TLS uses platform trust on Apple/Windows or a system CA bundle on Linux; explicit
native caFile uses Mbed TLS chain and hostname validation. Platform trust checks
use supplied/cached chains without fetching missing intermediates on the QUIC
worker. Server certificates should include their intermediate chain. Optional
certificate hashes require current EC certificates with at most 14 days validity;
TLS CertificateVerify still proves ownership of the pinned certificate key.

A client opens one bidirectional reliable stream. Both peers send a WebTransport
only D(0/1) capability command before their V version command so noDatagram on
either peer disables session datagram use. Native TCP and WebSocket K/V/A framing
is unchanged. Datagram payloads are conservatively capped at 1100 bytes and use
reliable fallback when larger or rejected. Unreliable delivery retains the
legacy udp callback label; reliable delivery retains tcp.

Picoquic, Picotls and cJSON use MIT licenses; micro-ecc uses BSD-2-Clause and
Cifra uses CC0. Mbed TLS is used under its Apache-2.0 option. Complete dependency
notices are in THIRD_PARTY_NOTICES.txt and accompany desktop, iOS and npm builds.
The build recipe corrects a certificate-chain allocation leak in a build copy
of the pinned picoquic verifier. Downloaded upstream sources remain unchanged;
changing the pin requires reviewing that patch and updating the notices.

Build and test the backend directly from the repository root:

```sh
cmake -S src/sys/webtransport -B build/webtransport/native -DPDG_WEBTRANSPORT_TEST_DRIVER=ON
cmake --build build/webtransport/native -j8
./tools/node test/lib/webtransport_native.integration.js
./test/tools webtransport
./test/unit net_webtransport
./test/unit --node net_webtransport
./test/ios net_webtransport --iphone
./test/unit --web --automated net_webtransport
```

For offline Xcode/npm builds set PDG_WEBTRANSPORT_SOURCES to a directory containing
picoquic, picotls, mbedtls and cjson source trees at the pinned revisions. CMake
consumers can use FETCHCONTENT_SOURCE_DIR_PICOQUIC/PICOTLS/MBEDTLS/CJSON.
Source trees may be shared; build directories must remain platform specific.
Linux ARM64 is verified in the PDG Ubuntu 24.04.4 Docker environment with GCC
13.3, CMake 3.28.3 and Node 24.21. The native backend and standalone headless
runtime build, the npm package builds and installs, native protocol integration
passes, and standalone/Node networking each pass 50 tests and 237 assertions.
The WebTransport and network transport tooling suites also pass. Logs are under
artifacts/test-results/linux-docker/node-24.21/webtransport-*.log.
Windows execution and Linux x86_64 execution remain unvalidated.
