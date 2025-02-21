/*
This is the c configuration file for the keymap

Copyright 2023 Vicente Ortiz

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "keymap_spanish.h"
#include "macros.h"

bool is_kc_window_active = false;

enum sofle_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _QWERTY,
    _M_QWERTY,
    _GAME,
    _LOWER,
    _G_LOWER,
    _RAISE,
    _ADJUST,
};

// KC_NUBS or KC_GRV custom less than: < due to bug mac/linux not using the same key
enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_M_QWERTY,
    KC_GAME,       // toggle game layer
    KC_C_WINDOW,   // change window (alt+tab)
    KC_C_TAB,      // change tab (ctrl+tab)
    KC_C_TAB_PREV,  // change tab window prev (shift+ctrl+tab),
    KC_C_CBR,  // { and SHIFT({) = } 
    KC_C_BRK,  // [ and SHIFT([) = ]
    KC_C_PAR,  // ( and SHIFT(() = )
    KC_C_E,  // ! and SHIFT(!) = ¡
    KC_C_Q,  // ? and SHIFT(?) = ¿
    KC_C_S,  // / and SHIFT(/) = \ backslash
    KC_C_QU,  // " and SHIFT(") = '
    KC_VIRG, // ~ for wind/mac
    C_LST, // < for mac/win
    WDEL, // word delete for mac/win
    PRVWD, // previous word for mac/win
    NXTWD, // next word for mac/win
    C_HOME, // home for mac/win
    C_END, // end for mac/win
    Q_SUPER, // combo super/win
};


const uint16_t PROGMEM combo_super_left[] = {KC_R, KC_F, COMBO_END};
const uint16_t PROGMEM combo_super_right[] = {KC_U, KC_J, COMBO_END};

combo_t key_combos[] = {
    COMBO(combo_super_right, Q_SUPER),
    COMBO(combo_super_left, Q_SUPER),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, XXXXXXX,
  XXXXXXX,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                          KC_H,    KC_J,    KC_K,    KC_L,    PLUS, XXXXXXX,
  XXXXXXX,LSFT_T(KC_Z),LALT_T(KC_X),KC_C,KC_V,    KC_B, KC_MUTE,        KC_MPLY, KC_N,    KC_M, KC_COMM, KC_DOT,RSFT_T(KC_SLSH),XXXXXXX,
  XXXXXXX, XXXXXXX,LCTL_T(KC_ESC),LT(_LOWER, KC_TAB),KC_SPC, KC_ENT,LT(_RAISE, KC_BSPC),KC_DELETE,    XXXXXXX, XXXXXXX
),
[_M_QWERTY] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, XXXXXXX,
  XXXXXXX,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                          KC_H,    KC_J,    KC_K,    KC_L,    PLUS, XXXXXXX,
  XXXXXXX,LSFT_T(KC_Z), LALT_T(KC_X),  KC_C,   KC_V,   KC_B, KC_MUTE,    KC_MPLY, KC_N,    KC_M, KC_COMM, KC_DOT, RSFT_T(KC_SLSH),XXXXXXX,
  XXXXXXX, XXXXXXX,LGUI_T(KC_ESC),LT(_LOWER, KC_TAB),KC_SPC,KC_ENT,LT(_RAISE, KC_BSPC),  KC_DELETE, XXXXXXX, XXXXXXX
),
[_GAME] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0, ES_QUOT,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
  KC_LSFT,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                        KC_H,    KC_J,    KC_K,    KC_L,    PLUS, KC_RSFT,
  KC_LCTL, KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,    XXXXXXX,   KC_N,    KC_M, KC_COMM, KC_DOT, RSFT_T(KC_SLSH), KC_END,
                 KC_LGUI,KC_ENT,KC_LALT, MO(_G_LOWER), KC_SPC,      KC_ENT,  KC_BSPC, KC_DELETE, KC_RALT, KC_HOME
),
[_LOWER] = LAYOUT(
  _______, _______, _______, _______, _______ , _______,                     _______, _______, _______, _______, _______, _______,
  _______, KC_VOLU, KC_MUTE, PRV_WPC,  NXT_WPC, KC_GAME,                     S(ES_6),  KC_C_S,KC_C_PAR, S(ES_9), S(ES_0), _______,
  _______, KC_VOLD, KC_MPLY, S(KC_TAB),KC_C_WINDOW,_______,                  KC_C_E,   C_LST,KC_C_CBR,KC_C_BRK,   KC_C_Q,_______,
  _______, KC_LSFT, KC_CAPS,KC_C_TAB_PREV,KC_C_TAB,ES_GRV,_______,  _______, KC_RBRC, KC_C_QU,S(KC_COMM),S(KC_DOT),S(ES_MINS),_______,
                    _______, _______, _______, _______, _______,    _______, LT(_RAISE, KC_NO),WDEL,_______, _______
),
[_G_LOWER] = LAYOUT(
  _______,  KC_F1,   KC_F2,   KC_F3,    KC_F4 ,   KC_F5,                       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  _______, _______, KC_UP,   _______,  _______, KC_GAME,                     S(ES_6),  KC_C_S,KC_C_PAR, S(ES_9), S(ES_0),  KC_F12,
  _______, KC_LEFT, KC_DOWN, KC_RGHT,  _______, _______,                    KC_C_E,   C_LST,KC_C_CBR,KC_C_BRK,   KC_C_Q,_______,
  _______,    KC_H,    KC_I,    KC_K,     KC_L,    KC_M, _______,  _______, KC_RBRC, KC_C_QU,S(KC_COMM),S(KC_DOT),S(ES_MINS),_______,
                    _______,KC_DELETE,_______, _______, _______,    _______, LT(_RAISE, KC_NO),WDEL,_______, _______
),
[_RAISE] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______,
  _______,ALGR(ES_1),ALGR(ES_2),ALGR(ES_3),S(ES_4),S(ES_5),                 _______,   PRVWD, _______,   NXTWD, _______, _______,
  _______, _______, _______, _______, _______, _______,                     KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, _______, _______,
  _______, _______, _______, _______, _______, _______,  _______,  _______, _______,  C_HOME, _______,   C_END, _______, _______,
                    _______, _______, _______,MO(_LOWER),_______,  _______, _______, _______, _______, _______
),
[_ADJUST] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX,KC_M_QWERTY,KC_QWERTY,ALGR(ES_E),XXXXXXX,XXXXXXX,                      XXXXXXX,    KC_7,    KC_8,    KC_9,    KC_0, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX,XXXXXXX, XXXXXXX,                      XXXXXXX,    KC_4,    KC_5,    KC_6, KC_VIRG, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,    KC_1,    KC_2,    KC_3, XXXXXXX, XXXXXXX,
                    _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    // unregister mods from K_C_WINDOW and  KC_C_TAB
    if (is_kc_window_active) {
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LGUI);
        is_kc_window_active = false;
    }

    // update _ADJUST layer
    if (IS_LAYER_ON(_LOWER) || IS_LAYER_ON(_RAISE)) {
        state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    }
    return state;
}

#ifdef OLED_ENABLE

static void print_status_narrow(void) {
    // Print current mode
    oled_write_P(PSTR("\n"), false);

    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("Win"), false);
            break;
        case _M_QWERTY:
            oled_write_ln_P(PSTR("Mac"), false);
            break;
        case _GAME:
            oled_write_ln_P(PSTR("GAME"), false);
            break;
        default:
            oled_write_ln_P(PSTR(""), false);
    }
    oled_write_ln_P(PSTR("\n\n"), false);
    // Print current layer
    switch (get_highest_layer(layer_state)) {
        case _RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case _LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case _G_LOWER:
            oled_write_ln_P(PSTR("GLow"), false);
            break;
        case _ADJUST:
            oled_write_ln_P(PSTR("Adj\n"), false);
            break;
        default:
            oled_write_ln_P(PSTR(""), false);
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    }
    return false;
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Detect the activation of both Shifts
    if ((get_mods() & MOD_MASK_SHIFT) == MOD_MASK_SHIFT) {
        tap_code(KC_CAPS);
    }
    bool isWin = get_highest_layer(default_layer_state) == _QWERTY;
    switch (keycode) {
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case KC_M_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_M_QWERTY);
            }
            return false;
        case KC_GAME:{
            bool isGame = get_highest_layer(default_layer_state) == _GAME;
            if (record->event.pressed) {
                if (isGame) {
                    set_single_persistent_default_layer(_QWERTY);
                } else {
                    set_single_persistent_default_layer(_GAME);
                }
            }
            return false;
            }
        case KC_C_WINDOW:
            if (record->event.pressed) {
                if (!is_kc_window_active) {
                    is_kc_window_active = true;
                    register_code(KC_LALT);
                }
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
        case KC_C_TAB:
            if (record->event.pressed) {
                if (!is_kc_window_active) {
                    is_kc_window_active = true;
                    register_code(KC_LCTL);
                }
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
        case KC_C_TAB_PREV:
            if (record->event.pressed) {
                if (!is_kc_window_active) {
                    is_kc_window_active = true;
                    register_code(KC_LCTL);
                }
                register_code(KC_LSFT);
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
                unregister_mods(MOD_LSFT);
            }
            break;
        case KC_C_CBR:{
                bool isShifted = get_mods() & MOD_MASK_SHIFT;
                if (record->event.pressed) {
                    if(isShifted) {
                        del_mods(MOD_MASK_SHIFT);
                        register_code16(ES_RCBR);
                        register_code(KC_LSFT);
                    } else {
                        register_code16(ES_LCBR);
                    }
                } else {
                    if(isShifted) {
                        unregister_code16(ES_RCBR);
                    } else {
                        unregister_code16(ES_LCBR);
                    }
                }
                break;
            }
        case KC_C_BRK:{
                bool isShifted = get_mods() & MOD_MASK_SHIFT;
                if (record->event.pressed) {
                    if(isShifted) {
                        del_mods(MOD_MASK_SHIFT);
                        register_code16(ES_RBRC);
                        register_code(KC_LSFT);
                    } else {
                        register_code16(ES_LBRC);
                    }
                } else {
                    if(isShifted) {
                        unregister_code16(ES_RBRC);
                    } else {
                        unregister_code16(ES_LBRC);
                    }
                }
                break;
            }
        case KC_C_PAR:{
                bool isShifted = get_mods() & MOD_MASK_SHIFT;
                if (record->event.pressed) {
                    if(isShifted) {
                        del_mods(MOD_MASK_SHIFT);
                        register_code16(ES_RPRN);
                        register_code(KC_LSFT);
                    } else {
                        register_code16(ES_LPRN);
                    }
                } else {
                    if(isShifted) {
                        unregister_code16(ES_RPRN);
                    } else {
                        unregister_code16(ES_LPRN);
                    }
                }
                break;
            }
        case KC_C_E:{
                bool isShifted = get_mods() & MOD_MASK_SHIFT;
                 if (record->event.pressed) {
                    if (isShifted) {
                        del_mods(MOD_MASK_SHIFT);
                        register_code16(ES_IEXL);
                        register_code(KC_LSFT);
                    } else {
                        register_code16(ES_EXLM);
                    }
                } else {
                    if (isShifted) {
                        unregister_code16(ES_IEXL);
                    } else {
                        unregister_code16(ES_EXLM);
                    }
                }
                break;
            }
        case KC_C_Q:{
                bool isShifted = get_mods() & MOD_MASK_SHIFT;
                 if (record->event.pressed) {
                    if (isShifted) {
                        del_mods(MOD_MASK_SHIFT);
                        register_code16(ES_IQUE);
                        register_code(KC_LSFT);
                    } else {
                        register_code16(ES_QUES);
                    }
                } else {
                    if (isShifted) {
                        unregister_code16(ES_IQUE);
                    } else {
                        unregister_code16(ES_QUES);
                    }
                }
                break;
            }
        case KC_C_S:{
                bool isShifted = get_mods() & MOD_MASK_SHIFT;
                 if (record->event.pressed) {
                    if (isShifted) {
                        del_mods(MOD_MASK_SHIFT);
                        register_code16(ES_BSLS);
                        register_code(KC_LSFT);
                    } else {
                        register_code16(ES_SLSH);
                    }
                } else {
                    if (isShifted) {
                        unregister_code16(ES_BSLS);
                    } else {
                        unregister_code16(ES_SLSH);
                    }
                }
                break;
            }
       case KC_C_QU: {
                bool isShifted = get_mods() & MOD_MASK_SHIFT;
                if (record->event.pressed) {
                    if (isShifted) {
                        del_mods(MOD_MASK_SHIFT);
                        register_code16(ES_QUOT);
                        register_code(KC_LSFT);
                    } else {
                        register_code16(ES_DQUO);
                    }
                } else {
                    if (isShifted) {
                        unregister_code16(ES_QUOT);
                    } else {
                        unregister_code16(ES_DQUO);
                    }
                }
                break;
            }
        case PLUS:
            if (!record->tap.count && record->event.pressed) {
                tap_code16(ES_NTIL); // Intercept hold to send ñ
                return false;
            }
            return true;
        case KC_VIRG:
            if (record->event.pressed) {
                if (isWin) {
                    tap_code16(ALGR(KC_4));
                    tap_code(KC_SPC);
                } else {
                    tap_code16(ALGR(ES_NTIL));
                }
            }
            return true;
        case C_LST:
            if (record->event.pressed) {
                if (isWin) {
                  register_code16(KC_GRV);
                } else {
                  register_code16(KC_NUBS);
                }
            } else {
                if (isWin) {
                  unregister_code16(KC_GRV);
                } else {
                  unregister_code16(KC_NUBS);
                }
            }
            return true;
        case WDEL:
            if (record->event.pressed) {
                if (isWin) {
                    register_code16(LCTL(KC_DELETE));
                } else {
                    register_code16(LALT(KC_DELETE));
                }
            } else {
                if (isWin) {
                    unregister_code16(LCTL(KC_DELETE));
                } else {
                    unregister_code16(LALT(KC_DELETE));
                }
            }
            return true;
        case PRVWD:
            if (record->event.pressed) {
                if (isWin) {
                    register_code16(LCTL(KC_LEFT));
                } else {
                    register_code16(LALT(KC_LEFT));
                }
            } else {
                if (isWin) {
                    unregister_code16(LCTL(KC_LEFT));
                } else {
                    unregister_code16(LALT(KC_LEFT));
                }
            }
            return true;
        case NXTWD:
            if (record->event.pressed) {
                if (isWin) {
                    register_code16(LCTL(KC_RIGHT));
                } else {
                    register_code16(LALT(KC_RIGHT));
                }
            } else {
                if (isWin) {
                    unregister_code16(LCTL(KC_RIGHT));
                } else {
                    unregister_code16(LALT(KC_RIGHT));
                }
            }
            return true;
        case C_HOME:
            if (record->event.pressed) {
                if (isWin) {
                    register_code16(KC_HOME);
                } else {
                    register_code16(RCMD(KC_LEFT));
                }
            } else {
                if (isWin) {
                    unregister_code16(KC_HOME);
                } else {
                    unregister_code16(RCMD(KC_LEFT));
                }
                
            }
            return true;
        case C_END:
            if (record->event.pressed) {
                if (isWin) {
                    register_code16(KC_END);
                } else {
                    register_code16(RCMD(KC_RIGHT));
                }
            } else {
                if (isWin) {
                    unregister_code16(KC_END);
                } else {
                    unregister_code16(RCMD(KC_RIGHT));
                }
            }
            return true;
        case LT(_RAISE, KC_NO):
            if(record->tap.count && record->event.pressed) {
                if (isWin) {
                    register_code16(LCTL(KC_BSPC));
                } else {
                    register_code16(LALT(KC_BSPC));
                }
            } else {
                if (isWin) {
                    unregister_code16(LCTL(KC_BSPC));
                } else {
                    unregister_code16(LALT(KC_BSPC));
                }
            }
            return true;
        case Q_SUPER:
            if (record->event.pressed) {
                if (isWin) {
                    register_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                }
            } else {
                if (isWin) {
                    unregister_code(KC_LGUI);
                } else {
                    unregister_code(KC_LCTL);
                }
            }
            return true;
    }
    return true;
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LALT_T(KC_X):
        case LALT_T(KC_DOT):
        case PLUS:
            // Do not select the hold action when another key is pressed.
            return false;
        default:
            // Immediately select the hold action when another key is pressed.
            return true;
    }
}

bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RSFT_T(KC_SLSH):
            return true;
        default:
            return false;
    }
}

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 1) {
        if (clockwise) {
            // next track
            tap_code(KC_MNXT);
        } else {
            // previous track
            tap_code(KC_MPRV);
        }
    } else if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true;
}

#endif
