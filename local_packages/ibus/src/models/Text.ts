import { IBusText, textNewFromString, textSetAttributes } from ".."

import { AttrList } from "./AttrList"

class Text {
  private readonly text: IBusText

  private constructor(text: string) {
    this.text = textNewFromString(text)
  }

  public static newFromString(text: string) {
    return new Text(text)
  }

  public getRef() {
    return this.text
  }

  public setAttributes(list: AttrList) {
    textSetAttributes({ list: list.getRef(), text: this.text })
  }
}

export { Text }
