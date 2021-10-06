const ibus = require("../src");

const { KeyCodes } = ibus.helpers;

const disableHandler = () => {
  console.log("disable called from JS");
};

const enableHandler = () => {
  console.log("enable called from JS");
  ibus.lookupTableSetOrientation();
  ibus.lookupTableSetPageSize(3);
  ibus.lookupTableSetRound();
};

const keyEventHandler = (keyInfo) => {
  const key = String.fromCharCode(keyInfo.keyval) || "";

  const isReleasedKey = ibus.helpers.isReleasedKey(keyInfo);

  if (!isReleasedKey) {
    const { keycode } = keyInfo;

    if (keycode === KeyCodes.UP) {
      ibus.lookupTableCursorUp();
      ibus.engineUpdateLookupTable(true);
      return;
    } else if (keycode === KeyCodes.DOWN) {
      ibus.lookupTableCursorDown();
      ibus.engineUpdateLookupTable(true);
      return;
    } else if (keycode === KeyCodes.PAGE_UP) {
      ibus.lookupTablePageUp();
      ibus.engineUpdateLookupTable(true);
      return;
    } else if (keycode === KeyCodes.PAGE_DOWN) {
      ibus.lookupTablePageDown();
      ibus.engineUpdateLookupTable(true);
      return;
    }

    const candidatesNum = ibus.lookupTableGetNumberOfCandidates();

    if (key === "l") {
      ibus.lookupTableAppendCandidate("Sample " + ((candidatesNum || 0) + 1));
    } else if (key === "p") {
      ibus.engineHideLookupTable();
      ibus.lookupTableClear();
    } else if (key === "o") {
      ibus.engineUpdatePreeditText("Foo");
      return;
    } else if (key === "i" && candidatesNum > 0) {
      const cursorPos = ibus.lookupTableGetCursorPos();
      const pageSize = ibus.lookupTableGetPageSize();
      const index = cursorPos % pageSize;

      console.log("main.js: index", index, pageSize, cursorPos);

      ibus.lookupTableSetLabel(index, "ABC");
      ibus.engineUpdateLookupTable(true);

      return;
    }

    if (key !== "p" && key !== "i") {
      if (candidatesNum > 0) {
        ibus.lookupTableSetCursorPos(candidatesNum - 1);
      }
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
