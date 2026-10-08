These localhost certificate and key files are public test fixtures, never
production credentials. Chromium integration tests trust this certificate's
SPKI only for their isolated test process; Node tests use it as a private CA.

To renew them, run from the repository root:

```sh
openssl req -x509 -newkey rsa:2048 -nodes \
  -keyout test/spec/fixtures/websocket/localhost.key \
  -out test/spec/fixtures/websocket/localhost.crt -days 3650 \
  -subj /CN=localhost \
  -addext 'subjectAltName=DNS:localhost,IP:127.0.0.1,IP:::1'
```

The Wasm build excludes the certificate, key and standalone echo host. The
shared message type remains available to client test code.
