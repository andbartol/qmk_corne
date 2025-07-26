uint16_t vim_accum = 0;
bool vim_delete_flag = false;
bool change_flag = false;

bool
process_vim_layer(uint16_t keycode, keyrecord_t *record, int vimlayer) {
  uint8_t mods = get_mods();
  bool shift_pressed = mods & MOD_MASK_SHIFT;
  bool ctrl_pressed  = mods & MOD_MASK_CTRL;

  if (!layer_state_is(vimlayer)) return true;
  if (keycode == KC_W && record->event.pressed) {
    uint16_t times = vim_accum != 0 ? vim_accum : 1;
    if (vim_delete_flag) {
      for (; times > 0; times--)
        SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_DEL) SS_DELAY(1) SS_UP(X_LCTL) SS_UP(X_DEL));
      vim_delete_flag = false;
    } else {
      for (; times > 0; times--)
        SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_RIGHT) SS_DELAY(1) SS_UP(X_LCTL) SS_UP(X_RIGHT));
    }
    vim_accum = 0;
    return false;
  }
  else if (keycode == KC_B && record->event.pressed) {
    uint16_t times = vim_accum != 0 ? vim_accum : 1;
    if (vim_delete_flag) {
      for (; times > 0; times--)
        SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_BSPC) SS_DELAY(1) SS_UP(X_LCTL) SS_UP(X_BSPC));
      vim_delete_flag = false;
    } else {
      for (; times > 0; times--)
        SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_LEFT) SS_DELAY(1) SS_UP(X_LCTL) SS_UP(X_LEFT));
    }
    vim_accum = 0;
    return false;
  }
  else if (keycode == KC_D && record->event.pressed) {
    if (vim_delete_flag) {
      SEND_STRING(SS_DOWN(X_HOME) SS_DELAY(1) SS_UP(X_HOME));
      SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_LSFT) SS_DOWN(X_END) SS_DELAY(1) SS_UP(X_LCTL) SS_UP(X_LSFT) SS_UP(X_END));
      SEND_STRING(SS_DOWN(X_BSPC) SS_DELAY(1) SS_UP(X_BSPC));
      vim_delete_flag = false;
    }
    else
      vim_delete_flag = true;
    return false;
  }
  else if (keycode == KC_X && record->event.pressed) {
    SEND_STRING(SS_DOWN(X_DEL) SS_DELAY(1) SS_UP(X_DEL));
    vim_delete_flag = false;
    change_flag = false;
    return false;
  }
  else if (keycode == KC_C && record->event.pressed) {
    vim_delete_flag = true;
    change_flag = true;
    return false;
  }
  else if (keycode == KC_I && record->event.pressed) {
    if (shift_pressed)
      SEND_STRING(SS_DOWN(X_HOME) SS_DELAY(1) SS_UP(X_HOME));
    layer_off(vimlayer);
    vim_delete_flag = false;
    change_flag = false;
    return false;
  }
  else if (keycode == KC_A && record->event.pressed) {
    if (shift_pressed)
      SEND_STRING(SS_DOWN(X_END) SS_DELAY(1) SS_UP(X_END));
    layer_off(vimlayer);
    vim_delete_flag = false;
    change_flag = false;
    return false;
  }
  else if (keycode == KC_ESC && record->event.pressed) {
    if (ctrl_pressed) {
      SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_LSFT) SS_DOWN(X_Z) SS_DELAY(1) SS_UP(X_LCTL) SS_UP(X_LSFT) SS_UP(X_Z));
    }
    vim_delete_flag = false;
    vim_accum = 0;
    return false;
  }
  else if (keycode == KC_HOME && record->event.pressed) {
    if (vim_delete_flag) {
      SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_LSFT) SS_DOWN(X_HOME) SS_DELAY(1) SS_UP(X_LCTL) SS_UP(X_LSFT) SS_UP(X_HOME));
      SEND_STRING(SS_DOWN(X_BSPC) SS_DELAY(1) SS_UP(X_BSPC));
      vim_delete_flag = false;
      return false;
    }
    vim_accum = 0;
  }
  else if (keycode == KC_U && record->event.pressed) {
    SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_Z) SS_DELAY(1) SS_UP(X_Z) SS_UP(X_LCTL) SS_DELAY(1));
    vim_accum = 0;
    vim_delete_flag = false;
  }
  else if (keycode == KC_END && record->event.pressed) {
    if (vim_delete_flag) {
      SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_LSFT) SS_DOWN(X_END) SS_DELAY(1) SS_UP(X_LCTL) SS_UP(X_LSFT) SS_UP(X_END));
      SEND_STRING(SS_DOWN(X_BSPC) SS_DELAY(1) SS_UP(X_BSPC));
      vim_delete_flag = false;
      return false;
    }
    vim_accum = 0;
  }
  else if (keycode >= KC_1 && keycode <= KC_0 && record->event.pressed) {
    if (keycode == KC_0) vim_accum *= 10;
    else vim_accum = (vim_accum * 10) + keycode - KC_1 + 1;
    return false;
  }
  else if (keycode >= KC_RIGHT && keycode <= KC_UP && record->event.pressed) {
    uint16_t times = vim_accum != 0 ? vim_accum : 1;
    switch (keycode) {
      case KC_RIGHT:
        if (vim_delete_flag) {
          for (; times > 0; times--)
            SEND_STRING(SS_DOWN(X_DEL) SS_DELAY(1) SS_UP(X_DEL));
          vim_delete_flag = false;
        } else {
          for (; times > 0; times--)
            SEND_STRING(SS_DOWN(X_RIGHT) SS_DELAY(1) SS_UP(X_RIGHT));
        }
        break;
      case KC_LEFT:
        if (vim_delete_flag) {
          for (; times > 0; times--)
            SEND_STRING(SS_DOWN(X_BSPC) SS_DELAY(1) SS_UP(X_BSPC));
          vim_delete_flag = false;
        } else {
          for (; times > 0; times--)
            SEND_STRING(SS_DOWN(X_LEFT) SS_DELAY(1) SS_UP(X_LEFT));
        }
        break;
      case KC_UP:
        for (; times > 0; times--)
          SEND_STRING(SS_DOWN(X_UP) SS_DELAY(1) SS_UP(X_UP));
        break;
      case KC_DOWN:
        for (; times > 0; times--)
          SEND_STRING(SS_DOWN(X_DOWN) SS_DELAY(1) SS_UP(X_DOWN));
        break;
    }
    vim_accum = 0;
    return false;
  }
  return true;
}

