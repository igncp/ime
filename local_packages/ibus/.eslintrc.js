const { disabledRules, tsExtends, tsRules } = require("../../other/eslintForTS")

module.exports = {
  extends: "../../.eslintrc.js",
  overrides: [
    {
      extends: tsExtends,
      files: ["*.ts", "*.tsx"],
      parserOptions: {
        project: ["./tsconfig.json"],
        tsconfigRootDir: __dirname,
      },
      rules: {
        ...disabledRules,
        ...tsRules,
      },
    },
    {
      files: ["test/**/*"],
      rules: {
        "no-console": 0,
      },
    },
  ],
}
