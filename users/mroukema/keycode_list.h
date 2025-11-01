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

// Define C Macros to transform .def data
#define BLANK(...)
#define CSK_TABLE(custom_key, base_key, shifted_key)                                     \
// | custom_key | - | base_key | shifted_key |                                             \

#define CSMK_TABLE(mod, custom_key, base_key, shifted_key)                               \
// | custom_key | mod | base_key | shifted_key |                                           \

// Generate data needed for custom keycodes

// Create Enum
#undef CUSTOM_KEYCODE
#undef CUSTOM_SHIFTABLE_KEYCODE
#undef CUSTOM_SHIFTABLE_MOD_KEYCODE
#define CUSTOM_KEYCODE CSK_TABLE
#define CUSTOM_SHIFTABLE_KEYCODE CSK_TABLE
#define CUSTOM_SHIFTABLE_MOD_KEYCODE CSMK_TABLE

// | Custom Keycode | Mod Key | Unshifted Key | Shifted Key |
// | -------------- | ------- | ------------- | ----------- |
#include "defs/custom_keycodes.def"

#undef CUSTOM_KEYCODE
#undef CUSTOM_SHIFTABLE_KEYCODE
#undef CUSTOM_SHIFTABLE_MOD_KEYCODE


