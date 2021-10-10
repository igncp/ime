Proof of concept of an IME (Input Method Editor) for IBus written in TypeScript

[![Checks](https://github.com/igncp/ime/actions/workflows/checks.yml/badge.svg)](https://github.com/igncp/ime/actions/workflows/checks.yml)

Using [ibus-rime](https://github.com/rime/ibus-rime) as a reference for the IBus integration

This project is WIP and in a very early stage. The current objectives are:

1. Create Node.js bindings for [IBus](https://github.com/ibus/ibus) which is written in C
    - You can check the current progress of the bindings in [local_packages/ibus](./local_packages/ibus)
1. Have a proof of concept of an IME with very few features using IBus
    - There are several examples in [local_packages/ibus/test](./local_packages/ibus/test) that use several IBus features
    - Rime configuration files are listed in the [plum repository](https://github.com/rime/plum), the MVP will not understand these files yet
