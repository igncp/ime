type Addon = {
  send: (message: string) => void
}

// eslint-disable-next-line @typescript-eslint/no-var-requires
const addon = require("../build/Release/module") as Addon

export default addon
