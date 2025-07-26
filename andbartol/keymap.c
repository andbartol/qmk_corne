#include QMK_KEYBOARD_H
#include "passwd.c"
#include "process_vim.h"
#include "autoclose.h"
#include "poweraccent.h"

#ifndef PASSWD
#define PASSWD ""
#endif

enum layer_number {
  _BASE = 0,
  _NUMS,
  _SYMB,
  _FKEY,
  _MVWN,
  _MOUS,
  _VIML,
  _VIMN,
};

enum my_keycodes {
  KC_PASS = SAFE_RANGE,
  KC_TEST,
};

enum {
  TD_VESC,
};

#define KC_NUMS MO(_NUMS)
#define KC_SYMB MO(_SYMB)
#define KC_FKEY MO(_FKEY)
#define KC_MVWN MO(_MVWN)
#define KC_MOUS MO(_MOUS)
#define KC_ALTT LALT(KC_TAB)
#define KC_ALF3 LALT(KC_F3)
#define KC_VESC KC_ESC
// #define KC_VESC TD(TD_VESC) // vim mode

#ifdef MASTER_LEFT
#define KC_CLSE LALT(KC_F4)
#define KC_LOCK KC_L
#else
#define KC_CLSE LGUI(LSFT(KC_Q))
#define KC_LOCK LGUI(LSFT(KC_M))
#endif

tap_dance_action_t tap_dance_actions[] = {
    [TD_VESC] = ACTION_TAP_DANCE_LAYER_MOVE(KC_ESC, _VIML),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_VESC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_MVWN, KC_NUMS,  KC_SPC,     KC_ENT, KC_SYMB, KC_LALT
                                      //`--------------------------'  `--------------------------'

  ),

    [_NUMS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_ALTT,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, KC_ALF3, KC_CLSE, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, XXXXXXX, KC_PGUP,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_MOUS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGDN,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, KC_FKEY, KC_LALT
                                      //`-----------------------------'  `--------------------------'
  ),

    [_SYMB] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, KC_FKEY,  KC_SPC,     KC_ENT, _______, KC_LALT
                                      //`--------------------------'  `--------------------------'
  ),

    [_FKEY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_MPLY,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,  KC_F11,  KC_F12, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_HOME, XXXXXXX, XXXXXXX,  KC_END, XXXXXXX, KC_VOLU,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_PASS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_LALT
                                      //`--------------------------'  `--------------------------'
  ),

    [_MVWN] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, _______, _______, _______, _______, _______,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, KC_LOCK, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_LALT
                                      //`--------------------------'  `--------------------------'
  ),

    [_MOUS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_ALTT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_WH_U, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX, KC_PGUP,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, _______, KC_ACL0, KC_ACL1, KC_ACL2, XXXXXXX,                      KC_WH_D, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGDN,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_BTN1, KC_BTN2, KC_LALT
                                      //`-----------------------------'  `--------------------------'
  ),

    [_VIML] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_ALTT, XXXXXXX,    KC_W, XXXXXXX,  KC_END, XXXXXXX,                      XXXXXXX,    KC_U,    KC_I, XXXXXXX,KC_HOME, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A, XXXXXXX,    KC_D, XXXXXXX, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, XXXXXXX, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX,    KC_X,    KC_C, XXXXXXX,    KC_B,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,MO(_VIMN),  KC_SPC,     KC_ENT,KC_SYMB, KC_LALT
                                      //`-----------------------------'  `--------------------------'
  ),

    [_VIMN] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_ALTT,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, XXXXXXX, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, KC_FKEY, KC_LALT
                                      //`-----------------------------'  `--------------------------'
  ),
};

void
press_button(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed)
    {
      register_code(keycode);
    } else {
      unregister_code(keycode);
    }
}

bool cpd_pressed = false;
bool cpu_pressed = false;

bool
process_record_user(uint16_t keycode, keyrecord_t *record) {

  uint8_t mods = get_mods();
  bool ctrl_pressed = mods & MOD_MASK_CTRL;
  bool alt_pressed  = mods & MOD_MASK_ALT;

  if (!process_vim_layer(keycode, record, _VIML)) {
    return false;
  } else if (KC_MVWN == keycode) {
    press_button(KC_LGUI, record);
  } else if (KC_PASS == keycode && record->event.pressed) {
    SEND_STRING(PASSWD);
  } else if (KC_BSPC == keycode && ctrl_pressed && alt_pressed) {
    press_button(KC_DEL, record);
    return false;
  } else if (KC_QUOT == keycode && ctrl_pressed) {
    if (record->event.pressed) cpu_pressed = true;
    press_button(KC_PGUP, record);
    return false;
  } else if (KC_QUOT == keycode && !record->event.pressed && cpu_pressed) { // TODO: Estrarre questa logica contorta in un modulo
    cpu_pressed = false;
    press_button(KC_PGUP, record);
    return false;
  } else if (KC_VESC == keycode && ctrl_pressed) {
    if (record->event.pressed) cpd_pressed = true;
    press_button(KC_PGDN, record);
    return false;
  } else if (KC_VESC == keycode && !record->event.pressed && cpd_pressed) {
    cpd_pressed = false;
    press_button(KC_PGDN, record);
    return false;
  } else if (!process_autoclose(keycode, record)) {
    return false;
  }
#ifdef MASTER_RIGHT
  else if (!process_poweraccent(keycode, record)) {
    return false;
  }
#endif

  return true;
}

