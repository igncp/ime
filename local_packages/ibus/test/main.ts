import auxiliary from "./auxiliary"
import bus from "./bus"
import engine from "./engine"
import lookupTable from "./lookupTable"
import preedit from "./preedit"
import properties from "./properties"

const modules = {
  auxiliary,
  bus,
  engine,
  lookupTable,
  preedit,
  properties,
}

const { lookupTable: main } = modules

main().catch((error) => {
  console.log("main.ts: error", error)
})
