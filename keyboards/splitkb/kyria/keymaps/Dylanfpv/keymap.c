
 /* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "keymap_uk.h"
#include "animations.c"
#include "layeroled.c"
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;
uint8_t selected_anim = 0;
// Layers
enum layers {
    _COLEMAK = 0,
    _GAME,
    _NUM,
    _MEDIA,
};

// Tap dances
enum {
  TD_LP = 0,
  TD_RP,
  TD_MINS,
  TD_EQL,
  TD_GAME,
};
// Aliases
#define GAME    TO(_GAME)
#define NUM     MO(_NUM)
#define MEDIATAB LT(_MEDIA, KC_TAB)

// Tap dance configs
void td_lp (tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    SEND_STRING("(");
  } else if (state->count == 2) {
    SEND_STRING("{");
  } else if (state->count == 3) {
    SEND_STRING("[");
  }
}
void td_rp (tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    SEND_STRING(")");
  } else if (state->count == 2) {
    SEND_STRING("}");
  } else if (state->count == 3) {
    SEND_STRING("]");
  }
}

tap_dance_action_t tap_dance_actions[] = {
  [TD_LP] = ACTION_TAP_DANCE_FN_ADVANCED( NULL, NULL, td_lp),
  [TD_RP] = ACTION_TAP_DANCE_FN_ADVANCED( NULL, NULL, td_rp),
  [TD_MINS] = ACTION_TAP_DANCE_DOUBLE(UK_MINS, UK_UNDS),
  [TD_EQL] = ACTION_TAP_DANCE_DOUBLE(UK_EQL, UK_PLUS),
  [TD_GAME] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_ENT, _GAME),
};
// Tapping term config
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LSFT_T(UK_T):
      return TAPPING_TERM - 105;
    case LSFT_T(UK_7):
      return TAPPING_TERM - 85;
    case LSFT_T(UK_4):
      return TAPPING_TERM - 85;
    case LSFT_T(UK_N):
      return TAPPING_TERM - 105;
    case TD_LP:
      return TAPPING_TERM + 50;
    case TD_RP:
      return TAPPING_TERM + 50;
    case TD_MINS:
      return TAPPING_TERM + 50;
    case TD_EQL:
      return TAPPING_TERM + 50;
    default:
      return TAPPING_TERM;
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * Base Layer: Colemak
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |   ESC  |   Q  |   W  |   F  |   P  |   G  |                              |   J  |   L  |   U  |   Y  | ;  : |  BSPC  |
 * |--------+------+-----+------+------+------|                              |------+------+------+------+------+--------|
 * |  MTAB  |   A  |   R  |  S   |   T  |   D  |                              |   H  |   N  |   E  |   I  |   O  |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |  LSFT  |   Z  |   X  |   C  |   V  |   B  |SPACE |CTRLE |  | ALT  | BSPC |   K  |   M  | ,  < | . >  | /  ? |  RSFT  |
 * `----------------------+------+------+------+      +------|  |------+      +------+------+------+----------------------'
 *                        |      |  (   |  NUM |      | CTRL |  | ENT  |      | LEAD |  )   | GAME |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_COLEMAK] = LAYOUT(
         KC_ESC,         UK_Q,          UK_W,          UK_F,          UK_P,      UK_G,                                              UK_J,         UK_L,         UK_U,         UK_Y,      UK_SCLN,     XXXXXXX,
       MEDIATAB, LGUI_T(UK_A),  LALT_T(UK_R),  LCTL_T(UK_S),  LSFT_T(UK_T),      UK_D,                                              UK_H, RSFT_T(UK_N), RCTL_T(UK_E), LALT_T(UK_I), LGUI_T(UK_O),     KC_QUOT,
        KC_LSFT,         UK_Z,          UK_X,          UK_C,          UK_V,      UK_B, XXXXXXX,  C(UK_E), KC_LALT,  XXXXXXX,        UK_K,         UK_M,      UK_COMM,       UK_DOT,      UK_SLSH,     KC_RSFT,
                                     KC_MPLY,    TD(TD_LP) ,           NUM,             KC_SPC, KC_LCTL,  MT(MOD_LCTL,KC_ENT),  KC_BSPC,   QK_LEAD,     TD(TD_RP), TD(TD_GAME)
    ),




/*
 * Num Layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  ESC   |  !   |  "   |  £   |  $   |  %   |                              |  ^   |  &   |  *   |  -   |  =   |  BSPC  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |    `   |  1   |  2   |  3   |  4   |  5   |                              |  6   |  7   |  8   |  9   |  0   |   #    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |    \   | LEFT |  UP  | DOWN | RGHT |      | SPC  |      |  |      |      |      |      |  ,   |  .   |  /   |        |
 * `----------------------+------+------+------+      +------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |  ENT | BSPC |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NUM] = LAYOUT(
       KC_ESC,  UK_EXLM,  UK_DQUO,  UK_PND,          UK_DLR ,    UK_PERC,                                      UK_CIRC,         UK_AMPR, UK_ASTR, TD(TD_MINS), TD(TD_EQL),  XXXXXXX,
       UK_GRV,     UK_1,     UK_2,    UK_3,     LSFT_T(UK_4),       UK_5,                                         UK_6,    LSFT_T(UK_7),    UK_8,        UK_9,       UK_0,  UK_HASH,
       UK_BSLS, KC_LEFT,    KC_UP,    KC_DOWN,    KC_RGHT,    _______, XXXXXXX, _______, _______, XXXXXXX, _______,         C(KC_LEFT),    UK_COMM,       UK_DOT,    C(KC_RGHT),  _______,
                                   _______,          _______,     _______,  KC_SPC, _______,  KC_ENT, KC_BSPC, _______,         _______, _______
    ),


/*
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      | VolUp|      |      |                              |      |      |      |      |      |  BSPC  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      | Prev | Play | Next |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      | VolDn| Mute |      |  SPC |      |  |      | BSPC |      |      |      |      |      |        |
 * `----------------------+------+------+------+      +------|  |------+      +------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      | NUM  |      |      |  |  ENT |      |MEDIA |      |      |
 *                       `----------------------------------'  `----------------------------------'
 */
    [_MEDIA] = LAYOUT(
     _______, _______, _______, KC_VOLU, _______,  _______,                                        _______,     RGB_VAI, RGB_SAI, RGB_MOD, _______, _______,
     _______, _______, KC_MPRV, KC_MPLY, KC_MNXT,  _______,                                        _______,     RGB_HUD, RGB_TOG, RGB_HUI, _______, _______,
     _______, _______, _______, KC_VOLD, KC_MUTE,  _______, XXXXXXX, _______, _______, XXXXXXX,    _______,     RGB_VAD, RGB_SAD, RGB_RMOD,  _______, _______,
                                _______, _______,      NUM,  KC_SPC, _______,  KC_ENT, KC_BSPC,    _______,     _______, _______
    ),

/*
 * Game Layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |   ESC  |      |   Q  |   W  |   E  |   R  |                              |  T   |      |      |      |      |  BSPC  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  MTAB  |      |   A  |   S  |   D  |   F  |                              |  G   |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift | LSFT |   Z  |   X  |   C  |   V  |Space |  ALT |  |      | BSPC |  B   |      |      |      |      |        |
 * `----------------------+------+------+------+      +------|  |------+      +------+------+------+----------------------'
 *                        |      |      | NUM  |      | CTRL |  |  ENT |      |      |      | GAME |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_GAME] = LAYOUT(
        KC_ESC, _______, UK_Q,    UK_W,     UK_E,    UK_R,                                        UK_T, UK_Y, UK_U, UK_I, UK_O,  UK_P,
      MEDIATAB, _______, UK_A,    UK_S,    UK_D,    UK_F,                                        UK_G, UK_H, UK_J, UK_K, UK_L,  UK_SCLN,
       KC_LSFT, KC_LSFT, UK_Z,    UK_X,    UK_C,    UK_V, XXXXXXX, KC_LALT, _______, XXXXXXX,    UK_B, UK_N,  UK_M, _______, _______,  _______,
                               _______, _______,     NUM,  KC_SPC, KC_LCTL,  KC_ENT, KC_BSPC, _______, _______,    TO(_COLEMAK)
    ),
// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};
void leader_start_user(void) {
    // Do something when the leader key is pressed
}

void leader_end_user(void) {
    if (leader_sequence_one_key(KC_C)) {
      // LaTex compile
      register_code(KC_LSFT);
      register_code(KC_F10);
      unregister_code(KC_F10);
      unregister_code(KC_LSFT);
    } else if (leader_sequence_two_keys(KC_L, KC_F)) {
      // Sends a latex fraction
      SEND_STRING(SS_TAP(X_NUBS) "frac{}{}" SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT));
    } else if (leader_sequence_two_keys(KC_L, KC_P)) {
      // Sends a latex partial fraction
      SEND_STRING(SS_TAP(X_NUBS) "frac{"SS_TAP(X_NUBS) "partial }{"SS_TAP(X_NUBS) "partial }" SS_LCTL(SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)));
    } else if (leader_sequence_two_keys(KC_G, KC_P)) {
      // Git commit and push on obsidian
      SEND_STRING(SS_LCTL(SS_LALT("c")) SS_LCTL(SS_LALT("u")));
    } else if (leader_sequence_two_keys(KC_F, KC_K)) {
      // build kyria firmware with handness
      SEND_STRING("cd qmk_firmware");
      register_code(KC_ENT);
      unregister_code(KC_ENT);
      SEND_STRING("make splitkb/kyria/rev1:Dylanfpv:uf2-split-left CONVERT_TO=KB2040 ");
    }
}

void matrix_scan_user(void) {
  // Timer for encoder alt tabbing
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1250) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}


// oled rotation
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}
static void animation_selection(void){
    if (selected_anim == 1){
        render_animation();
    }else if(selected_anim ==2){
        render_wave();
    }else{
        render_kanagawa();
    }
}
// render northstar logo
bool oled_task_user(void) {
    switch (get_highest_layer(layer_state)) {
        case _COLEMAK:
            if (!is_keyboard_master()){
                render_colemak_oled();
            }else{
                animation_selection();
            }
            return false;
            break;
        case _GAME:
            if (!is_keyboard_master()){
                render_game_oled();
            }else{
                animation_selection();
            }
            return false;
            break;
        case _NUM:
            if (!is_keyboard_master()){
                render_num_oled();
            }else{
                animation_selection();
            }
            return false;
            break;
        case _MEDIA:
            if (!is_keyboard_master()){
                render_media_oled();
            }else{
                animation_selection();
            }
            return false;
            break;
}
return false;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
      switch (get_highest_layer(layer_state)) {
          case _MEDIA:
           if (!clockwise && selected_anim  < 10) {
              selected_anim ++;
           } else if (clockwise && selected_anim  > 0){
              selected_anim --;
           }
        return false;
        break;
        default:
          if (clockwise) {
              tap_code(KC_VOLD);
          } else {
              tap_code(KC_VOLU);
          }
      }
    } else if (index == 1) { /* Second encoder */
        switch (get_highest_layer(layer_state)) {
        case _NUM:
            if (clockwise) {
            if (!is_alt_tab_active) {
            is_alt_tab_active = true;
            register_code(KC_LALT);
            }
            alt_tab_timer = timer_read();
            tap_code16(S(KC_TAB));
            } else {
            if (!is_alt_tab_active) {
            is_alt_tab_active = true;
            register_code(KC_LALT);
            }
            alt_tab_timer = timer_read();
            tap_code16(KC_TAB);
            }
            break;
        case _MEDIA:
            if (clockwise) {
                tap_code16(S(KC_LEFT));
            } else {
                tap_code16(S(KC_RGHT));
            }
          return false;
          break;
        default:
            if (clockwise) {
                tap_code(KC_MPRV);
            } else {
                tap_code(KC_MNXT);
            }
        }

    }
    return false;
}
