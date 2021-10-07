const ibus = require("../src");

const { KeyCodes, KeyEventReturn } = ibus.helpers;

const keysToSkip = [
  KeyCodes.ALT_TAB,
  KeyCodes.ARROW_LEFT,
  KeyCodes.ARROW_RIGHT,
  KeyCodes.ARROW_UP,
  KeyCodes.CONTROL,
  KeyCodes.DEL,
  KeyCodes.LOCK_NUM,
  KeyCodes.PAGE_DOWN,
  KeyCodes.SHIFT_RIGHT,
  KeyCodes.TAB,
];

class AuxiliaryTest {
  constructor() {
    ibus.registerHandlers({
      disable: this._disable.bind(this),
      enable: this._enable.bind(this),
      keyEvent: this._keyEvent.bind(this),
    });

    this.auxiliaryText = "";
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

  _enable() {
    const engineName = ibus.engineGetName();
    console.log("enable called from JS: ", engineName);
  }

  _disable() {
    console.log("disable called from JS");
  }

  _engineUpdateAuxiliaryText(isVisible) {
    ibus.engineUpdateAuxiliaryText(this.auxiliaryText, isVisible);
  }

  _keyEvent(keyInfo) {
    if (ibus.helpers.isReleasedKey(keyInfo)) {
      return KeyEventReturn.CustomHandling;
    }

    const { keycode } = keyInfo;
    const key = String.fromCharCode(keyInfo.keyval) || "";

    if (ibus.helpers.isKeyWithCtrl(keyInfo) || keycode === KeyCodes.SHIFT) {
      return KeyEventReturn.NativeHandling;
    }

    if (keycode === KeyCodes.ESC) {
      this.auxiliaryText = "";
      this._engineUpdateAuxiliaryText(false);

      return KeyEventReturn.CustomHandling;
    }

    if (keycode === KeyCodes.ENTER) {
      if (!this.auxiliaryText) {
        return KeyEventReturn.NativeHandling;
      }

      ibus.engineCommitText(this.auxiliaryText);
      this.auxiliaryText = "";
      this._engineUpdateAuxiliaryText(false);

      return KeyEventReturn.CustomHandling;
    }

    const shouldSkipKey = keysToSkip.includes(keycode);

    if (shouldSkipKey) {
      this.auxiliaryText = "";
      this._engineUpdateAuxiliaryText(false);
      return KeyEventReturn.NativeHandling;
    }

    if (keycode === KeyCodes.BACKSPACE) {
      if (!this.auxiliaryText) {
        return KeyEventReturn.NativeHandling;
      }

      this.auxiliaryText = this.auxiliaryText.slice(
        0,
        this.auxiliaryText.length - 1
      );
    } else {
      this.auxiliaryText += key;
    }

    this._engineUpdateAuxiliaryText(true);

    return KeyEventReturn.CustomHandling;
  }
}

const main = async () => {
  const test = new AuxiliaryTest();

  await test.init();
};

main();
