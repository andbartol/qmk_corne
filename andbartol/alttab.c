bool at_active = false;

bool
process_poweraccent(uint16_t keycode, keyrecord_t *record) {
  uint8_t mods = get_mods();
  bool alt_pressed = mods & MOD_MASK_ALT;

  if (alt_pressed && KC_TAB == keycode) {
    at_active = true;
    return false;
  }
}
