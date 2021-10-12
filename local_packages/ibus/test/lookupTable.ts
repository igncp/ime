import {
  KeyCodes,
  KeyEventReturn,
  KeyInfo,
  helpers,
  main as mainIBus,
  registerHandlers,
} from "../src"
import * as ibusHelpers from "../src/helpers"

const { AttrList, Attribute, Engine, LookupTable, Text } = ibusHelpers

const disableHandler = () => {
  console.log("disable called from JS")
}

const table = LookupTable.create({
  cursorPos: 1,
  isRound: false,
  isVisible: true,
  pageSize: 4,
})

const enableHandler = () => {
  console.log("enable called from JS")
  table.setOrientation(LookupTable.IBusOrientation.IBUS_ORIENTATION_VERTICAL)

  table.setCursorVisible(true)
  table.setPageSize(5)
  table.setRound(false)
}

const keyEventHandler = (keyInfo: KeyInfo): boolean => {
  const key = String.fromCharCode(keyInfo.keyval) || ""

  const isReleasedKey = helpers.isReleasedKey(keyInfo)

  if (isReleasedKey) {
    return KeyEventReturn.NativeHandling
  }

  const { keycode } = keyInfo

  if (keycode === KeyCodes.UP) {
    table.cursorUp()
    Engine.updateLookupTable({ isVisible: true, table })

    return KeyEventReturn.CustomHandling
  }

  if (keycode === KeyCodes.DOWN) {
    table.cursorDown()
    Engine.updateLookupTable({ isVisible: true, table })

    return KeyEventReturn.CustomHandling
  }

  if (keycode === KeyCodes.PAGE_UP) {
    table.pageUp()
    Engine.updateLookupTable({ isVisible: true, table })

    return KeyEventReturn.CustomHandling
  }

  if (keycode === KeyCodes.PAGE_DOWN) {
    table.pageDown()
    Engine.updateLookupTable({ isVisible: true, table })

    return KeyEventReturn.CustomHandling
  }

  const candidatesNum = table.getNumberOfCandidates()

  if (key === "l") {
    const textStr = `Sample ${candidatesNum + 1}`
    const text = Text.newFromString(textStr)
    const list = AttrList.create()
    const attrUnderline = Attribute.new({
      endIndex: textStr.length,
      startIndex: 0,
      type: Attribute.IBusAttrType.IBUS_ATTR_TYPE_UNDERLINE,
      value: Attribute.IBusAttrUnderline.IBUS_ATTR_UNDERLINE_SINGLE,
    })
    const attrForegroundFirst = Attribute.newForeground({
      color: 0x00ff00,
      endIndex: "Sample".length,
      startIndex: 0,
    })
    const attrForegroundSecond = Attribute.newForeground({
      color: 0x0000ff,
      endIndex: textStr.length,
      startIndex: "Sample ".length,
    })

    ;[attrUnderline, attrForegroundFirst, attrForegroundSecond].forEach(
      (attr) => {
        list.append(attr)
      }
    )

    text.setAttributes(list)
    table.appendCandidate(text)
  } else if (key === "p") {
    Engine.hideLookupTable()
    table.clear()
  } else if (key === "i" && candidatesNum > 0) {
    const cursorPos = table.getCursorPos()
    const pageSize = table.getPageSize()
    const rowIndex = table.getCursorInPage()

    console.log(
      "main.js: rowIndex",
      rowIndex,
      "pageSize",
      pageSize,
      "cursorPos",
      cursorPos
    )

    table.setLabel({
      candidateIndex: rowIndex,
      label: "ABC",
    })
    Engine.updateLookupTable({ isVisible: true, table })

    return KeyEventReturn.CustomHandling
  }

  if (key !== "p" && key !== "i") {
    if (candidatesNum > 0) {
      table.setCursorPos(candidatesNum - 1)
    }

    Engine.updateLookupTable({ isVisible: true, table })
  }

  return KeyEventReturn.CustomHandling
}

// from the XML file
const config = {
  busName: "im.custom-ime.CustomIme",
  imeName: "custom-ime",
}

const main = () => {
  registerHandlers({
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

  mainIBus()

  return Promise.resolve()
}

export default main
