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
float pointer_accumulated_x = 0;
float pointer_accumulated_y = 0;
#endif

__attribute__ ((weak))
void keyboard_post_init_keymap(void) {}

void keyboard_post_init_user(void) {
    // Ensure RSTHD is default layer since GAMING is placed lower in stack to allow GAMING to tap/toggle into typing layer
    set_single_default_layer(RSTHD);
    keyboard_post_init_keymap();
}

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        #ifdef POINTING_DEVICE_ENABLE
        case DRAG_SCROLL:
            set_scrolling = record->event.pressed;
            return false;
        #endif
        case TO_DEFAULT:
            layer_clear();
            layer_move(default_layer_state);
            return false;
        default:
            process_custom_shifted_keys(keycode, record);
    }
    return process_record_keymap(keycode, record);
};

#ifdef POINTING_DEVICE_ENABLE

__attribute__ ((weak))
void pointing_device_init_keymap(void) {}

void pointing_device_init_user(void) {
    // set auto mouse layer here since layer enum not available at the time AUTO_MOUSE_DEFAULT_LAYER needs to be defined (in config.h of keymap/keyboard)
    set_auto_mouse_layer(AUTO_MOUSE_LAYER);
    pointing_device_init_keymap();
}
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
    } else {
        int8_t absMouseX = abs(mouse_report.x);
        int8_t absMouseY = abs(mouse_report.y);
        if(absMouseX > 0 && absMouseX <= FINE_SCROLL_THRESHOLD) {
            pointer_accumulated_x += (float)mouse_report.x / FINE_POINTER_DIVISOR_X;

            mouse_report.x = (int8_t)pointer_accumulated_x;

            pointer_accumulated_x -= (int8_t)pointer_accumulated_x;
        }
        if(absMouseY > 0 && absMouseY <= FINE_SCROLL_THRESHOLD) {
            pointer_accumulated_y += (float)mouse_report.y / FINE_POINTER_DIVISOR_Y;

            mouse_report.y = (int8_t)pointer_accumulated_y;

            pointer_accumulated_y -= (int8_t)pointer_accumulated_y;
        }
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
    if (get_highest_layer(state) != AUTO_MOUSE_LAYER) {
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
