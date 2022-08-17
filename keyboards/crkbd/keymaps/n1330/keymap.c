#include QMK_KEYBOARD_H
#include <stdio.h>

// naginata
#include "naginata.h"
NGKEYS naginata_keys;

enum keymap_layers {
  _COLEMAKDH,
  _QWERTY,
  _NAGINATA,
  _LOWER,
  _RAISE,
  _ADJUST,
  _NUM,
};

enum custom_keycodes {
  QWERTY = NG_SAFE_RANGE,
  COLEMAKDH,
  NAGINATA,
  LOWER,
  RAISE,
  EI,
  KANA,
  ESC,
};

// QWERTY
#define MAP_A SFT_T(KC_A)
#define MAP_S ALT_T(KC_S)
#define MAP_D GUI_T(KC_D)
#define MAP_F CTL_T(KC_F)
#define MAP_J CTL_T(KC_J)
#define MAP_K GUI_T(KC_K)
#define MAP_L ALT_T(KC_L)
#define SCLN SFT_T(KC_SCLN)

//COLEMAKDH
#define MAP_R ALT_T(KC_R)
#define MAPC_S GUI_T(KC_S)
#define MAP_T CTL_T(KC_T)
#define MAP_N CTL_T(KC_N)
#define MAP_E GUI_T(KC_E)
#define MAP_I ALT_T(KC_I)
#define MAP_O SFT_T(KC_O)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAKDH] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN,  XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,   MAP_A,   MAP_R,  MAPC_S,   MAP_T,    KC_G,                         KC_M,   MAP_N,   MAP_E,   MAP_I,   MAP_O, KC_MINS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                         KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                      EI,LT(_LOWER,KC_SPC),  KC_TAB,    KC_BSPC,LT(_RAISE,KC_ENT),    KANA
                                      //`--------------------------'  `--------------------------'
  ),

  [_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,   MAP_A,   MAP_S,   MAP_D,   MAP_F,    KC_G,                         KC_H,   MAP_J,   MAP_K,   MAP_L,    SCLN, KC_MINS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                      EI,LT(_LOWER,KC_SPC),  KC_TAB,    KC_BSPC,LT(_RAISE,KC_ENT),    KANA
                                      //`--------------------------'  `--------------------------'
  ),

  [_NAGINATA] = LAYOUT_split_3x6_3(
    _______,NG_Q   ,NG_W   ,NG_E   ,NG_R   ,NG_T   ,                NG_Y   ,NG_U   ,NG_I   ,NG_O   ,NG_P   ,_______,
    _______,NG_A   ,NG_S   ,NG_D   ,NG_F   ,NG_G   ,                NG_H   ,NG_J   ,NG_K   ,NG_L   ,NG_SCLN,_______,
    _______,NG_Z   ,NG_X   ,NG_C   ,NG_V   ,NG_B   ,                NG_N   ,NG_M   ,NG_COMM,NG_DOT ,NG_SLSH,_______,
                                    _______,NG_SHFT,MO(_LOWER),_______,_______,_______
  ),

  [_LOWER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, _______,   KC_F2,   KC_F4, KC_BSPC, _______,                      _______, _______, _______, _______,_______,  XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX,  KC_ESC,  KC_DEL,  KC_ENT,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX,  QWERTY,NAGINATA,XXXXXXX,                      KC_HOME, KC_PGDN, KC_PGUP,  KC_END, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,   MO(_NUM),_______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_RAISE] = LAYOUT_split_3x6_3(
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    KC_5,    KC_3,    KC_1,    KC_9,    KC_7,                         KC_6,    KC_8,    KC_0,    KC_2,    KC_4, XXXXXXX,
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, KC_QUOT, KC_HASH, KC_UNDS, KC_LPRN, KC_RPRN,                      KC_PERC,  KC_EQL, KC_MINS, KC_ASTR, KC_PLUS, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  KC_DQT, KC_CIRC,  KC_DLR, KC_LBRC, KC_RBRC,                      KC_COLN, KC_EXLM, KC_LABK, KC_RABK, KC_SLSH, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------|--------+--------+--------+--------+--------+
                                          _______, _______, KC_BSPC,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,    KC_5,    KC_3,    KC_1,    KC_9,    KC_7,                         KC_6,    KC_8,    KC_0,    KC_2,    KC_4, XXXXXXX,
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, KC_BSLS,  KC_GRV,   KC_AT, KC_LCBR, KC_RCBR,                      KC_PERC,  KC_EQL, KC_TILD, KC_AMPR, KC_PIPE, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  KC_DQT, KC_CIRC,  KC_DLR, KC_LBRC, KC_RBRC,                      KC_COLN, KC_EXLM, KC_LABK, KC_RABK, KC_SLSH, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, KC_BSPC,    _______, _______, _______
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

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MAP_A:
    case MAP_S:
    case MAP_L:
    case SCLN:
    case MAPC_S:
    case MAP_I:
    case MAP_O:
      return TAPPING_TERM + 60;
    default:
      return TAPPING_TERM;
  }
}

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
        naginata_off();
        layer_off(_QWERTY);
        layer_on(_COLEMAKDH);
        tap_code(KC_LANG2);
        tap_code(KC_MHEN);
      }
      return false;
      break;
    case KANA:
      if (record->event.pressed) {
        layer_off(_COLEMAKDH);
        layer_on(_QWERTY);
        naginata_off();
        tap_code(KC_LANG1);
        tap_code(KC_HENK);
      }
      return false;
      break;
    case ESC:
      if (record->event.pressed) {
        register_code(KC_ESC);
        naginata_off();
        tap_code(KC_LANG2);
        tap_code(KC_MHEN);
      } else {
        unregister_code(KC_ESC);
      }
      return false;
      break;
    case COLEMAKDH:
      if (record->event.pressed) {
        naginata_off();
        layer_off(_QWERTY);
        layer_on(_COLEMAKDH);
        tap_code(KC_LANG2);
        tap_code(KC_MHEN);
      }
      return false;
      break;
    case QWERTY:
      if (record->event.pressed) {
        naginata_off();
        layer_off(_COLEMAKDH);
        layer_on(_QWERTY);
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
