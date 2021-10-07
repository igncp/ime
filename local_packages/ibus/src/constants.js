// https://ibus.github.io/docs/ibus-1.4/ibus-ibustypes.html#IBusModifierType-enum
const IBusModifierType = {
  IBUS_BUTTON1_MASK: 1 << 8,
  IBUS_BUTTON2_MASK: 1 << 9,
  IBUS_BUTTON3_MASK: 1 << 10,
  IBUS_BUTTON4_MASK: 1 << 11,
  IBUS_BUTTON5_MASK: 1 << 12,
  IBUS_CONTROL_MASK: 1 << 2,
  IBUS_FORWARD_MASK: 1 << 25,
  IBUS_HANDLED_MASK: 1 << 24,
  IBUS_HYPER_MASK: 1 << 27,
  IBUS_LOCK_MASK: 1 << 1,
  IBUS_META_MASK: 1 << 28,
  IBUS_MOD1_MASK: 1 << 3,
  IBUS_MOD2_MASK: 1 << 4,
  IBUS_MOD3_MASK: 1 << 5,
  IBUS_MOD4_MASK: 1 << 6,
  IBUS_MOD5_MASK: 1 << 7,
  IBUS_MODIFIER_MASK: 0x5f001fff,
  IBUS_RELEASE_MASK: 1 << 30,
  IBUS_SHIFT_MASK: 1 << 0,
  IBUS_SUPER_MASK: 1 << 26,
};

IBusModifierType.IBUS_IGNORED_MASK = IBusModifierType.IBUS_FORWARD_MASK;

const KeyCodes = {
  ALT_TAB: 56,
  ARROW_DOWN: 108,
  ARROW_LEFT: 105,
  ARROW_RIGHT: 106,
  ARROW_UP: 103,
  BACKSPACE: 14,
  CONTROL: 29,
  DEL: 111,
  DOWN: 108,
  ENTER: 28,
  ESC: 1,
  LOCK_NUM: 69,
  PAGE_DOWN: 109,
  PAGE_UP: 104,
  SHIFT: 42,
  SHIFT_RIGHT: 54,
  TAB: 15,
  UP: 103,
};

const KeyEventReturn = {
  CustomHandling: true,
  NativeHandling: false,
};

module.exports = {
  IBusModifierType,
  KeyCodes,
  KeyEventReturn,
};
