import * as ibus from "../src"
import { Bus, Factory } from "../src/helpers"

const main = async () => {
  ibus.init()

  const bus = Bus.new()
  const connection = bus.getConnection()

  const engineName = "custom-ime"

  const factory = Factory.new(connection)

  factory.addEngine(engineName)

  bus.requestName("im.custom-ime.CustomIme")

  console.log("Waiting")
  ibus.main()

  await new Promise((resolve) => setTimeout(resolve, 1000))
}

export default main
