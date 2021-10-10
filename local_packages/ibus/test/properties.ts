import * as ibus from "../src"

const { KeyEventReturn } = ibus

class PropertiesTest {
  private firstProperty: ibus.IBusProperty | null = null

  public constructor() {
    ibus.registerHandlers({
      disable: PropertiesTest.disable,
      enable: PropertiesTest.enable,
      focusIn: this.focusIn.bind(this),
      focusOut: this.focusOut.bind(this),
      keyEvent: this.keyEvent.bind(this),
      propertyActivate: this.propertyActivate.bind(this),
    })
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

  private static enable() {
    const engineName = ibus.engineGetName()

    console.log("enable called from JS: ", engineName)
  }

  private static disable() {
    console.log("disable called from JS")
  }

  private focusOut() {
    if (this.firstProperty) {
      const state = ibus.propertyGetState(this.firstProperty)

      console.log("properties.ts: state", state)
    }
  }

  private keyEvent(keyInfo: ibus.KeyInfo) {
    if (ibus.helpers.isReleasedKey(keyInfo)) {
      return KeyEventReturn.CustomHandling
    }

    const key = String.fromCharCode(keyInfo.keyval) || ""

    if (key === "r" && this.firstProperty) {
      const state = ibus.propertyGetState(this.firstProperty)

      console.log("properties.ts: state", state)
    }

    console.log("properties.ts: keyInfo", keyInfo)

    return KeyEventReturn.CustomHandling
  }

  private propertyActivate(propertyActivate: ibus.PropertyActivate) {
    if (this.firstProperty) {
      ibus.propertySetState({
        newState: propertyActivate.state,
        property: this.firstProperty,
      })
    }

    console.log("properties.ts: propertyActivate", propertyActivate)
  }

  private focusIn() {
    console.log("focusIn JS")

    if (!this.firstProperty) {
      const label = ibus.textNewFromString("Sample Label")

      const property = ibus.propertyNew({
        isSensitive: true,
        key: "sampleKey",
        label,
        state: ibus.IBusPropState.PROP_STATE_CHECKED,
        tooltip: "Sample Tooltip",
        type: ibus.IBusPropType.PROP_TYPE_TOGGLE,
      })

      ibus.propListAppend(property)

      console.log("properties.ts: text", label)
      this.firstProperty = property
    }

    ibus.engineRegisterProperties()
  }
}

const main = () => {
  new PropertiesTest()

  PropertiesTest.init()

  return Promise.resolve()
}

export default main
