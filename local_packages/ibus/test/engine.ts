import * as ibus from "../src"

const main = async () => {
  ibus.init()

  const bus = ibus.busNew()
  const connection = ibus.busGetConnection(bus)
  const engineName = "foo"

  const engine = ibus.engineNew({
    connection,
    engineName,
    objPath: "/org/freedesktop/IBus/Engine/1",
  })
  const factory = ibus.factoryNew(connection)

  ibus.factoryAddEngine({
    engineName,
    factory,
  })

  console.log("engine.ts: engine", engine)

  console.log("Waiting")

  await new Promise((resolve) => setTimeout(resolve, 1000))
}

export default main
