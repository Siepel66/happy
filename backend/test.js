var myLog = require('./support/mylog.js');
var Switch = require('./devices/switch.js');
var WgetSwitch = require('./devices/wgetswitch.js');


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
