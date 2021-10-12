import {
  IBusLookupTable,
  IBusOrientation,
  lookupTableAppendCandidate,
  lookupTableClear,
  lookupTableCursorDown,
  lookupTableCursorUp,
  lookupTableGetCursorInPage,
  lookupTableGetCursorPos,
  lookupTableGetNumberOfCandidates,
  lookupTableGetPageSize,
  lookupTableNew,
  lookupTablePageDown,
  lookupTablePageUp,
  lookupTableSetCursorPos,
  lookupTableSetCursorVisible,
  lookupTableSetLabel,
  lookupTableSetOrientation,
  lookupTableSetPageSize,
  lookupTableSetRound,
} from ".."

import { Text } from "./Text"

type LookupTableOpts = Parameters<typeof lookupTableNew>[0]

class LookupTable {
  public static IBusOrientation = IBusOrientation

  private readonly table: IBusLookupTable

  private constructor(opts: LookupTableOpts) {
    this.table = lookupTableNew(opts)
  }

  public static create(opts: LookupTableOpts) {
    return new LookupTable(opts)
  }

  public appendCandidate(text: Text) {
    lookupTableAppendCandidate({ table: this.table, text: text.getRef() })
  }

  public clear() {
    lookupTableClear(this.table)
  }

  public cursorDown() {
    lookupTableCursorDown(this.table)
  }

  public cursorUp() {
    lookupTableCursorUp(this.table)
  }

  public getCursorInPage() {
    return lookupTableGetCursorInPage(this.table)
  }

  public getCursorPos() {
    return lookupTableGetCursorPos(this.table)
  }

  public getNumberOfCandidates() {
    return lookupTableGetNumberOfCandidates(this.table)
  }

  public getPageSize() {
    return lookupTableGetPageSize(this.table)
  }

  public pageDown() {
    lookupTablePageDown(this.table)
  }

  public pageUp() {
    lookupTablePageUp(this.table)
  }

  public setCursorPos(cursorPos: number) {
    lookupTableSetCursorPos({ cursorPos, table: this.table })
  }

  public setCursorVisible(isVisible: boolean) {
    lookupTableSetCursorVisible({ isVisible, table: this.table })
  }

  public setOrientation(orientation: IBusOrientation) {
    lookupTableSetOrientation({
      orientation,
      table: this.table,
    })
  }

  public setLabel(
    opts: Omit<Parameters<typeof lookupTableSetLabel>[0], "table">
  ) {
    lookupTableSetLabel({
      ...opts,
      table: this.table,
    })
  }

  public setPageSize(pageSize: number) {
    lookupTableSetPageSize({
      pageSize,
      table: this.table,
    })
  }

  public setRound(isRound: boolean) {
    lookupTableSetRound({
      isRound,
      table: this.table,
    })
  }

  public getRef() {
    return this.table
  }
}

export { LookupTable }
