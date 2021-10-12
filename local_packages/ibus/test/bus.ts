import * as ibus from "../src"
import * as ibusHelpers from "../src/helpers"

const { KeyEventReturn } = ibus

const disableHandler = () => {
  console.log("disable called from JS")
}

const enableHandler = () => {
  console.log("enable called from JS")
}

const keyEventHandler = (keyInfo: ibus.KeyInfo): boolean => {
  const isReleasedKey = ibus.helpers.isReleasedKey(keyInfo)

  if (isReleasedKey) {
    return KeyEventReturn.NativeHandling
  }

  return KeyEventReturn.CustomHandling
}

// from the XML file
const config = {
  busName: "im.custom-ime.CustomIme",
  imeName: "custom-ime",
}

const main = () => {
  ibus.registerHandlers({
    disable: disableHandler,
    enable: enableHandler,
    focusIn: () => {},
    focusOut: () => {},
    keyEvent: keyEventHandler,
    propertyActivate: () => {},
  })

  const { bus, connection } = ibusHelpers.initFull({
    busName: config.busName,
    imeName: config.imeName,
  })

  const engines = ibus.busListEngines(bus)
  const enginesInfos = engines.map((engineDesc) =>
    ibusHelpers.buildEngineDescInfo(engineDesc)
  )

  console.log("bus.ts: enginesSummaries", enginesInfos.slice(0, 1))
  console.log(
    "bus.ts: customIMESummary",
    enginesInfos.find((engineInfo) => engineInfo.name === "custom-ime")
  )

  const currentInputContextString = ibus.busCurrentInputContext(bus)
  const inputContext = ibus.inputContextGetInputContext({
    connection,
    path: currentInputContextString,
  })

  console.log("bus.ts: inputContext", inputContext)

  ibus.main()

  return Promise.resolve()
}

export default main
