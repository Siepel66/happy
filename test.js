var wget = require('node-wget');
var myLog = require('./mylog.js');
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

sw = new WgetSwitch("Totem", 0, "http://192.168.2.150", 80, 12);
sw2 = new Switch("Virtual", 0);

sw.on();
myLog("main", "main", "State: " + sw.getState());
sw.off();
myLog("main", "main", "State: " + sw.getState());

sw2.on();
myLog("main", "main", "State: " + sw2.getState());
sw2.off();
myLog("main", "main", "State: " + sw2.getState());
