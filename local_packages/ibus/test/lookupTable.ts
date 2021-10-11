import * as ibus from "../src"
import * as ibusHelpers from "../src/helpers"

const { KeyCodes, KeyEventReturn } = ibus

const disableHandler = () => {
  console.log("disable called from JS")
}

const table = ibus.lookupTableNew({
  cursorPos: 1,
  isRound: false,
  isVisible: true,
  pageSize: 4,
})

const enableHandler = () => {
  console.log("enable called from JS")
  ibus.lookupTableSetOrientation({
    orientation: ibus.IBusOrientation.IBUS_ORIENTATION_VERTICAL,
    table,
  })
  // ibus.lookupTableSetCursorVisible(false)
  ibus.lookupTableSetPageSize({
    pageSize: 5,
    table,
  })
  ibus.lookupTableSetRound(table)
}

const keyEventHandler = (keyInfo: ibus.KeyInfo): boolean => {
  const key = String.fromCharCode(keyInfo.keyval) || ""

  const isReleasedKey = ibus.helpers.isReleasedKey(keyInfo)

  if (isReleasedKey) {
    return KeyEventReturn.NativeHandling
  }

  const { keycode } = keyInfo

  if (keycode === KeyCodes.UP) {
    ibus.lookupTableCursorUp(table)
    ibus.engineUpdateLookupTable({ isVisible: true, table })

    return KeyEventReturn.CustomHandling
  }

  if (keycode === KeyCodes.DOWN) {
    ibus.lookupTableCursorDown(table)
    ibus.engineUpdateLookupTable({ isVisible: true, table })

    return KeyEventReturn.CustomHandling
  }

  if (keycode === KeyCodes.PAGE_UP) {
    ibus.lookupTablePageUp(table)
    ibus.engineUpdateLookupTable({ isVisible: true, table })

    return KeyEventReturn.CustomHandling
  }

  if (keycode === KeyCodes.PAGE_DOWN) {
    ibus.lookupTablePageDown(table)
    ibus.engineUpdateLookupTable({ isVisible: true, table })

    return KeyEventReturn.CustomHandling
  }

  const candidatesNum = ibus.lookupTableGetNumberOfCandidates(table)

  if (key === "l") {
    const textStr = `Sample ${candidatesNum + 1}`
    const text = ibus.textNewFromString(textStr)
    const list = ibus.attrListNew()
    const attrUnderline = ibus.attributeNew({
      endIndex: textStr.length,
      startIndex: 0,
      type: ibus.IBusAttrType.IBUS_ATTR_TYPE_UNDERLINE,
      value: ibus.IBusAttrUnderline.IBUS_ATTR_UNDERLINE_SINGLE,
    })
    const attrForegroundFirst = ibus.attrForegroundNew({
      color: 0x00ff00,
      endIndex: "Sample".length,
      startIndex: 0,
    })
    const attrForegroundSecond = ibus.attrForegroundNew({
      color: 0x0000ff,
      endIndex: textStr.length,
      startIndex: "Sample ".length,
    })

    ;[attrUnderline, attrForegroundFirst, attrForegroundSecond].forEach(
      (attr) => {
        ibus.attrListAppend({ attr, list })
      }
    )

    ibus.textSetAttributes({ list, text })

    ibus.lookupTableAppendCandidate({ table, text })
  } else if (key === "p") {
    ibus.engineHideLookupTable()
    ibus.lookupTableClear(table)
  } else if (key === "i" && candidatesNum > 0) {
    const cursorPos = ibus.lookupTableGetCursorPos(table)
    const pageSize = ibus.lookupTableGetPageSize(table)
    const rowIndex = ibus.lookupTableGetCursorInPage(table)

    console.log(
      "main.js: rowIndex",
      rowIndex,
      "pageSize",
      pageSize,
      "cursorPos",
      cursorPos
    )

    ibus.lookupTableSetLabel({ candidateIndex: rowIndex, label: "ABC", table })
    ibus.engineUpdateLookupTable({ isVisible: true, table })

    return KeyEventReturn.CustomHandling
  }

  if (key !== "p" && key !== "i") {
    if (candidatesNum > 0) {
      ibus.lookupTableSetCursorPos({ cursorPos: candidatesNum - 1, table })
    }

    ibus.engineUpdateLookupTable({ isVisible: true, table })
  }

  return KeyEventReturn.CustomHandling
}

// from the XML file
const config = {
  busName: "im.custom-ime.CustomIme",
  imeName: "custom-ime",
}

const main = () => {
  ibus.registerHandlers({
    disable: disableHandler,
    enable: enableHandler,
    focusIn: () => {},
    focusOut: () => {},
    keyEvent: keyEventHandler,
    propertyActivate: () => {},
  })

  ibusHelpers.initFull({
    busName: config.busName,
    imeName: config.imeName,
  })

  ibus.main()

  return Promise.resolve()
}

export default main
