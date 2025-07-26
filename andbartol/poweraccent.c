uint16_t pa_start_timer = 0;
uint16_t pa_start_keycode = 0;
bool     pa_shift = false;
bool     pa_timer_running = false;
bool     pa_first_space_pressed = false;

char*
find_string_combo(void) {
  if (!pa_shift) {
    switch (pa_start_keycode) {
      case KC_A: return "`a";
      case KC_E: return "`e";
      case KC_I: return "`i";
      case KC_O: return "`o";
      case KC_U: return "`u";
      default: return "";
    }
  } else {
    switch (pa_start_keycode) {
      case KC_A: return "`A";
      case KC_E: return "`E";
      case KC_I: return "`I";
      case KC_O: return "`O";
      case KC_U: return "`U";
      default: return "";
    }
  }
}

char*
find_string_combo_2(void) {
  if (!pa_shift) {
    switch (pa_start_keycode) {
      case KC_A: return "'a";
      case KC_E: return "'e";
      case KC_I: return "'i";
      case KC_O: return "'o";
      case KC_U: return "'u";
      default: return "";
    }
  } else {
    switch (pa_start_keycode) {
      case KC_A: return "'A";
      case KC_E: return "'E";
      case KC_I: return "'I";
      case KC_O: return "'O";
      case KC_U: return "'U";
      default: return "";
    }
  }
}

bool
process_poweraccent(uint16_t keycode, keyrecord_t *record) {
  uint8_t mods = get_mods();
  bool shift_pressed = mods & MOD_MASK_SHIFT;

  if (KC_A == keycode || KC_E == keycode || KC_I == keycode || KC_O == keycode || KC_U == keycode) {
    if (record->event.pressed) {
      pa_start_keycode = keycode;
      pa_start_timer = timer_read();
      pa_shift = shift_pressed;
      pa_timer_running = true;
    } else {
      pa_timer_running = false;
      pa_first_space_pressed = false;
    }
  } else if (pa_timer_running && KC_SPC == keycode && record->event.pressed) {
    if (timer_elapsed(pa_start_timer) > POWERACCENT_TERM) {
      clear_mods();
      SEND_STRING(SS_TAP(X_BSPC) SS_TAP(X_SCRL));
      if (!pa_first_space_pressed) {
        send_string(find_string_combo());
        pa_first_space_pressed = true;
      } else {
        send_string(find_string_combo_2());
        pa_first_space_pressed = false;
      }
      set_mods(mods);
      return false;
    }
    pa_timer_running = false;
    pa_first_space_pressed = false;
  }

  return true;
}
