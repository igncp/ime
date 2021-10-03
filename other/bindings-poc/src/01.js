const addon = require("../build/Release/module_01");

const value = 10;
console.log(`${value} times 2 equals`, addon.myFunction(value));
