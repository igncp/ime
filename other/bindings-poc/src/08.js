const assert = require("assert");
const addon = require("../build/Release/module_08");

const obj = addon.getObj();

assert.deepStrictEqual(obj.propertyA, 123, "Unexpected object received");
assert.deepStrictEqual(obj.propertyB, obj, "Unexpected object received");
