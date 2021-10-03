const ibus = require("ibus");

const main = async () => {
  ibus.registerHandlers({
    keyEvent: (keyInfo) => {
      console.log("Inside key event", keyInfo);
      console.log(
        "parsed keyInfo.keycode",
        String.fromCharCode(keyInfo.keycode)
      );
      console.log("parsed keyInfo.keyval", String.fromCharCode(keyInfo.keyval)); // this is the correct one
      console.log("");
    },
  });

  // these match the ones in the XML file
  await ibus.init("custom-ime", "im.custom-ime.CustomIme", () => {
    ibus.main();
  });
};

main();
