#include QMK_KEYBOARD_H
#include <stdio.h>

// naginata
#include "naginata.h"
NGKEYS naginata_keys;

enum keymap_layers {
  _QWERTY,
  _DVORAK,
  _NAGINATA,
  _LOWER,
  _RAISE,
  _ADJUST,
  _NUM,
};

enum custom_keycodes {
  QWERTY = NG_SAFE_RANGE,
  LOWER,
  RAISE,
  EI,
  KANA,
  DVORAK,
  NAGINATA,
};

enum tap_dance_keycodes {
  Q,
  COMM,
  DOT,
  SCLN,
};

void comm_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code(KC_COMM);
  } else {
    layer_off(_DVORAK);
    naginata_off();
    tap_code(KC_LANG2);
    tap_code(KC_MHEN);
  }
}

void comm_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code(KC_COMM);
  }
}

void dot_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code(KC_DOT);
  } else {
    layer_off(_DVORAK);
    naginata_off();
    tap_code(KC_LANG1);
    tap_code(KC_HENK);
  }
}

void dot_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code(KC_DOT);
  }
}

typedef enum {
  SINGLE_TAP,
  SINGLE_HOLD,
  DOUBLE_TAP,
  ELSE,
} td_state_t;
static td_state_t td_state;

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) { return SINGLE_TAP; }
    else { return SINGLE_HOLD; }
  }
  if (state->count == 2) { return DOUBLE_TAP; }
  else { return ELSE; }
}

void scln_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      register_code(KC_SCLN);
      break;
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_RSFT));
      break;
    case DOUBLE_TAP:
      register_code(KC_ESC);
      break;
    case ELSE:
      break;
  }
}

void scln_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case SINGLE_TAP:
      unregister_code(KC_SCLN);
      break;
    case SINGLE_HOLD:
      unregister_mods(MOD_BIT(KC_RSFT));
      break;
    case DOUBLE_TAP:
      unregister_code(KC_ESC);
      break;
    case ELSE:
      break;
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [Q] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_ESC),
  [COMM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, comm_finished, comm_reset),
  [DOT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dot_finished, dot_reset),
  [SCLN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, scln_finished, scln_reset)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,   TD(Q),    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,SFT_T(KC_A),ALT_T(KC_S),CTL_T(KC_D),GUI_T(KC_F),KC_G,              KC_H,GUI_T(KC_J),CTL_T(KC_K),ALT_T(KC_L),TD(SCLN),KC_MINS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,TD(COMM), TD(DOT), KC_SLSH, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                      EI,LT(_LOWER,KC_SPC),  KC_TAB,    KC_BSPC,LT(_RAISE,KC_ENT),    KANA
                                      //`--------------------------'  `--------------------------'
  ),

  [_DVORAK] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
    _______,   KC_SCLN, KC_COMM,  KC_DOT,    KC_P,    KC_Y,                         KC_F,    KC_G,    KC_C,    KC_R,    KC_L, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    _______,      KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                         KC_D,    KC_H,    KC_T,    KC_N,    KC_S, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    _______,   KC_QUOT,    KC_Q,    KC_J,    KC_K,    KC_X,                         KC_B,    KC_M,    KC_W,    KC_V,    KC_Z, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_NAGINATA] = LAYOUT_split_3x6_3(
    _______,NG_Q   ,NG_W   ,NG_E   ,NG_R   ,NG_T   ,                NG_Y   ,NG_U   ,NG_I   ,NG_O   ,NG_P   ,_______, \
    _______,NG_A   ,NG_S   ,NG_D   ,NG_F   ,NG_G   ,                NG_H   ,NG_J   ,NG_K   ,NG_L   ,NG_SCLN,_______, \
    _______,NG_Z   ,NG_X   ,NG_C   ,NG_V   ,NG_B   ,                NG_N   ,NG_M   ,NG_COMM,NG_DOT ,NG_SLSH,_______, \
                                    _______,NG_SHFT,_______,_______,_______,_______
  ),

  [_LOWER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,  KC_DEL, KC_EXLM, KC_PIPE, KC_AMPR, KC_TILD,                      KC_PLUS, KC_ASTR, KC_MINS,  KC_EQL, KC_PERC, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_CIRC,  KC_DLR, KC_COLN, KC_LPRN, KC_LCBR,                      KC_RCBR, KC_RPRN, KC_LABK, KC_RABK, KC_SLSH, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, MO(_NUM)
                                      //`--------------------------'  `--------------------------'
  ),

  [_RAISE] = LAYOUT_split_3x6_3(
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  KC_DEL, KC_EXLM, KC_PIPE, KC_AMPR, KC_TILD,                      KC_PLUS,  KC_EQL, KC_MINS, KC_ASTR, KC_PERC, XXXXXXX,
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, KC_HASH, KC_UNDS,  KC_DQT, KC_QUOT,  KC_GRV,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT,  KC_ESC, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_CIRC,  KC_DLR, KC_LBRC, KC_LPRN, KC_LCBR,                      KC_RCBR, KC_RPRN, KC_RBRC, KC_BSLS,   KC_AT, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------|--------+--------+--------+--------+--------+
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  KC_F11,  KC_F12, XXXXXXX,  DVORAK,NAGINATA,                      _______, _______, _______, _______, _______, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_NUM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                      XXXXXXX,    KC_7,    KC_8,    KC_9, KC_ASTR, KC_PERC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,                      XXXXXXX,    KC_4,    KC_5,    KC_6, KC_MINS, KC_SLSH,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  KC_F11,  KC_F12, XXXXXXX, XXXXXXX, XXXXXXX,                         KC_0,    KC_1,    KC_2,    KC_3, KC_PLUS,  KC_EQL,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),
};

uint8_t layer_state_set_user(uint8_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

void matrix_init_user(void) {
  // naginata
  uint16_t ngonkeys[] = {};
  uint16_t ngoffkeys[] = {};
  set_naginata(_NAGINATA, ngonkeys, ngoffkeys);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case EI:
      if (record->event.pressed) {
        layer_off(_DVORAK);
        naginata_off();
        tap_code(KC_LANG2);
        tap_code(KC_MHEN);
      }
      return false;
      break;
    case KANA:
      if (record->event.pressed) {
        layer_off(_DVORAK);
        naginata_off();
        tap_code(KC_LANG1);
        tap_code(KC_HENK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        naginata_off();
        layer_on(_DVORAK);
        tap_code(KC_LANG2);
        tap_code(KC_MHEN);
      }
      return false;
      break;
    case NAGINATA:
      if (record->event.pressed) {
        naginata_on();
      }
      return false;
      break;
    default:
      break;
  }
  if (!process_naginata(keycode, record))
    return false;
  return true;
}
