import { IBusFactory, factoryAddEngine, factoryNew } from ".."

import { Connection } from "./Connection"

class Factory {
  private readonly factory: IBusFactory

  private constructor(connection: Connection) {
    this.factory = factoryNew(connection.getRef())
  }

  public static new(connection: Connection) {
    return new Factory(connection)
  }

  public addEngine(engineName: string) {
    factoryAddEngine({
      engineName,
      factory: this.factory,
    })
  }

  public getRef() {
    return this.factory
  }
}

export { Factory }
