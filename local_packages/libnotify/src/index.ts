import addon from "./addon"

const send = (message: string) => {
  if (!message || typeof message !== "string") {
    throw new Error("Invalid argument")
  }

  addon.send(message)
}

export { send }
