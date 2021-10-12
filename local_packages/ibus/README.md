The current objective of this package is to expose just some of the many C
functions available from IBus: the ones already used by `ibus-rime` plus some
of the important ones.

The approach is to wrap most of the C structs by Node.js objects, and keep the
naming and signatures similar to the ones provided by the C functions.

You can see the exposed functions in:

- [C bindings](./bindings/module.c): All the exposed functions are listed here
- [Custom IME](./bindings/custom_ime.h): Required to register the engine GType
- [Node.js side](./src/index.ts): This is the main Node.js client to use from external consumers
- [Node.js helpers](./src/helpers.ts): Some utility functions that use the Node.js for common operations

You can also find more information in the [IBus API docs](https://ibus.github.io/docs/ibus-1.5/index.html).
