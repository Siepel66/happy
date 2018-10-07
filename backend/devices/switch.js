var myLog = require('../support/mylog.js');

class Switch {
  constructor(name, state) {
    this.name = name;
    this.state = state;
  }

  on () {
    myLog("Switch", this.name, "Set on");
    this.state = 1;
  }

  off () {
    myLog("Switch", this.name, "Set off");
    this.state = 0;
  }

  getState() {
    return this.state;
  }
}

module.exports = Switch;
