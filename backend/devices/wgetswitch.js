var wget = require('node-wget');
var myLog = require('../support/mylog.js');
var Switch = require('./switch.js')

class WgetSwitch extends Switch {
  constructor(name, state, server, port, io) {
    super(name, state);
    this.server = server;
    this.port = port;
    this.io = io;
  }

  sendToSwitch(state) {
    myLog("WgetSwitch", this.name, "Send state " + state + " to server");
    wget(this.server + ":" + this.port + "/control?cmd=GPIO," + this.io + "," + state);
  }

  on() {
    super.on();
    this.sendToSwitch(this.state);
  }

  off() {
    super.off();
    this.sendToSwitch(this.state);
  }
}

module.exports = WgetSwitch;
