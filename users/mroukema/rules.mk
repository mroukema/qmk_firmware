VPATH += 	$(USER_PATH)/defs

SRC += 		$(USER_PATH)/mroukema.c \
			$(USER_PATH)/lib/custom_keycodes.c \
			$(USER_PATH)/lib/keymap_combos.c

INTROSPECTION_KEYMAP_C = keyrecords/tap_dances.c

ifeq ($(strip $(OS_DETECTION_ENABLE)), yes)
	OPT_DEFS+=-DOS_DETECTION
endif

ifneq ($(PLATFORM),CHIBIOS)
    LTO_ENABLE = yes               # Enable link time optimization
endif
