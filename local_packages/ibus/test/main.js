const ibus = require("../src");

const disableHandler = () => {
  console.log("disable called from JS");
};

const enableHandler = () => {
  console.log("enable called from JS");
  ibus.lookupTableSetOrientation();
};

const keyEventHandler = (keyInfo) => {
  const key = String.fromCharCode(keyInfo.keyval) || "";

  const isReleasedKey = ibus.helpers.isReleasedKey(keyInfo);

  if (!isReleasedKey) {
    console.log("main.js: key", key);
    if (key === "l") {
      ibus.lookupTableAppendCandidate("Sample");
    } else if (key === "p") {
      ibus.engineHideLookupTable();
      ibus.lookupTableClear();
    } else if (key === "o") {
      ibus.engineUpdatePreeditText("Foo");
      return;
    }

    if (key !== "p") {
      ibus.engineUpdateLookupTable(true);
    }

    ibus.engineCommitText(key.toUpperCase());
  }
};

// from the XML file
const config = {
  busName: "im.custom-ime.CustomIme",
  imeName: "custom-ime",
};

const main = async () => {
  ibus.registerHandlers({
    disable: disableHandler,
    enable: enableHandler,
    keyEvent: keyEventHandler,
  });

  await ibus.init(config.imeName, config.busName, () => {
    ibus.main();
  });
};

main();
