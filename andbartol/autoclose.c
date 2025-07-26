uint16_t open_timer = 0;
uint16_t start_keycode = 0;

bool
process_autoclose(uint16_t keycode, keyrecord_t *record) {
	if (!record->event.pressed) return true;

	if (KC_LCBR == keycode) {
		open_timer = timer_read();
		start_keycode = keycode;
	} else if (KC_RCBR == keycode && KC_LCBR == start_keycode) {
		if (timer_elapsed(open_timer) < AUTOCLOSE_TERM) {
			SEND_STRING("}" SS_TAP(X_LEFT));
			open_timer = 0;
			start_keycode = 0;
			return false;
		} else {
			open_timer = 0;
			start_keycode = 0;
		}
	} else if (KC_LBRC == keycode) {
		open_timer = timer_read();
		start_keycode = keycode;
	} else if (KC_RBRC == keycode && KC_LBRC == start_keycode) {
		if (timer_elapsed(open_timer) < AUTOCLOSE_TERM) {
			SEND_STRING("]" SS_TAP(X_LEFT));
			open_timer = 0;
			start_keycode = 0;
			return false;
		} else {
			open_timer = 0;
			start_keycode = 0;
		}
	} else if (KC_LPRN == keycode) {
		open_timer = timer_read();
		start_keycode = keycode;
	} else if (KC_RPRN == keycode && KC_LPRN == start_keycode) {
		if (timer_elapsed(open_timer) < AUTOCLOSE_TERM) {
			SEND_STRING(")" SS_TAP(X_LEFT));
			open_timer = 0;
			start_keycode = 0;
			return false;
		} else {
			open_timer = 0;
			start_keycode = 0;
		}
	}

	return true;
}
