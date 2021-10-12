import { IBusBus, busGetConnection, busNew, busRequestName } from ".."

import { Connection } from "./Connection"

class Bus {
  private readonly bus: IBusBus

  private constructor() {
    this.bus = busNew()
  }

  public static new() {
    return new Bus()
  }

  public getConnection() {
    const connection = busGetConnection(this.bus)

    return Connection.fromExisting(connection)
  }

  public getRef() {
    return this.bus
  }

  public requestName(busName: string) {
    return busRequestName({ bus: this.bus, busName })
  }
}

export { Bus }
