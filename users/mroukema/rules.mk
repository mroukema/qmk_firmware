VPATH += 	$(USER_PATH)/defs

SRC += 		$(USER_PATH)/mroukema.c \
			$(USER_PATH)/lib/custom_keycodes.c \
			$(USER_PATH)/lib/keymap_combos.c \
			$(USER_PATH)/keyrecords/tap_dances.c

ifneq ($(PLATFORM),CHIBIOS)
    LTO_ENABLE = yes               # Enable link time optimization
endif
