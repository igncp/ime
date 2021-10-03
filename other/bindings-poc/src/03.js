const addon = require("../build/Release/module_03");

// This poc is not working because it is not possible to save a reference to a
// function in this way

const obj = {
  fn: () => {
    console.log("Inside obj.fn");
  },
};

const main = () => {
  addon.registerGlobalFn(obj);

  addon.callRegisteredGlobalFn();
};

main();
