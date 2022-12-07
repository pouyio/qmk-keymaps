#include QMK_KEYBOARD_H
#include "keymap_spanish.h"
#include "macros.h"

bool is_kc_window_active = false;

enum combos {
  Q_SUPER,
  COMBO_LENGTH  
};

uint16_t COMBO_LEN = COMBO_LENGTH;

enum layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _QWERTY,
    _M_QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

// KC_NUBS or KC_GRV custom less than: < due to bug mac/linux not using the same key
enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_M_QWERTY,
    KC_C_WINDOW,   // change window (alt+tab)
    KC_C_TAB,      // change tab (ctrl+tab)
    KC_C_TAB_PREV,  // change tab window prev (shift+ctrl+tab),
    KC_C_CBR,  // { and SHIFT({) = } 
    KC_C_BRK,  // [ and SHIFT([) = ]
    KC_C_PAR,  // ( and SHIFT(() = )
    KC_VIRG, // ~ for wind/mac
    C_BSLS, // \ backslash for win/mac
    C_LST, // < for mac/win
    WDEL, // word delete for mac/win
    PRVWD, // previous word for mac/win
    NXTWD, // next word for mac/win
    C_HOME, // home for mac/win
    C_END, // end for mac/win
};


const uint16_t PROGMEM combo_super[] = {KC_Q, KC_W, COMBO_END};

combo_t key_combos[] = {
    [Q_SUPER] = COMBO_ACTION(combo_super),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT(
  XXXXXXX,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, XXXXXXX,
  XXXXXXX,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                          KC_H,    KC_J,    KC_K,    KC_L,    PLUS, XXXXXXX,
  XXXXXXX,LSFT_T(KC_Z),LALT_T(KC_X),KC_C,KC_V,    KC_B,                          KC_N,    KC_M, KC_COMM,LALT_T(KC_DOT),RSFT_T(KC_SLSH),XXXXXXX,
                                LCTL_T(KC_ESC),LT(_LOWER, KC_TAB),KC_SPC, KC_ENT,LT(_RAISE, KC_BSPC),KC_DELETE
),
[_M_QWERTY] = LAYOUT(
  XXXXXXX,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, XXXXXXX,
  XXXXXXX,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                          KC_H,    KC_J,    KC_K,    KC_L,    PLUS, XXXXXXX,
  XXXXXXX,LSFT_T(KC_Z),LALT_T(KC_X),  KC_C,   KC_V,   KC_B,                      KC_N,    KC_M, KC_COMM,LALT_T(KC_DOT), RSFT_T(KC_SLSH),XXXXXXX,
                       LGUI_T(KC_ESC),LT(_LOWER, KC_TAB),KC_SPC,KC_ENT,LT(_RAISE, KC_BSPC),  KC_DELETE
),
[_LOWER] = LAYOUT(
  _______, KC_VOLU, KC_MUTE, PRV_WPC,  NXT_WPC, _______,                     S(ES_6), S(ES_7),KC_C_PAR, S(ES_9), S(ES_0), _______,
  _______, KC_VOLD, KC_MPLY, _______,KC_C_WINDOW,ES_QUOT,                    S(ES_1),   C_LST,KC_C_CBR,KC_C_BRK,S(ES_QUOT),_______,
  _______, KC_LSFT, _______,KC_C_TAB_PREV,KC_C_TAB,ES_GRV,                   KC_RBRC, S(ES_2),S(KC_COMM),S(KC_DOT),S(ES_MINS),_______,
                                      _______, _______, _______,    _______, LT(_RAISE, KC_NO),WDEL
),
[_RAISE] = LAYOUT(
  _______,ALGR(ES_1),ALGR(ES_2),ALGR(ES_3),S(ES_4),S(ES_5),                 _______,   PRVWD,   KC_UP,   NXTWD, _______, _______,
  _______, _______, _______, _______, _______, _______,                     _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
  _______, _______, _______, _______, _______, _______,                     _______,  C_HOME, _______,   C_END, _______, _______,
                             _______,MO(_LOWER),_______,  _______, _______, _______
),
[_ADJUST] = LAYOUT(
  XXXXXXX, KC_EQL,KC_QWERTY,ALGR(ES_E),XXXXXXX,KC_PLUS,                      XXXXXXX,    KC_7,    KC_8,    KC_9,    KC_0, XXXXXXX,
  XXXXXXX, C_BSLS,KC_M_QWERTY,XXXXXXX,XXXXXXX, XXXXXXX,                      XXXXXXX,    KC_4,    KC_5,    KC_6, KC_VIRG, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,    KC_1,    KC_2,    KC_3, XXXXXXX, XXXXXXX,
                                      _______, _______, _______,    _______, _______, _______
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
        case C_BSLS:
            if (record->event.pressed) {
                if (isWin) {
                    register_code16(ALGR(ES_MORD));
                } else {
                    // not working
                    register_code16(LALT(KC_GRV));
                }
            } else {
                if (isWin) {
                    unregister_code16(ALGR(ES_MORD));
                } else {
                    unregister_code16(LALT(KC_GRV));
                }
            }
            return true;
        case C_LST:
            if (record->event.pressed) {
                if (isWin) {
                    register_code16(KC_NUBS);
                } else {
                    register_code16(KC_GRV);
                }
            } else {
                if (isWin) {
                    unregister_code16(KC_NUBS);
                } else {
                    unregister_code16(KC_GRV);
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
    }
    return true;
}

void process_combo_event(uint16_t combo_index, bool pressed) {
  bool isWin = get_highest_layer(default_layer_state) == _QWERTY;
  switch(combo_index) {
    case Q_SUPER:
      if (pressed) {
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
      break;
  }
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
