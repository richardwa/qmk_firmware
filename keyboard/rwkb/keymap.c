// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.

#include "rwkb.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QW 0
#define _LW 1
#define _RS 2
#define _OT 3 

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QW] = { /* Qwerty */
  {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
  {KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT },
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MT(MOD_LSFT, KC_QUOT)},
  {KC_LCTL, KC_FN2, KC_LGUI, KC_LALT, 
      KC_FN0, 
      LT(_RS, KC_SPC),  
      LT(_LW, KC_SPC),  
      //KC_FN1, 
      KC_SPC,
   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},
[_LW] = { /* LOWER */
  {KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TRNS, KC_7,    KC_8,    KC_9,    KC_TRNS, KC_TRNS},
  {KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_PLUS, KC_4,    KC_5,    KC_6,    KC_MINUS,KC_TRNS},
  {KC_TRNS, KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS, KC_ASTR, KC_1,    KC_2,    KC_3,    KC_SLSH, KC_EQL},
  {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TG(_LW), KC_TRNS, KC_TRNS, KC_0,    KC_0,    KC_DOT,  KC_COMM, KC_ESC}
},
[_RS] = { /* RAISE */
  {KC_TILD, KC_EXLM, KC_AT,   KC_HASH,   KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL},
  {KC_TRNS, KC_INS,  KC_HOME, KC_PGUP,   KC_TRNS, KC_TRNS,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_UNDS, KC_TRNS}, 
  {KC_TRNS, KC_DELETE,KC_END, KC_PGDN,   KC_TRNS, KC_TRNS,  KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_BSLS, KC_PIPE},
  {KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TG(_RS), KC_HOME, KC_PGDN, KC_PGUP, KC_END}
},
[_OT] = { /* OTHER */
  {KC_TRNS, KC_TRNS, KC_MS_U, KC_WH_U, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, M(0) },
  {KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS },
  {KC_TRNS, KC_TRNS, KC_TRNS, KC_WH_D, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS },
  {KC_TRNS, TG(_OT), KC_TRNS, KC_TRNS, KC_MS_BTN1, KC_MS_BTN2, KC_TRNS, KC_MS_BTN3, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
}
};

const uint16_t PROGMEM fn_actions[] = {
    [0]=ACTION_LAYER_TAP_TOGGLE(_LW),
    [1]=ACTION_LAYER_TAP_TOGGLE(_RS),
    [2]=ACTION_LAYER_TAP_TOGGLE(_OT)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            ledMatrixToggle();
          }
        break;
      }
    return MACRO_NONE;
};
