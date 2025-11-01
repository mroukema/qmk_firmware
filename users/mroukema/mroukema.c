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

#include "mroukema.h"

#ifdef POINTING_DEVICE_ENABLE
bool set_scrolling = false;

// Variables to store accumulated scroll values
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;
#endif

void keyboard_post_init_user(void) {
    set_single_default_layer(RSTHD);
}

__attribute__ ((weak))
void pointing_device_init_keymap(void) {}

void pointing_device_init_user(void) {
    set_auto_mouse_layer(MOUSE); // only required if AUTO_MOUSE_DEFAULT_LAYER is not set to index of <mouse_layer>
    set_auto_mouse_enable(true);         // always required before the auto mouse feature will work
    pointing_device_init_keymap();
}
__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
    //process_auto_mouse(keycode, record);
    #endif
    switch (keycode) {
        #ifdef POINTING_DEVICE_ENABLE
        case DRAG_SCROLL:
            set_scrolling = record->event.pressed;
            return false;
        #endif
        case TO_DEFAULT:
            layer_clear();
            layer_move(default_layer_state);
            break;
        default:
            process_custom_shifted_keys(keycode, record);
    }
    return process_record_keymap(keycode, record);
};

#ifdef POINTING_DEVICE_ENABLE
__attribute__ ((weak))
report_mouse_t pointing_device_task_keymap(report_mouse_t mouse_report) {
    return mouse_report;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    // Check if drag scrolling is active
    if (set_scrolling) {
        // Calculate and accumulate scroll values based on mouse movement and divisors
        scroll_accumulated_h += (float)mouse_report.x / SCROLL_DIVISOR_H;
        scroll_accumulated_v += (float)mouse_report.y / SCROLL_DIVISOR_V;

        // Assign integer parts of accumulated scroll values to the mouse report
        mouse_report.h = (int8_t)scroll_accumulated_h;
        mouse_report.v = (int8_t)scroll_accumulated_v;

        // Update accumulated scroll values by subtracting the integer parts
        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

        // Clear the X and Y values of the mouse report
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return pointing_device_task_keymap(mouse_report);
}

bool is_mouse_record_user(uint16_t keycode, keyrecord_t* record) {
    switch(keycode) {
        case DRAG_SCROLL:
            return true;
        case KC_RIGHT ... KC_UP:
            return true;
        default:
            return false;
    }
}
#endif

__attribute__ ((weak))
layer_state_t layer_state_set_keymap(layer_state_t state) {
    return state;
}

// Function to handle layer changes and disable drag scrolling when not in AUTO_MOUSE_DEFAULT_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    // Disable set_scrolling if the current layer is not the AUTO_MOUSE_DEFAULT_LAYER
    #ifdef POINTING_DEVICE_ENABLE
    if (get_highest_layer(state) != MOUSE) {
        set_scrolling = false;
    }
    #endif
    return layer_state_set_keymap(state);
}

__attribute__ ((weak))
void matrix_scan_keymap(void) {}

void matrix_scan_user(void) {
    #ifdef TIMEOUT_TO_DEFAULT_LAYER
    if(get_highest_layer(default_layer_state) != get_highest_layer(layer_state)) {
        switch (get_highest_layer(layer_state)) {
            case GAMING:
                break;
            case MOUSE:
                break;
            default:
                if(last_input_activity_elapsed() > TIMEOUT_TO_DEFAULT_LAYER) {
                    layer_move(default_layer_state);
                }

        }
    }
    #endif
    matrix_scan_keymap();
}
