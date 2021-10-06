Proof of concept of an IME (Input Method Editor) for IBus written in JS

Using [ibus-rime](https://github.com/rime/ibus-rime) as a reference for the IBus integration

This project is WIP and in a very early stage. The current objectives are:

1. Create Node.js bindings for [IBus](https://github.com/ibus/ibus) which is written in C
    - IBus is intended for Linux
1. Have a proof of concept of an IME with very few features using IBus
    - The target is that in the future it can support Rime configuration files and dictionaries
