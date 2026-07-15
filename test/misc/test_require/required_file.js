const required_from_required_file = require('./required_from_required_file.js');

function test_required_file() {
    console.log('Called test_required_file()');
    required_from_required_file();
}

module.exports = test_required_file;