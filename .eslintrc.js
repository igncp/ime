const denyList = require("./scripts/restrictedNames")
const {
  commonExtends,
  disabledRules,
  tsExtends,
  tsRules,
} = require("./other/eslintForTS")

const isFindRules = process.env.FIND_RULES === "true"

module.exports = {
  env: {
    browser: true,
    es6: true,
    jest: true,
    node: true,
  },
  extends: isFindRules ? tsExtends : commonExtends,
  globals: {
    $: false,
    ROOT_PATH: false,
  },
  overrides: [
    {
      files: ["research/**/*.js"],
      rules: {
        "no-console": 0,
      },
    },
    {
      files: ["*.js"],
      rules: {
        "@typescript-eslint/explicit-member-accessibility": 0,
        "@typescript-eslint/no-unused-vars": 0,
        "no-shadow": 2,
      },
    },
    {
      files: ["*.d.ts"],
      rules: {
        "@typescript-eslint/init-declarations": 2,
        "init-declarations": 0,
        "no-var": 0,
      },
    },
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
  ],
  parser: "@typescript-eslint/parser",
  parserOptions: {
    ecmaVersion: 9,
    sourceType: "module",
  },
  plugins: [
    "prettier",
    "sort-destructure-keys",
    "import",
    "typescript-sort-keys",
    "@typescript-eslint",
  ],
  rules: {
    ...disabledRules,
    ...(isFindRules ? tsRules : {}),

    "arrow-body-style": [2, "as-needed"],
    "block-scoped-var": 2,
    "camelcase": [2, { properties: "never" }],
    "class-methods-use-this": 2,
    "consistent-return": 2,
    "eqeqeq": 2,
    "eslint-comments/no-unused-disable": 2,
    "func-names": 2,
    "id-denylist": [2, ...denyList],

    "import/exports-last": 2,
    "import/group-exports": 2,
    "import/no-namespace": 0, // @TODO: Reconsider to add in future for main src

    "init-declarations": [2, "always"],
    "max-params": [2, 1],
    "newline-before-return": 2,
    "no-console": 2,
    "no-constant-condition": [2, { checkLoops: false }],
    "no-else-return": [2, { allowElseIf: false }],
    "no-func-assign": 2,
    "no-multi-assign": 2,
    "no-nested-ternary": 2,
    "no-new-func": 2,
    "no-param-reassign": 2,
    "no-plusplus": 2,
    "no-restricted-globals": [2, "global"],
    "no-restricted-syntax": [
      "error",
      "IfStatement[consequent.type!='BlockStatement']",
    ],
    "no-return-assign": [2, "always"],
    "no-shadow": 0, // using ts plugin one
    "no-unneeded-ternary": 2,
    "no-unreachable": 2,
    "no-unreachable-loop": 2,
    "no-useless-call": 2,
    "no-useless-computed-key": 2,
    "no-useless-concat": 2,
    "no-useless-rename": 2,
    "no-useless-return": 2,
    "no-var": 2,
    "object-shorthand": [2, "always"],
    "one-var": [2, "never"],
    "padding-line-between-statements": [
      2,
      {
        blankLine: "always",
        next: ["const", "let"],
        prev: "*",
      },
      {
        blankLine: "always",
        next: "*",
        prev: ["const", "let"],
      },
      {
        blankLine: "any",
        next: ["const", "let"],
        prev: ["const", "let"],
      },
      {
        blankLine: "always",
        next: "function",
        prev: "multiline-block-like",
      },
      {
        blankLine: "always",
        next: "multiline-block-like",
        prev: "multiline-block-like",
      },
      {
        blankLine: "always",
        next: "block-like",
        prev: "block-like",
      },
      {
        blankLine: "always",
        next: "class",
        prev: "*",
      },
      {
        blankLine: "always",
        next: "*",
        prev: "class",
      },
      {
        blankLine: "always",
        next: "*",
        prev: "multiline-block-like",
      },
      {
        blankLine: "always",
        next: "multiline-block-like",
        prev: "*",
      },
      {
        blankLine: "always",
        next: "default",
        prev: "*",
      },
      {
        blankLine: "always",
        next: "function",
        prev: "*",
      },
    ],
    "prefer-arrow-callback": 2,
    "prefer-const": 2,
    "prefer-destructuring": [
      2,
      {
        AssignmentExpression: {
          array: false, // eslint-disable-line id-denylist
          object: false,
        },
        VariableDeclarator: {
          array: false, // eslint-disable-line id-denylist
          object: true,
        },
      },
      { enforceForRenamedProperties: true },
    ],
    "prefer-rest-params": 2,
    "prefer-template": 2,

    "prettier/prettier": "error",

    "quote-props": [2, "consistent-as-needed"],

    "require-atomic-updates": 2,

    "sort-destructure-keys/sort-destructure-keys": 2,

    "sort-imports": [
      "error",
      {
        ignoreDeclarationSort: true,
      },
    ],
    "sort-keys": 2,
    "spaced-comment": 2,

    "typescript-sort-keys/interface": "error",
    "typescript-sort-keys/string-enum": "error",
  },
}
