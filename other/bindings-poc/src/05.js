// https://nodejs.github.io/node-addon-examples/getting-started/objectwrap

const assert = require("assert");

const addon = require("../build/Release/module_05");

const { ObjectWrapDemo } = addon;

function testBasic() {
  const instance = new ObjectWrapDemo("mr-yeoman");
  assert(instance.greet, "The expected method is not defined");
  assert.strictEqual(
    instance.greet("kermit"),
    "mr-yeoman",
    "Unexpected value returned"
  );
}

function testInvalidParams() {
  new ObjectWrapDemo();
}

assert.doesNotThrow(testBasic, undefined, "testBasic threw an expection");
assert.throws(testInvalidParams, undefined, "testInvalidParams didn't throw");

console.log("Tests passed- everything looks OK!");
