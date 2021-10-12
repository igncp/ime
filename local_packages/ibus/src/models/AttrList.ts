import { IBusAttrList, attrListAppend, attrListNew } from ".."

import { Attribute } from "./Attribute"

class AttrList {
  private readonly list: IBusAttrList

  private constructor() {
    this.list = attrListNew()
  }

  public static create() {
    return new AttrList()
  }

  public append(attr: Attribute) {
    attrListAppend({ attr: attr.getRef(), list: this.list })
  }

  public getRef() {
    return this.list
  }
}

export { AttrList }
