/* Copyright 2022 Thomas Baart <thomas@splitkb.com>
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

#pragma once
#define TAPPING_TERM 245
#define TAPPING_FORCE_HOLD_PER_KEY
#define TAPPING_TOGGLE 2
#define TAPPING_TERM_PER_KEY
#define LEADER_TIMEOUT 450
#define LEADER_PER_KEY_TIMING
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define EE_HANDS
#define DEBOUNCING_DELAY 10
#define SPLIT_WATCHDOG_ENABLE

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U
#ifdef RGBLIGHT_ENABLE
#    undef RGBLIGHT_ANIMATIONS
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    define RGBLIGHT_MODE_KNIGHT
#    define RGBLIGHT_HUE_STEP  8
#    define RGBLIGHT_SAT_STEP  8
#    define RGBLIGHT_VAL_STEP  8
#    define RGBLIGHT_LIMIT_VAL 160
#    define RGBLED_NUM 20
#endif
#define SPLIT_LAYER_STATE_ENABLE
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
// EC11K encoders have a different resolution than other EC11 encoders.
// When using the default resolution of 4, if you notice your encoder skipping
// every other tick, lower the resolution to 2.
#define ENCODER_RESOLUTION 2
// If you are using an Elite C rev3 on the slave side, uncomment the lines below:
//#define SPLIT_USB_DETECT
//#define NO_USB_STARTUP_CHECK
// Allows media codes to properly register in macros and rotary encoder code
#define TAP_CODE_DELAY 10
// Allows to use either side as the master. Look at the documentation for info:
// https://docs.qmk.fm/#/config_options?id=setting-handedness
//#define EE_HANDS
// Space saving
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE

#define NO_MUSIC_MODE
#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT

