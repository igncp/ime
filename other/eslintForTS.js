const disabledRules = {
  "@typescript-eslint/ban-ts-comment": 0,
  "@typescript-eslint/explicit-module-boundary-types": 0,
  "@typescript-eslint/no-empty-function": 0,
  "@typescript-eslint/no-non-null-assertion": 0,
  "@typescript-eslint/no-unsafe-assignment": 0,
  "@typescript-eslint/no-unsafe-call": 0,
  "@typescript-eslint/no-unsafe-member-access": 0,
  "@typescript-eslint/no-unsafe-return": 0,
  "@typescript-eslint/restrict-plus-operands": 0,
  "@typescript-eslint/restrict-template-expressions": 0,
  "@typescript-eslint/unbound-method": 0,
}

const tsRules = {
  "@typescript-eslint/array-type": [2, { default: "array-simple" }],
  "@typescript-eslint/explicit-member-accessibility": 2,
  "@typescript-eslint/lines-between-class-members": [
    2,
    "always",
    { exceptAfterSingleLine: true },
  ],
  "@typescript-eslint/member-ordering": 2,
  "@typescript-eslint/method-signature-style": 2,
  "@typescript-eslint/no-duplicate-imports": 2,
  "@typescript-eslint/no-explicit-any": 2,
  "@typescript-eslint/no-redeclare": 2,
  "@typescript-eslint/no-shadow": 2,
  "@typescript-eslint/no-unnecessary-boolean-literal-compare": 2,
  "@typescript-eslint/no-unnecessary-condition": [
    2,
    { allowConstantLoopConditions: true },
  ],
  "@typescript-eslint/no-unnecessary-qualifier": 2,
  "@typescript-eslint/no-unnecessary-type-arguments": 2,
  "@typescript-eslint/no-unnecessary-type-assertion": 2,
  "@typescript-eslint/no-unnecessary-type-constraint": 2,
  "@typescript-eslint/no-unused-expressions": 2,
  "@typescript-eslint/no-unused-vars": 2,
  "@typescript-eslint/no-use-before-define": [
    2,
    {
      enums: true,
      ignoreTypeReferences: false,
      typedefs: true,
    },
  ],
  "@typescript-eslint/prefer-nullish-coalescing": 2,
  "@typescript-eslint/prefer-optional-chain": 2,
  "@typescript-eslint/prefer-readonly": 2,
  "@typescript-eslint/prefer-reduce-type-parameter": 2,
  "@typescript-eslint/sort-type-union-intersection-members": 2,
}

const commonExtends = [
  "eslint:recommended",
  "plugin:eslint-comments/recommended",
]

const tsExtends = commonExtends.concat([
  "plugin:@typescript-eslint/recommended",
  "plugin:@typescript-eslint/recommended-requiring-type-checking",
])

module.exports = {
  commonExtends,
  disabledRules,
  tsExtends,
  tsRules,
}
