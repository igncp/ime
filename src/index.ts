import * as ibus from "ibus"
import * as libnotify from "libnotify"

const keyEventHandler = (keyInfo: ibus.KeyInfo) => {
  const key = String.fromCharCode(keyInfo.keyval) || ""

  const isReleasedKey = ibus.helpers.isReleasedKey(keyInfo)

  if (!isReleasedKey) {
    ibus.engineCommitText(key.toUpperCase())
  }

  return ibus.KeyEventReturn.CustomHandling
}

// from the XML file
const config = {
  busName: "im.custom-ime.CustomIme",
  imeName: "custom-ime",
}

const main = () => {
  libnotify.send("Starting Custom IME")

  ibus.registerHandlers({
    disable: () => {},
    enable: () => {},
    focusIn: () => {},
    focusOut: () => {},
    keyEvent: keyEventHandler,
    propertyActivate: () => {},
  })

  ibus.init({
    busName: config.busName,
    cb: () => {
      ibus.main()
    },
    imeName: config.imeName,
  })
}

main()
