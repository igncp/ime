import addon, {
  AttributeNewOpts,
  Handlers,
  IBusAttrList,
  IBusAttribute,
  IBusProperty,
  IBusText,
  KeyInfo,
  PropertyActivate,
  PropertyNewOpts,
} from "./addon"
import {
  IBusAttrType,
  IBusAttrUnderline,
  IBusModifierType,
  IBusOrientation,
  IBusPropState,
  IBusPropType,
  KeyCodes,
  KeyEventReturn,
} from "./constants"

const runWithCatch = <FnResult>(fn: () => FnResult): FnResult => {
  try {
    const functionResult = fn()

    return functionResult
  } catch (error) {
    console.log("index.js: error", error) // eslint-disable-line no-console

    throw error
  }
}

const engineCommitText = (text: string) => {
  runWithCatch(() => {
    addon.engineCommitText(text)
  })
}

const attrForegroundNew = ({
  color,
  endIndex,
  startIndex,
}: {
  color: number
  endIndex: number
  startIndex: number
}) => runWithCatch(() => addon.attrForegroundNew(color, startIndex, endIndex))

const attrListAppend = ({
  attr,
  list,
}: {
  attr: IBusAttribute
  list: IBusAttrList
}) => {
  runWithCatch(() => {
    addon.attrListAppend(list, attr)
  })
}

const attrListNew = () => runWithCatch(() => addon.attrListNew())

const attributeNew = (opts: AttributeNewOpts) =>
  runWithCatch(() => addon.attributeNew(opts))

const engineGetName = () => runWithCatch(() => addon.engineGetName())

const engineHideAuxiliaryText = () => {
  runWithCatch(() => {
    addon.engineHideAuxiliaryText()
  })
}

const engineHideLookupTable = () => {
  runWithCatch(() => {
    addon.engineHideLookupTable()
  })
}

const engineHidePreeditText = () => {
  runWithCatch(() => {
    addon.engineHidePreeditText()
  })
}

const engineRegisterProperties = () => {
  runWithCatch(() => {
    addon.engineRegisterProperties()
  })
}

const engineShowAuxiliaryText = () => {
  runWithCatch(() => {
    addon.engineShowAuxiliaryText()
  })
}

const engineShowLookupTable = () => {
  runWithCatch(() => {
    addon.engineShowLookupTable()
  })
}

const engineShowPreeditText = () => {
  runWithCatch(() => {
    addon.engineShowPreeditText()
  })
}

const engineUpdateAuxiliaryText = ({
  isVisible,
  text,
}: {
  isVisible: boolean
  text: string
}) => {
  runWithCatch(() => {
    addon.engineUpdateAuxiliaryText(text, isVisible)
  })
}

const engineUpdateLookupTable = (isVisible: boolean) => {
  if (typeof isVisible !== "boolean") {
    throw new Error("Incorrect param isVisible for engineUpdateLookupTable")
  }

  runWithCatch(() => {
    addon.engineUpdateLookupTable(isVisible)
  })
}

const engineUpdatePreeditText = ({
  cursorPos,
  isVisible,
  text,
}: {
  cursorPos: number
  isVisible: boolean
  text: string
}) => {
  runWithCatch(() => {
    addon.engineUpdatePreeditText(text, cursorPos, isVisible)
  })
}

const init = ({
  busName,
  cb,
  imeName,
}: {
  busName: string
  cb: () => void
  imeName: string
}) => {
  addon.init(imeName, busName, cb)
}

const main = () => {
  addon.main()
}

const registerHandlers = (handlers: Handlers) => {
  if (!handlers as unknown) {
    throw new Error("Missing handlers")
  }

  const handlerNames: Array<keyof Handlers> = ["keyEvent", "enable", "disable"]

  handlerNames.forEach((handlerName) => {
    if (typeof handlers[handlerName] !== "function") {
      throw new Error(`Incorrect handler ${handlerName}`)
    }
  })

  const wrappedHandlers = handlerNames.reduce<Handlers>(
    (...[handlersObj, handlerName]) => {
      // @ts-ignore
      handlersObj[handlerName] = (...args) =>
        // @ts-ignore
        runWithCatch(() => handlers[handlerName](...args))

      return handlersObj
    },
    { ...handlers }
  )

  addon.registerHandlers(wrappedHandlers)
}

const isReleasedKey = (keyInfo: KeyInfo) =>
  (keyInfo.modifiers & IBusModifierType.IBUS_RELEASE_MASK) !== 0

const isKeyWithCtrl = (keyInfo: KeyInfo) =>
  (keyInfo.modifiers & IBusModifierType.IBUS_CONTROL_MASK) !== 0

const isKeyWithShift = (keyInfo: KeyInfo) =>
  (keyInfo.modifiers & IBusModifierType.IBUS_SHIFT_MASK) !== 0

const lookupTableAppendCandidate = (text: IBusText) => {
  runWithCatch(() => {
    addon.lookupTableAppendCandidate(text)
  })
}

const lookupTableClear = () => {
  runWithCatch(() => {
    addon.lookupTableClear()
  })
}

const lookupTableCursorDown = () => {
  runWithCatch(() => {
    addon.lookupTableCursorDown()
  })
}

const lookupTableCursorUp = () => {
  runWithCatch(() => {
    addon.lookupTableCursorUp()
  })
}

const lookupTableGetCursorInPage = () =>
  runWithCatch(() => addon.lookupTableGetCursorInPage())

const lookupTableGetCursorPos = () =>
  runWithCatch(() => addon.lookupTableGetCursorPos())

const lookupTableGetNumberOfCandidates = () =>
  runWithCatch(() => addon.lookupTableGetNumberOfCandidates())

const lookupTableGetPageSize = () =>
  runWithCatch(() => addon.lookupTableGetPageSize())

const lookupTablePageDown = () => {
  runWithCatch(() => {
    addon.lookupTablePageDown()
  })
}

const lookupTablePageUp = () => {
  runWithCatch(() => {
    addon.lookupTablePageUp()
  })
}

const lookupTableSetCursorPos = (cursorPos: number) => {
  runWithCatch(() => {
    addon.lookupTableSetCursorPos(cursorPos)
  })
}

const lookupTableSetCursorVisible = (isVisible: boolean) => {
  runWithCatch(() => {
    addon.lookupTableSetCursorVisible(isVisible)
  })
}

const lookupTableSetLabel = ({
  candidateIndex,
  label,
}: {
  candidateIndex: number
  label: string
}) => {
  runWithCatch(() => {
    addon.lookupTableSetLabel(candidateIndex, label)
  })
}

const lookupTableSetOrientation = (orientation: IBusOrientation) => {
  runWithCatch(() => {
    addon.lookupTableSetOrientation(orientation)
  })
}

const lookupTableSetPageSize = (pageSize: number) => {
  runWithCatch(() => {
    addon.lookupTableSetPageSize(pageSize)
  })
}

const propListAppend = (prop: IBusProperty) => {
  runWithCatch(() => {
    addon.propListAppend(prop)
  })
}

const propertyGetState = (prop: IBusProperty) =>
  runWithCatch(() => addon.propertyGetState(prop))

const propertyNew = (opts: PropertyNewOpts) =>
  runWithCatch(() => addon.propertyNew(opts))

const propertySetState = ({
  newState,
  property,
}: {
  newState: IBusPropState
  property: IBusProperty
}) => {
  runWithCatch(() => {
    addon.propertySetState(property, newState)
  })
}

const textNewFromString = (text: string) =>
  runWithCatch(() => addon.textNewFromString(text))

const textSetAttributes = ({
  list,
  text,
}: {
  list: IBusAttrList
  text: IBusText
}) => {
  runWithCatch(() => {
    addon.textSetAttributes(text, list)
  })
}

const lookupTableSetRound = () => {
  runWithCatch(() => {
    addon.lookupTableSetRound()
  })
}

const helpers = {
  isKeyWithCtrl,
  isKeyWithShift,
  isReleasedKey,
}

export {
  IBusAttrType,
  IBusAttrUnderline,
  IBusModifierType,
  IBusOrientation,
  IBusPropState,
  IBusPropType,
  IBusProperty,
  IBusText,
  KeyCodes,
  KeyEventReturn,
  KeyInfo,
  PropertyActivate,
  attrForegroundNew,
  attrListAppend,
  attrListNew,
  attributeNew,
  engineCommitText,
  engineGetName,
  engineHideAuxiliaryText,
  engineHideLookupTable,
  engineHidePreeditText,
  engineRegisterProperties,
  engineShowAuxiliaryText,
  engineShowLookupTable,
  engineShowPreeditText,
  engineUpdateAuxiliaryText,
  engineUpdateLookupTable,
  engineUpdatePreeditText,
  helpers,
  init,
  lookupTableAppendCandidate,
  lookupTableClear,
  lookupTableCursorDown,
  lookupTableCursorUp,
  lookupTableGetCursorInPage,
  lookupTableGetCursorPos,
  lookupTableGetNumberOfCandidates,
  lookupTableGetPageSize,
  lookupTablePageDown,
  lookupTablePageUp,
  lookupTableSetCursorPos,
  lookupTableSetCursorVisible,
  lookupTableSetLabel,
  lookupTableSetOrientation,
  lookupTableSetPageSize,
  lookupTableSetRound,
  main,
  propListAppend,
  propertyGetState,
  propertyNew,
  propertySetState,
  registerHandlers,
  textNewFromString,
  textSetAttributes,
}
