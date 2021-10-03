const addon = require("../build/Release/module_03");

addon.registerGlobalFn(() => {
  console.log("Inside cb");
});

console.log("Before callRegisteredGlobalFn");

addon.callRegisteredGlobalFn();

console.log("After callRegisteredGlobalFn");
