const addon = require("../build/Release/module");

const init = (cb) => {
  return new Promise((resolve, reject) => {
    try {
      const result = addon.init(cb);

      resolve(result);
    } catch (error) {
      reject(error);
    }
  });
};

const main = () => {
  addon.main();
};

module.exports = {
  init,
  main,
};
