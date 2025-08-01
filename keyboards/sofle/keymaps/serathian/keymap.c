// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "wpm.h"
#include "process_unicode.h"

enum sofle_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _QWERTY,
    _COLEMAK,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum unicode_names {
    A_UML,
    A_UML_UPPER,
    O_UML,
    O_UML_UPPER
};

const uint32_t PROGMEM unicode_map[] = {
    [A_UML] = 0x00E4, // ä
    [A_UML_UPPER] = 0x00C4, // Ä
    [O_UML] = 0x00F6, // ö
    [O_UML_UPPER] = 0x00D6, // Ö
};

// Layout change
#define KC_QWERTY PDF(_QWERTY)
#define KC_COLEMAK PDF(_COLEMAK)

// Unicode keycodes
#define KC_A_UML UP(A_UML, A_UML_UPPER)
#define KC_O_UML UP(O_UML, O_UML_UPPER)

// Navigation keycodes
#define KC_PRVWD LALT(KC_LEFT)
#define KC_NXTWD LALT(KC_RIGHT)
#define KC_LSTRT LCTL(KC_LEFT)
#define KC_LEND LCTL(KC_RIGHT)

#define LT_LOWER LT(_LOWER, KC_ESC) // LT for Lower layer with Escape
#define LT_RAISE LT(_RAISE, KC_BSPC) // LT for Raise layer with Backspace
#define LT_LGUI MT(MOD_LGUI, KC_TAB) // MT for Left GUI with Tab
#define LT_RGUI MT(MOD_RGUI, KC_SEMICOLON) // MT for Right GUI with Enter

// Aerospace keycodes
#define AS_TOG LAG(KC_TAB) // Nav Toggle
#define AS_H LAG(KC_H) // Nav Left
#define AS_J LAG(KC_J) // Nav Down
#define AS_K LAG(KC_K) // Nav Up
#define AS_L LAG(KC_L) // Nav Right

#define AS_M_H LSAG(KC_H) // Move (Join*) Left
#define AS_M_J LSAG(KC_J) // Move (Join*) Down
#define AS_M_K LSAG(KC_K) // Move (Join*) Up
#define AS_M_L LSAG(KC_L) // Move (Join*) Right
#define AS_SER LSAG(KC_DOT) // *Service Mode

#define AS_L_H LAG(KC_DOT) // Layout Horizontal
#define AS_L_V LAG(KC_COMM) // Layout Vertical
#define AS_T_N OS_LAG // Navigate
#define AS_T_M OS_LSAG // Move

// Aerospace lay-taps
#define AS_SPC LAG_T(KC_SPC) // Navigate 


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[_QWERTY] = LAYOUT(
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_GRV,
  KC_ESC,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_BSPC,
  KC_TAB,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,     XXXXXXX,KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT,
                 KC_LCTL,KC_LALT,KC_LGUI, MO(_LOWER), KC_ENT,      KC_SPC,  MO(_RAISE), KC_RGUI, KC_RALT, KC_RCTL
),
/*
 * COLEMAK
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   F  |   P  |   G  |                    |   J  |   L  |   U  |   Y  |   ;  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |   A  |   R  |   S  |   T  |   D  |-------.    ,-------|   H  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   K  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[_COLEMAK] = LAYOUT(
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_GRV,
  KC_ESC,LSFT_T(KC_Q),LCTL_T(KC_W),LALT_T(KC_F),LGUI_T(KC_P),KC_G,                      KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN,  KC_BSPC,
  KC_TAB,   KC_A,   KC_R,    KC_S,    KC_T,    KC_D,                      KC_H,    KC_N,    KC_E,    KC_I,    KC_O,  KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,      XXXXXXX,KC_K,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT,
                KC_LCTL,KC_LALT, KC_LGUI,LT_LOWER, KC_ENT,        AS_SPC, LT_RAISE, KC_RGUI, KC_RALT, KC_RCTL
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  `   | KC_1 | KC_2 | KC_3 | KC_4 | KC_5 |                    | LC_U |   $  |   ^  | LC_I | LC_O | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  | KC_6 | KC_7 | KC_8 | KC_9 | KC_0 |-------.    ,-------| LC_D |   {  |   }  |   <  |   >  |  ~   |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * | Shift|  =   |  -   |   [  |   ]  |   :  |-------|    |-------|   %  |   (  |   )  |  @   |   |  | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_LOWER] = LAYOUT(
  _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
   KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       RCTL(KC_U),KC_DLR,KC_CIRC,RCTL(KC_I),RCTL(KC_O),  KC_F12,
  _______,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                       RCTL(KC_D), KC_LCBR, KC_RCBR, KC_LABK, KC_RABK, KC_TILD,
  _______,  KC_EQL, KC_MINS, KC_LBRC, KC_RBRC, KC_COLN, _______,       _______, KC_PERC, KC_LPRN, KC_RPRN, KC_AT, KC_PIPE, _______,
                       _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______
),
/* RAISE
 * ,----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |AS_L_H|AS_L_V|      |      |                    |      | PWrd |  Up  | NWrd | DLine| Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |AS_TOG| AS_H | AS_J | AS_K | AS_L |      |-------.    ,-------|      | Left | Down | Right|  Del | Bspc |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |      |AS_M_H|AS_M_J|AS_M_K|AS_M_L|AS_SER|-------|    |-------|      | LStr | Caps | LEnd |      | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_RAISE] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                           _______,  _______, _______, _______ ,  _______ ,_______,
  _______,  AS_T_N,  AS_L_H,  AS_L_V,  AS_T_M, XXXXXXX,                           KC_PGUP, KC_PRVWD,   KC_UP, KC_NXTWD,C(KC_BSPC),KC_BSPC,
   AS_TOG,    AS_H,    AS_J,    AS_K,    AS_L, XXXXXXX,                           KC_PGDN,  KC_LEFT, KC_DOWN,  KC_RGHT,    KC_DEL,KC_BSPC,
  _______,  AS_M_H,  AS_M_J,  AS_M_K,  AS_M_L,  AS_SER, _______,        _______,  XXXXXXX, KC_LSTRT, KC_CAPS, KC_LEND,   XXXXXXX, _______,
                        _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
*  |QK_BOOT|   |QWERTY|COLEMAK|UC_NEXT|      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  ä   |      |      |      |      |-------.    ,-------|      | VOLDO| MUTE | VOLUP|  ö   |      |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      | PREV | PLAY | NEXT |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
  [_ADJUST] = LAYOUT(
  QK_BOOT , XXXXXXX,KC_QWERTY,KC_COLEMAK, UC_NEXT, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX , XXXXXXX,  XXXXXXX ,  XXXXXXX , XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX ,KC_A_UML, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,                     XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, KC_O_UML, XXXXXXX,
   _______, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,  XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, _______,
                   _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

void print_status(void) {
    // Row 0: Mode
    oled_set_cursor(0, 1);
    oled_write_P(PSTR("MODE"), false);

    oled_set_cursor(0, 2);
    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:  oled_write_P(PSTR("qwrt"), false); break;
        case _COLEMAK: oled_write_P(PSTR("clmk"), false); break;
        default:       oled_write_P(PSTR("unkn"), false); break;
    }

    // Row 2: Unicode input mode
    oled_set_cursor(0, 3);
    switch (get_unicode_input_mode()) {
        case UNICODE_MODE_MACOS:     oled_write_P(PSTR("mac "), false); break;
        case UNICODE_MODE_WINCOMPOSE: oled_write_P(PSTR("winC"), false); break;
        default:                      oled_write_P(PSTR("unkn"), false); break;
    }

    // Row 3: Layer
    oled_set_cursor(0, 5);
    oled_write_P(PSTR("LAYER"), false);

    oled_set_cursor(0, 6);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
        case _COLEMAK: oled_write_P(PSTR("base "), false); break;
        case _LOWER:   oled_write_P(PSTR("lower"), false); break;
        case _RAISE:   oled_write_P(PSTR("raise"), false); break;
        case _ADJUST:  oled_write_P(PSTR("adjst"), false); break;
        default:       oled_write_P(PSTR("undef"), false); break;
    }

    // Row 5: Caps Lock
    oled_set_cursor(0, 8);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_P(PSTR("CAPS"), false);

    oled_set_cursor(0, 9);
    oled_write_P(led_usb_state.caps_lock ? PSTR("ON ") : PSTR("off"), false);
}

void render_mod_status(void) {
    uint8_t mods = get_mods() | get_oneshot_mods();   // include oneshot mods

    oled_set_cursor(0, 0);
    oled_write_P(PSTR("MODS"), false);

    oled_set_cursor(0, 1);
    oled_write_P((mods & MOD_MASK_CTRL) ? PSTR("-CTL") : PSTR("    "), false);

    oled_set_cursor(0, 2);
    oled_write_P((mods & MOD_MASK_ALT) ? PSTR("-ALT") : PSTR("    "), false);

    oled_set_cursor(0, 3);
    oled_write_P((mods & MOD_MASK_GUI) ? PSTR("-CMD") : PSTR("    "), false);

    oled_set_cursor(0, 4);
    oled_write_P((mods & MOD_MASK_SHIFT) ? PSTR("-SFT") : PSTR("    "), false);

    oled_set_cursor(0, 6);
    oled_write_P(PSTR("OSL:"), false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status();
    } else {
        render_mod_status();
    }
    return false;
}
