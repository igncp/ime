import { engineHideLookupTable, engineUpdateLookupTable } from ".."

import { LookupTable } from "./LookupTable"

class Engine {
  public static hideLookupTable() {
    engineHideLookupTable()
  }

  public static updateLookupTable({
    isVisible,
    table,
  }: {
    isVisible: boolean
    table: LookupTable
  }) {
    engineUpdateLookupTable({ isVisible, table: table.getRef() })
  }
}

export { Engine }
