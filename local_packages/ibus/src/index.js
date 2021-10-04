const addon = require("../build/Release/module");

const runWithCatch = (fn) => {
  try {
    const result = fn();
    return result;
  } catch (e) {
    console.log("index.js: error", e);
  }
};

// https://ibus.github.io/docs/ibus-1.4/ibus-ibustypes.html#IBusModifierType-enum
const IBusModifierType = {
  IBUS_RELEASE_MASK: 1 << 30,
};

const engineCommitText = (text) => {
  runWithCatch(() => {
    addon.engineCommitText(text);
  });
};

const engineHideLookupTable = () => {
  runWithCatch(() => {
    addon.engineHideLookupTable();
  });
};

const engineShowAuxiliaryText = () => {
  runWithCatch(() => {
    addon.engineShowAuxiliaryText();
  });
};

const engineShowLookupTable = () => {
  runWithCatch(() => {
    addon.engineShowLookupTable();
  });
};

const engineUpdateAuxiliaryText = (text) => {
  runWithCatch(() => {
    addon.engineUpdateAuxiliaryText(text);
  });
};

const engineUpdateLookupTable = (isVisible) => {
  if (typeof isVisible !== "boolean") {
    throw new Error("Incorrect param isVisible for engineUpdateLookupTable");
  }

  runWithCatch(() => {
    addon.engineUpdateLookupTable(isVisible);
  });
};

const engineUpdatePreeditText = (text) => {
  runWithCatch(() => {
    addon.engineUpdatePreeditText(text);
  });
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

  const handlerNames = ["keyEvent", "enable", "disable"];

  handlerNames.forEach((handlerName) => {
    if (typeof handlers[handlerName] !== "function") {
      throw new Error("Incorrect handler " + handlerName);
    }
  });

  const wrappedHandlers = handlerNames.reduce((handlersObj, handlerName) => {
    handlersObj[handlerName] = (...args) => {
      return runWithCatch(() => handlers[handlerName](...args));
    };
    return handlersObj;
  }, {});

  addon.registerHandlers(wrappedHandlers);
};

const isReleasedKey = (keyInfo) => {
  return keyInfo.modifiers & IBusModifierType.IBUS_RELEASE_MASK;
};

const lookupTableAppendCandidate = (text) => {
  runWithCatch(() => {
    addon.lookupTableAppendCandidate(text);
  });
};

const lookupTableClear = () => {
  runWithCatch(() => {
    addon.lookupTableClear();
  });
};

const lookupTableSetOrientation = () => {
  runWithCatch(() => {
    addon.lookupTableSetOrientation();
  });
};

const helpers = {
  isReleasedKey,
};

module.exports = {
  engineCommitText,
  engineHideLookupTable,
  engineShowAuxiliaryText,
  engineShowLookupTable,
  engineUpdateAuxiliaryText,
  engineUpdateLookupTable,
  engineUpdatePreeditText,
  helpers,
  init,
  lookupTableAppendCandidate,
  lookupTableClear,
  lookupTableSetOrientation,
  main,
  registerHandlers,
};
