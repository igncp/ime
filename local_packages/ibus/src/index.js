const addon = require("../build/Release/module");

// https://ibus.github.io/docs/ibus-1.4/ibus-ibustypes.html#IBusModifierType-enum
const IBusModifierType = {
  IBUS_RELEASE_MASK: 1 << 30,
};

const engineCommitText = (text) => {
  addon.engineCommitText(text);
};

const init = (imeName, busName, cb) => {
  return new Promise((resolve, reject) => {
    try {
      const result = addon.init(imeName, busName, cb);

      resolve(result);
    } catch (error) {
      reject(error);
    }
  });
};

const main = () => {
  addon.main();
};

const registerHandlers = (handlers) => {
  if (!handlers) {
    throw new Error("Missing handlers");
  }

  if (typeof handlers.keyEvent !== "function") {
    throw new Error("Incorrect keyEvent handler");
  }

  addon.registerHandlers(handlers);
};

const isReleasedKey = (keyInfo) => {
  return keyInfo.modifiers & IBusModifierType.IBUS_RELEASE_MASK;
};

const helpers = {
  isReleasedKey,
};

module.exports = {
  engineCommitText,
  helpers,
  init,
  main,
  registerHandlers,
};
