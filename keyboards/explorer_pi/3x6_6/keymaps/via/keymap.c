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

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
    //|--------------------------------------------------------------------------------------------------------------------|            |-------------------------------------------------------------------------------------------------------------------|
        KC_TAB,               KC_Q,               KC_W,               KC_E,               KC_R,               KC_T,                            KC_Y,             KC_U,                KC_I,               KC_O,               KC_P,              KC_EQUAL,
    //|------------------+------------------+-------------------+-------------------+-------------------+------------------|            |------------------+-------------------+-------------------+-------------------+-------------------+----------------|
        KC_ESC,               KC_A,               KC_S,               KC_D,               KC_F,               KC_G,                            KC_H,             KC_J,                KC_K,               KC_L,               KC_SCLN,              KC_MINUS,
    //|------------------+------------------+-------------------+-------------------+-------------------+------------------|            |------------------+-------------------+-------------------+-------------------+-------------------+----------------|
        KC_LCTL,               KC_Z,               KC_X,               KC_C,               KC_V,               KC_B,                            KC_N,             KC_M,                KC_COMM,            KC_DOT,               KC_BACKSLASH,       KC_RCTL,
    //|------------------+------------------+-------------------+-------------------+-------------------+------------------|            |------------------+-------------------+-------------------+-------------------+-------------------+----------------|
                                                  KC_LALT,           KC_LGUI,             KC_LSFT,          KC_BACKSPACE,                     KC_ENTER,           KC_SPC,              KC_DEL,             KC_RSFT
                       //|-------------------------------------------------------------------------------------------------|            |----------------------------------------------------------------------------------------|                                                                      KC_LGUI       ,     KC_LCTL       ,                                                        KC_RALT       ,     KC_RGUI
                                                                      KC_LGUI       ,     KC_LCTL       ,                                                        KC_RALT       ,     KC_RGUI
                                                            //|------------------------------------------------------------|            |----------------------------------------------------------|
    ),
    )
};
