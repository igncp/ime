const ibus = require("../src");

ibus.init((val) => {
  console.log("Called from inside the callback", val);

  ibus.main();
});
