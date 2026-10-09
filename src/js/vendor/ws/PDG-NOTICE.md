PDG bundles ws 8.22.0 from https://registry.npmjs.org/ws/-/ws-8.22.0.tgz
Archive SHA-256: ca9b3798b2e11ce8fac6713f50ef0501aa12b09b330623c1dc409dff94e7abc8.
(upstream https://github.com/websockets/ws, tag 8.22.0).

License: MIT; see LICENSE. Upstream package files are unmodified. Regenerate
`src/js/net_ws_bundle.js` with `node tools/bundle-websocket.js`; verify with
`node tools/bundle-websocket.js --check`. The bundle uses Node core modules and
excludes the optional bufferutil and utf-8-validate native accelerators. It
needs no application node_modules installation or native addon. Compression
is disabled by the PDG server. Browser builds do not contain this dependency.

A custom RFC 6455 host was rejected because it would duplicate masking,
fragmentation, UTF-8 validation, upgrade, TLS and close handling. The generated
bundle solves PDG's embedded loader constraints without changing upstream.

To update: review upstream security advisories and release notes, replace this
package with a pinned upstream release, regenerate, and run
`test/tools network-transport`, `test/unit net_websocket netclient netserver
netconnection`, and `test/unit --web --automated net_websocket`. Preserve LICENSE
and update the generator version and release notices. No native transitive
dependencies; Node core supplies crypto, TLS and streams. macOS validation is
recorded with this implementation; Windows/Linux use the same JavaScript bundle.
