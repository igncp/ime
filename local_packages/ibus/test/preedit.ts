import * as ibus from "../src"

const { KeyCodes, KeyEventReturn } = ibus

const keysToSkip = [
  KeyCodes.ARROW_LEFT,
  KeyCodes.ARROW_RIGHT,
  KeyCodes.ARROW_UP,
  KeyCodes.CONTROL,
  KeyCodes.DEL,
  KeyCodes.LOCK_NUM,
  KeyCodes.PAGE_DOWN,
  KeyCodes.TAB,
]

class PreeditTest {
  private preeditText: string

  public constructor() {
    ibus.registerHandlers({
      disable: PreeditTest._disable,
      enable: PreeditTest._enable,
      focusIn: () => {},
      focusOut: () => {},
      keyEvent: this._keyEvent.bind(this),
      propertyActivate: () => {},
    })

    this.preeditText = ""
  }

  public static init() {
    const config = {
      busName: "im.custom-ime.CustomIme",
      imeName: "custom-ime",
    }

    ibus.init({
      busName: config.busName,
      cb: () => {
        ibus.main()
      },
      imeName: config.imeName,
    })
  }

  private static _enable() {
    const engineName = ibus.engineGetName()

    console.log("enable called from JS", engineName)
  }

  private static _disable() {
    console.log("disable called from JS")
  }

  private _engineUpdatePreeditText() {
    ibus.engineUpdatePreeditText({
      cursorPos: this.preeditText.length,
      isVisible: true,
      text: this.preeditText,
    })
  }

  private _keyEvent(keyInfo: ibus.KeyInfo) {
    if (ibus.helpers.isReleasedKey(keyInfo)) {
      return KeyEventReturn.CustomHandling
    }

    const { keycode } = keyInfo
    const key = String.fromCharCode(keyInfo.keyval) || ""

    console.log("preedit.js: keycode", keycode, key, keyInfo.modifiers)

    if (ibus.helpers.isKeyWithCtrl(keyInfo) || keycode === KeyCodes.SHIFT) {
      return KeyEventReturn.NativeHandling
    }

    if (keycode === KeyCodes.ESC) {
      this.preeditText = ""
      this._engineUpdatePreeditText()

      return KeyEventReturn.CustomHandling
    }

    if (keycode === KeyCodes.ENTER) {
      if (!this.preeditText) {
        return KeyEventReturn.NativeHandling
      }

      ibus.engineCommitText(this.preeditText)
      this.preeditText = ""

      return KeyEventReturn.CustomHandling
    }

    const shouldSkipKey = keysToSkip.includes(keycode)

    if (shouldSkipKey) {
      this.preeditText = ""
      this._engineUpdatePreeditText()

      return KeyEventReturn.NativeHandling
    }

    if (keycode === KeyCodes.BACKSPACE) {
      if (!this.preeditText) {
        return KeyEventReturn.NativeHandling
      }

      this.preeditText = this.preeditText.slice(0, this.preeditText.length - 1)
    } else {
      this.preeditText += key
    }

    this._engineUpdatePreeditText()

    return KeyEventReturn.CustomHandling
  }
}

const main = () => {
  new PreeditTest()

  PreeditTest.init()

  return Promise.resolve()
}

export default main
