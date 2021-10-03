const addon = require("../build/Release/module_02");

addon.functionWithCallback((result) => {
  console.log("functionWithCallback", result);
});
