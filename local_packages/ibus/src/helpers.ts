import {
  IBusEngineDesc,
  busGetConnection,
  busIsConnected,
  busNew,
  busRequestName,
  engineDescGetAuthor,
  engineDescGetDescription,
  engineDescGetHotkeys,
  engineDescGetLanguage,
  engineDescGetLayout,
  engineDescGetLicense,
  engineDescGetLongname,
  engineDescGetName,
  engineDescGetRank,
  engineDescGetSetup,
  engineDescGetSymbol,
  engineDescGetTextdomain,
  engineDescGetVersion,
  factoryAddEngine,
  factoryNew,
  init,
} from "."
import { AttrList } from "./models/AttrList"
import { Attribute } from "./models/Attribute"
import { Bus } from "./models/Bus"
import { Connection } from "./models/Connection"
import { Engine } from "./models/Engine"
import { Factory } from "./models/Factory"
import { LookupTable } from "./models/LookupTable"
import { Text } from "./models/Text"

const buildEngineDescInfo = (engineDesc: IBusEngineDesc) => ({
  author: engineDescGetAuthor(engineDesc),
  description: engineDescGetDescription(engineDesc),
  hotkeys: engineDescGetHotkeys(engineDesc),
  language: engineDescGetLanguage(engineDesc),
  layout: engineDescGetLayout(engineDesc),
  license: engineDescGetLicense(engineDesc),
  longname: engineDescGetLongname(engineDesc),
  name: engineDescGetName(engineDesc),
  rank: engineDescGetRank(engineDesc),
  setup: engineDescGetSetup(engineDesc),
  symbol: engineDescGetSymbol(engineDesc),
  textdomain: engineDescGetTextdomain(engineDesc),
  version: engineDescGetVersion(engineDesc),
})

const initFull = ({
  busName,
  imeName,
}: {
  busName: string
  imeName: string
}) => {
  init()

  const bus = busNew()

  if (!busIsConnected(bus)) {
    console.error("not connected to ibus") // eslint-disable-line no-console
    process.exit(1)
  }

  const connection = busGetConnection(bus)
  const factory = factoryNew(connection)

  factoryAddEngine({
    engineName: imeName,
    factory,
  })

  const busRequest = busRequestName({ bus, busName })

  if (busRequest === 0) {
    console.error("error requesting bus name") // eslint-disable-line no-console
    process.exit(1)
  }

  return {
    bus,
    connection,
  }
}

export {
  AttrList,
  Attribute,
  Bus,
  Connection,
  Engine,
  Factory,
  LookupTable,
  Text,
  buildEngineDescInfo,
  initFull,
}
