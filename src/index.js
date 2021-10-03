const libnotify = require("libnotify");
const ibus = require("ibus");

const keyEventHandler = (keyInfo) => {
  const key = String.fromCharCode(keyInfo.keyval) || "";

  const isReleasedKey = ibus.helpers.isReleasedKey(keyInfo);

  if (!isReleasedKey) {
    ibus.engineCommitText(key.toUpperCase());
  }
};

// from the XML file
const config = {
  imeName: "custom-ime",
  busName: "im.custom-ime.CustomIme",
};

const main = async () => {
  libnotify.send("Starting Custom IME");

  ibus.registerHandlers({
    keyEvent: keyEventHandler,
  });

  await ibus.init(config.imeName, config.busName, () => {
    ibus.main();
  });
};

main();
