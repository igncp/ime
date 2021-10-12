- [ ] Create test files under ibus package for several usage flows to improve API
    - [x] Preedit text
    - [x] Auxiliary text
    - [x] Property
    - [x] Bus
    - [x] Lookup table with transitions, remove the global one
    - [ ] Engine

## General Improvements

- Support more IBus methods
- Far down the line: use `status` in C methods to check for errors
    - Add error handling
- Improve key detection, consider adding a dependency
- Memory cleanup on teardown
- Create models for interacting with ibus and hiding the wrapped types

## Challenges

- Different keyboard layouts
- Unicode
- Shortcuts
