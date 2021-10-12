import {
  IBusAttrType,
  IBusAttrUnderline,
  IBusAttribute,
  attrForegroundNew,
  attributeNew,
} from ".."

class Attribute {
  public static IBusAttrType = IBusAttrType
  public static IBusAttrUnderline = IBusAttrUnderline

  private readonly attribute: IBusAttribute

  private constructor(attribute: IBusAttribute) {
    this.attribute = attribute
  }

  public static new(opts: Parameters<typeof attributeNew>[0]) {
    const attribute = attributeNew(opts)

    return new Attribute(attribute)
  }

  public static newForeground(opts: Parameters<typeof attrForegroundNew>[0]) {
    const attribute = attrForegroundNew(opts)

    return new Attribute(attribute)
  }

  public getRef() {
    return this.attribute
  }
}

export { Attribute }
