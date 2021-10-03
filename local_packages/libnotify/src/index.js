const addon = require("../build/Release/module");

const send = (message) => {
  if (!message || typeof message !== "string") {
    throw new Error("Invalid argument");
  }

  addon.send(message);
};

module.exports = {
  send,
};
