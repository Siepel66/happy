var util = require('util');

function myLog(fname, name, message) {
  util.log(("                    " + fname).slice(-15) + " [" + name + "]:\t" + message);
}

module.exports = myLog;
