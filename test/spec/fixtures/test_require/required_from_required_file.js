function test_required_from_required_file() {
    console.log('Called test_required_from_required_file()');
    return require('pdg');
}

module.exports = test_required_from_required_file;
