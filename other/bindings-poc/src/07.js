const addon = require("../build/Release/module_07");

console.log("Before wrapObj");

const obj = addon.wrapObj();
console.log("07.js: obj", obj);
console.log("After wrapObj");

console.log("Before unwrapObj");
addon.unwrapObj(obj);
addon.unwrapObj(obj);
addon.unwrapObj(obj);
console.log("After unwrapObj");
