// Shared asynchronous acceptance must finish before its fixtures are released.
describe('Async runner lifecycle', function() {
    var ready = false, completed = 0, cleaned = 0;
    beforeEach(function(done) {
        setTimeout(function() { ready = true; done(); }, 15);
    });
    afterEach(function(done) {
        setTimeout(function() { ready = false; ++cleaned; done(); }, 15);
    });
    it('waits for setup and callback assertions', function(done) {
        expect(ready).toBe(true);
        setTimeout(function() {
            expect(ready).toBe(true);
            ++completed;
            done();
        }, 25);
    });
    it('waits for the previous test and teardown before the next setup', function(done) {
        expect(ready).toBe(true);
        expect(completed).toBe(1);
        expect(cleaned).toBe(1);
        setTimeout(function() { expect(ready).toBe(true); done(); }, 15);
    });
});
