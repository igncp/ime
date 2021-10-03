const libnotify = require("libnotify");
const ibus = require("ibus");

const main = async () => {
  libnotify.send("Starting Custom IME");

  await ibus.init(() => {
    ibus.main();
  });
};

main();
