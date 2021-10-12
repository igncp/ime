import { GDBusConnection } from ".."

class Connection {
  private readonly connection: GDBusConnection

  private constructor(connection: GDBusConnection) {
    this.connection = connection
  }

  public static fromExisting(connection: GDBusConnection) {
    return new Connection(connection)
  }

  public getRef() {
    return this.connection
  }
}

export { Connection }
