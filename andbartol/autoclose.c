static uint16_t autoclose_timer  = 0;
static uint16_t opening_keycode  = KC_NO;

static void reset_autoclose(void) {
    autoclose_timer = 0;
    opening_keycode = KC_NO;
}

static bool complete_autoclose(uint16_t expected_opening_keycode) {
    if (opening_keycode != expected_opening_keycode) {
        return true;
    }

    bool within_term = timer_elapsed(autoclose_timer) < AUTOCLOSE_TERM;

    reset_autoclose();

    return !within_term;
}

bool process_autoclose(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    switch (keycode) {
        case KC_LCBR:
        case KC_LBRC:
        case KC_LPRN:
            opening_keycode = keycode;
            autoclose_timer = timer_read();
            return true;

        case KC_RCBR:
            if (!complete_autoclose(KC_LCBR)) {
                SEND_STRING("}" SS_TAP(X_LEFT));
                return false;
            }
            break;

        case KC_RBRC:
            if (!complete_autoclose(KC_LBRC)) {
                SEND_STRING("]" SS_TAP(X_LEFT));
                return false;
            }
            break;

        case KC_RPRN:
            if (!complete_autoclose(KC_LPRN)) {
                SEND_STRING(")" SS_TAP(X_LEFT));
                return false;
            }
            break;
    }

    return true;
}
