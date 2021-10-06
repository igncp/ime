const ibus = require("../src");

const { KeyCodes, KeyEventReturn } = ibus.helpers;

const keysToSkip = [
  KeyCodes.ARROW_LEFT,
  KeyCodes.ARROW_RIGHT,
  KeyCodes.ARROW_UP,
  KeyCodes.CONTROL,
  KeyCodes.DEL,
  KeyCodes.LOCK_NUM,
  KeyCodes.PAGE_DOWN,
];

class PreeditTest {
  constructor() {
    ibus.registerHandlers({
      disable: this.disable.bind(this),
      enable: this.enable.bind(this),
      keyEvent: this.keyEvent.bind(this),
    });

    this.preeditText = "";
  }

  async init() {
    const config = {
      busName: "im.custom-ime.CustomIme",
      imeName: "custom-ime",
    };

    await ibus.init(config.imeName, config.busName, () => {
      ibus.main();
    });
  }

  enable() {
    console.log("enable called from JS");
  }

  disable() {
    console.log("disable called from JS");
  }

  _engineUpdatePreeditText() {
    ibus.engineUpdatePreeditText(
      this.preeditText,
      this.preeditText.length,
      true
    );
  }

  keyEvent(keyInfo) {
    if (ibus.helpers.isReleasedKey(keyInfo)) {
      return KeyEventReturn.CustomHandling;
    }

    const { keycode } = keyInfo;
    const key = String.fromCharCode(keyInfo.keyval) || "";
    console.log("preedit.js: keycode", keycode, key, keyInfo.modifiers);

    if (ibus.helpers.isKeyWithCtrl(keyInfo) || keycode === KeyCodes.SHIFT) {
      return KeyEventReturn.NativeHandling;
    }

    if (keycode === KeyCodes.ESC) {
      this.preeditText = "";
      this._engineUpdatePreeditText();

      return KeyEventReturn.CustomHandling;
    }

    if (keycode === KeyCodes.ENTER) {
      if (!this.preeditText) {
        return KeyEventReturn.NativeHandling;
      }

      ibus.engineCommitText(this.preeditText);
      this.preeditText = "";

      return KeyEventReturn.CustomHandling;
    }

    const shouldSkipKey = keysToSkip.includes(keycode);

    if (shouldSkipKey) {
      this.preeditText = "";
      this._engineUpdatePreeditText();
      return KeyEventReturn.NativeHandling;
    }

    if (keycode === KeyCodes.BACKSPACE) {
      if (!this.preeditText) {
        return KeyEventReturn.NativeHandling;
      }

      this.preeditText = this.preeditText.slice(0, this.preeditText.length - 1);
    } else {
      this.preeditText += key;
    }

    this._engineUpdatePreeditText();

    return KeyEventReturn.CustomHandling;
  }
}

const main = async () => {
  const test = new PreeditTest();

  await test.init();
};

main();
