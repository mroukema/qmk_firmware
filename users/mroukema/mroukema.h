/*
Copyright 2023 @mroukema

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

#pragma once

#include<stdlib.h>
#ifdef CONSOLE
#include "print.h"
#endif
#include QMK_KEYBOARD_H

#define LAYER_ENTRY KC_TRANSPARENT

#include "keyrecords/layer_names.h"

// C Macro Magic to define custom keycode and accompanying switch statement for custom shift behaviour
#include "lib/custom_keycodes.h"

#ifdef TAP_DANCE_ENABLE
#include "keyrecords/tap_dances.h"
#endif

#ifdef COMBO_ENABLE
/*
 * https://docs.qmk.fm/#/feature_combo?id=dictionary-management
 */
#include "lib/keymap_combos.h"
#endif

#ifdef POINTING_DEVICE_ENABLE
/*
 * https://docs.qmk.fm/features/pointing_device#pointing-device
 */

#define AUTO_MOUSE_LAYER MOUSE
#define FINE_SCROLL_THRESHOLD 1
#define FINE_POINTER_DIVISOR_X 5
#define FINE_POINTER_DIVISOR_Y 5
#define SCROLL_DIVISOR_H 30.0
#define SCROLL_DIVISOR_V 30.0
#endif
