const assert = require("assert");

const addon = require("../build/Release/module_06");

const { pow } = addon;

const testBasic = () => {
  assert.strictEqual(pow(1, 2), 1, "Unexpected value returned");
  assert.strictEqual(pow(2, 2), 4, "Unexpected value returned");
  assert.strictEqual(pow(3, 2), 9, "Unexpected value returned");
};

const testInvalidParams = () => {
  pow(2);
};

assert.doesNotThrow(testBasic, undefined, "testBasic threw an expection");
assert.throws(testInvalidParams, undefined, "testInvalidParams didn't throw");

console.log("Tests passed- everything looks OK!");
