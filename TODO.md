- [ ] Create test files under ibus package for several usage flows to improve API
    - [x] Preedit text
    - [x] Auxiliary text
    - [ ] Lookup table with transitions

## General Improvements

- Support more IBus methods
- Far down the line: use `status` in C methods to check for errors
    - Add error handling
- Improve key detection, consider adding a dependency
- Support using TS in some files
- Memory cleanup on teardown
- Don't have a global engine, proplist, or lookup table in C but pass it from JS
- Instead of using string for IBusText, use a wrapper to allow adding attributes

## Challenges

- Different keyboard layouts
- Unicode
- Shortcuts
