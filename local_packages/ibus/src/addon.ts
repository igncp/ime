import {
  IBusAttrType,
  IBusAttrUnderline,
  IBusOrientation,
  IBusPropState,
  IBusPropType,
} from "./constants"

type KeyInfo = {
  keycode: number
  keyval: number
  modifiers: number
}

type PropertyActivate = {
  state: IBusPropState
}

type Handlers = {
  disable: () => void
  enable: () => void
  focusIn: () => void
  focusOut: () => void
  keyEvent: (keyInfo: KeyInfo) => boolean
  propertyActivate: (opts: PropertyActivate) => void
}

type IBusType<Name> = {
  _ibusObjType: Name
}

type IBusAttrList = IBusType<"IBusAttrList">
type IBusAttribute = IBusType<"IBusAttribute">
type IBusProperty = IBusType<"IBusProperty">
type IBusText = IBusType<"IBusText">

type AttributeNewOpts = {
  endIndex: number
  startIndex: number
  type: IBusAttrType
  value: IBusAttrUnderline | 0
}

type PropertyNewOpts = {
  isSensitive: boolean
  key: string
  label: IBusText
  state: IBusPropState
  tooltip: string
  type: IBusPropType
}

type Addon = {
  attrForegroundNew: (
    color: number,
    startIndex: number,
    endIndex: number
  ) => IBusAttribute
  attrListAppend: (list: IBusAttrList, attr: IBusAttribute) => void
  attrListNew: () => IBusAttrList
  attributeNew: (opts: AttributeNewOpts) => IBusAttribute
  engineCommitText: (text: string) => void
  engineGetName: () => string
  engineHideAuxiliaryText: () => void
  engineHideLookupTable: () => void
  engineHidePreeditText: () => void
  engineRegisterProperties: () => void
  engineShowAuxiliaryText: () => void
  engineShowLookupTable: () => void
  engineShowPreeditText: () => void
  engineUpdateAuxiliaryText: (text: string, isVisible: boolean) => void
  engineUpdateLookupTable: (isVisible: boolean) => void
  engineUpdatePreeditText: (
    text: string,
    cursorPos: number,
    isVisible: boolean
  ) => void
  init: (imeName: string, busName: string, cb: () => void) => void
  lookupTableAppendCandidate: (text: IBusText) => void
  lookupTableClear: () => void
  lookupTableCursorDown: () => void
  lookupTableCursorUp: () => void
  lookupTableGetCursorInPage: () => number
  lookupTableGetCursorPos: () => number
  lookupTableGetNumberOfCandidates: () => number
  lookupTableGetPageSize: () => number
  lookupTablePageDown: () => void
  lookupTablePageUp: () => void
  lookupTableSetCursorPos: (cursorPos: number) => void
  lookupTableSetCursorVisible: (isVisible: boolean) => void
  lookupTableSetLabel: (candidateIndex: number, label: string) => void
  lookupTableSetOrientation: (orientation: IBusOrientation) => void
  lookupTableSetPageSize: (pageSize: number) => void
  lookupTableSetRound: () => void
  main: () => void
  propListAppend: (prop: IBusProperty) => void
  propertyGetState: (property: IBusProperty) => IBusPropState
  propertyNew: (opts: PropertyNewOpts) => IBusProperty
  propertySetState: (property: IBusProperty, newState: IBusPropState) => void
  registerHandlers: (handlers: Handlers) => void
  textNewFromString: (text: string) => IBusText
  textSetAttributes: (text: IBusText, list: IBusAttrList) => void
}

// eslint-disable-next-line @typescript-eslint/no-var-requires
const addon = require("../build/Release/module") as Addon

export {
  AttributeNewOpts,
  Handlers,
  IBusAttrList,
  IBusAttribute,
  IBusProperty,
  IBusText,
  KeyInfo,
  PropertyActivate,
  PropertyNewOpts,
}

export default addon
