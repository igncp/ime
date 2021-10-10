import * as ibus from "../src"
import * as ibusHelpers from "../src/helpers"

const { KeyCodes, KeyEventReturn } = ibus

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
]

class AuxiliaryTest {
  private auxiliaryText: string

  public constructor() {
    ibus.registerHandlers({
      disable: AuxiliaryTest.disable,
      enable: AuxiliaryTest.enable,
      focusIn: () => {},
      focusOut: () => {},
      keyEvent: this.keyEvent.bind(this),
      propertyActivate: () => {},
    })

    this.auxiliaryText = ""
  }

  public static init() {
    const config = {
      busName: "im.custom-ime.CustomIme",
      imeName: "custom-ime",
    }

    ibusHelpers.initFull({
      busName: config.busName,
      imeName: config.imeName,
    })

    ibus.main()
  }

  private static enable() {
    const engineName = ibus.engineGetName()

    console.log("enable called from JS: ", engineName)
  }

  private static disable() {
    console.log("disable called from JS")
  }

  private engineUpdateAuxiliaryText(isVisible: boolean) {
    ibus.engineUpdateAuxiliaryText({ isVisible, text: this.auxiliaryText })
  }

  private keyEvent(keyInfo: ibus.KeyInfo) {
    if (ibus.helpers.isReleasedKey(keyInfo)) {
      return KeyEventReturn.CustomHandling
    }

    const { keycode } = keyInfo
    const key = String.fromCharCode(keyInfo.keyval) || ""

    if (ibus.helpers.isKeyWithCtrl(keyInfo) || keycode === KeyCodes.SHIFT) {
      return KeyEventReturn.NativeHandling
    }

    if (keycode === KeyCodes.ESC) {
      this.auxiliaryText = ""
      this.engineUpdateAuxiliaryText(false)

      return KeyEventReturn.CustomHandling
    }

    if (keycode === KeyCodes.ENTER) {
      if (!this.auxiliaryText) {
        return KeyEventReturn.NativeHandling
      }

      ibus.engineCommitText(this.auxiliaryText)
      this.auxiliaryText = ""
      this.engineUpdateAuxiliaryText(false)

      return KeyEventReturn.CustomHandling
    }

    const shouldSkipKey = keysToSkip.includes(keycode)

    if (shouldSkipKey) {
      this.auxiliaryText = ""
      this.engineUpdateAuxiliaryText(false)

      return KeyEventReturn.NativeHandling
    }

    if (keycode === KeyCodes.BACKSPACE) {
      if (!this.auxiliaryText) {
        return KeyEventReturn.NativeHandling
      }

      this.auxiliaryText = this.auxiliaryText.slice(
        0,
        this.auxiliaryText.length - 1
      )
    } else {
      this.auxiliaryText += key
    }

    this.engineUpdateAuxiliaryText(!!this.auxiliaryText.length)

    return KeyEventReturn.CustomHandling
  }
}

const main = () => {
  new AuxiliaryTest()

  AuxiliaryTest.init()

  return Promise.resolve()
}

export default main
