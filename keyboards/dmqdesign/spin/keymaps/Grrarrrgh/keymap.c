#include QMK_KEYBOARD_H

// Sources and thanks
// OLED taken from u/Nik005566 https://github.com/kalinstanchev/qmk_firmware/tree/master/keyboards/dmqdesign/spin/keymaps/gorbachev
// Layer switching via encoder based on posts by u/SpaceBarRacecar and u/Klathmon
// Photoshop opacity encoder modified from u/AlonTzarfi https://github.com/AlonTzarafi/qmk_firmware_for_alon_keebs/blob/alon-sol2/keyboards/rgbkb/sol/keymaps/alon/keymap.c

enum layers {
    _NUMPAD,	//	This is a standard Numberpad layer
    _PS,		//	This is the Photoshop layer
	_PSDPAD,	//	This is the arrows - merge into other PS layer if possible
	_RGB,		//	This is the RGB control layer
	_D2			//	This is the Destiny 2 layer, for lazy Guardians which doesn't exist yet becasue macros are hard
};

#define HIGHEST_LAYER _D2 // When adding a new layer or chaing their order make sure this is updated



// Adobe Photoshop shortcuts
#define	UNDO	LCTL(KC_Z)
#define	NXTDOC	LCTL(KC_TAB)

// Macro declarations
enum {
	SPARROW,
	ORBIT,
	CLICK,
	DISMANTLE,
};
	
// Macro definitions
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case SPARROW:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_TAB));
        _delay_ms(200);
        SEND_STRING(SS_TAP(X_E));
        return false;
      }
	  break;
	case ORBIT:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_TAB));
        _delay_ms(200);
        SEND_STRING(SS_DOWN(X_O));
		_delay_ms(5000);
		SEND_STRING(SS_UP(X_O));
        return false;
      }
  }
  return true;
};

//tap dance quad functuion
typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP, // Send two single taps
    TRIPLE_TAP,
    TRIPLE_HOLD
};

// Tap Dance declarations - See bottom of file for definitions and quad function dances
enum {
    TD_A_I,
	TD_N_G,
	TD_X_C,
	TD_V_D,
	TD_F_R,
	TD_S_E,
	TD_P_K,
	TD_L_Z,
	TD_ENT_BSPACE,
};

uint8_t cur_dance(qk_tap_dance_state_t *state);

// For the complex 'x' tap dance. Put it here so it can be used in any keymap
void TD_A_I_finished(qk_tap_dance_state_t *state, void *user_data);
void TD_A_I_reset(qk_tap_dance_state_t *state, void *user_data);

void TD_N_G_finished(qk_tap_dance_state_t *state, void *user_data);
void TD_N_G_reset(qk_tap_dance_state_t *state, void *user_data);

void TD_X_C_finished(qk_tap_dance_state_t *state, void *user_data);
void TD_X_C_reset(qk_tap_dance_state_t *state, void *user_data);

void TD_V_D_finished(qk_tap_dance_state_t *state, void *user_data);
void TD_V_D_reset(qk_tap_dance_state_t *state, void *user_data);

void TD_F_R_finished(qk_tap_dance_state_t *state, void *user_data);
void TD_F_R_reset(qk_tap_dance_state_t *state, void *user_data);

void TD_S_E_finished(qk_tap_dance_state_t *state, void *user_data);
void TD_S_E_reset(qk_tap_dance_state_t *state, void *user_data);

void TD_P_K_finished(qk_tap_dance_state_t *state, void *user_data);
void TD_P_K_reset(qk_tap_dance_state_t *state, void *user_data);

void TD_L_Z_finished(qk_tap_dance_state_t *state, void *user_data);
void TD_L_Z_reset(qk_tap_dance_state_t *state, void *user_data);

void TD_ENT_BSPACE_finished(qk_tap_dance_state_t *state, void *user_data);
void TD_ENT_BSPACE_reset(qk_tap_dance_state_t *state, void *user_data);
// End of tap dance declarations (further code for quad funtions at bottom of keymap search for 'quad function tap dance')

// These are the layer layouts
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// _NUMPAD keymap
// .--------------------------------.
// |		   |		  |			|
// |   Mute	   |   Reset  |  To PS  |
// |		   |		  |			|
// |--------------------------------|
// |		|		|		|		|
// |	7	|	8	|	9	|	0	|
// |		|		|		|		|
// |--------+-------+-------+-------|
// |		|		|		|		|
// |	4	|	5	|	6	|	.	|
// |		|		|		|		|
// |--------+-------+-------+-------|
// |		|		|		|		|
// |	1	|	2	|	3	|   Ent |
// |		|		|		|		|
//  -------------------------------- 
    [_NUMPAD] = LAYOUT(/* Base */
                KC_AUDIO_MUTE, RESET, TO(_PS),
                KC_7, KC_8, KC_9, KC_0,
                KC_4, KC_5, KC_6, KC_DOT,
                KC_1, KC_2, KC_3, KC_ENT
                ),

// _PS keymap
// .--------------------------------.
// |		   |		  |			|
// |   	Esc    | Next Doc |	Numpad  |
// |		   |		  |			|
// |--------------------------------|
// |		|		|		|		|
// |   A I	|  N G	|  X C	|  V D	|
// |		|		|		|		|
// |--------+-------+-------+-------|
// |		|		|		|		|
// |   F R	|  S E	|  P K	|  L Z	|
// |		|		|		|		|
// |--------+-------+-------+-------|
// |		|		|		|	ENT	|
// |  SHFT	|  CTRL	|  ALT	|  BSPC	|
// |		|		|		|	SPC	|
//  -------------------------------- 
    [_PS] = LAYOUT(/* Base */
				KC_ESC, NXTDOC, TO(_NUMPAD),
				TD(TD_A_I), TD(TD_N_G), TD(TD_X_C), TD(TD_V_D),
				TD(TD_F_R), TD(TD_S_E), TD(TD_P_K), TD(TD_L_Z),
				KC_LSHIFT, KC_LCTL, KC_LALT, TD(TD_ENT_BSPACE)
                ),
				
// _PSDPAD keymap
// .--------------------------------.
// |		   |		  |			|
// |   	Esc    | Next Doc |	_PS		|
// |		   |		  |			|
// |--------------------------------|
// |		|		|		|		|
// |    	|   	|  UP	|	  	|
// |		|		|		|		|
// |--------+-------+-------+-------|
// |		|		|		|		|
// |  		| LEFT	| DOWN	| RIGHT	|
// |		|		|		|		|
// |--------+-------+-------+-------|
// |		|		|		|	ENT	|
// |  SHFT	|  CTRL	|  ALT	|  BSPC	|
// |		|		|		|	SPC	|
//  -------------------------------- 
	[_PSDPAD] = LAYOUT(/* Base */
                KC_ESC, NXTDOC, TO(_PS),
				KC_NO, KC_NO, KC_UP, KC_NO,
				KC_NO, KC_LEFT, KC_DOWN, KC_RIGHT,
				KC_LSHIFT, KC_LCTL, KC_LALT, TD(TD_ENT_BSPACE)
                ),
				
				// _RGB keymap
// .--------------------------------.
// |		   |		  |			|
// |   	 	   |   		  |		    |
// |		   |		  |			|
// |--------------------------------|
// |		|		|		|		|
// |  +Hue	|  +Sat	|+Bright|Nxt RGB|
// |		|		|		|		|
// |--------+-------+-------+-------|
// |		|		|		|		|
// |  -Hue	|  -Sat	|-Bright|Prv RGB|
// |		|		|		|		|
// |--------+-------+-------+-------|
// |		|		|		|		|
// | Numpad	|   PS	| Reset	|Tog RGB|
// |		|		|		|		|
//  -------------------------------- 

    [_RGB] = LAYOUT(/* Base */
				KC_TRNS, KC_TRNS, KC_TRNS,
				RGB_HUI, RGB_SAI, RGB_VAI, RGB_MOD,
				RGB_HUD, RGB_SAD, RGB_VAD, RGB_RMOD,
				TO(_NUMPAD), TO(_PS), RESET, RGB_TOG
                ),
				
	[_D2] = LAYOUT(/* Base */
                KC_AUDIO_MUTE, KC_NO, KC_NO,
                KC_NO, KC_NO, SPARROW, ORBIT,
                KC_NO, KC_NO, KC_NO, KC_NO,
                KC_NO, KC_NO, KC_NO, KC_NO
                )

};



// These rows deal with the rotary encoders
uint8_t selected_layer = 0;
// For Photoshop Opacity control
uint8_t opacity = 60;
uint8_t opacity_increment = 3;
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
                if (clockwise && !layer_state_is(_PS)) {
                    tap_code(KC_VOLU); //  Volume Up
				} else if (clockwise && layer_state_is(_PS)) {
					tap_code(KC_RBRACKET);
				} else if (!clockwise && !layer_state_is(_PS)) {
					tap_code(KC_VOLD);
                } else if (!clockwise && layer_state_is(_PS)) {
                    tap_code(KC_LBRACKET);
                }
    } else if (index == 1) { /* Second encoder */
        switch (get_highest_layer(layer_state)) {
            case _NUMPAD:
                if (clockwise) {
                    tap_code(KC_MS_WH_DOWN); // Scroll vertical
                } else {
                    tap_code(KC_MS_WH_UP);
                }
                break;
            case _RGB:
                if (clockwise) {
                    tap_code(KC_MS_WH_DOWN);
                } else {
                    tap_code(KC_MS_WH_UP);
                }
                break;
            case _PS:
                if (clockwise) {
                    if (opacity > 100 - opacity_increment) {
                        opacity = 100;
                    } else {
                        opacity += opacity_increment;
                    }
                } else {
                    if (opacity < 0 + opacity_increment) {
                        opacity = 0;
                    } else {
                        opacity -= opacity_increment;
                    }
                }
                
                uint8_t opacity_to_type = opacity;
                if (opacity_to_type == 0) {
                    opacity_to_type = 1;
                }
                
                uint8_t last = opacity_to_type % 10;
                uint8_t first = opacity_to_type / 10 % 10;
                uint8_t digits[2] = {first, last};
                for(int i = 0; i < 2; ++i) {
                    switch (digits[i]) {
                    case 0: tap_code(KC_0); break;
                    case 1: tap_code(KC_1); break;
                    case 2: tap_code(KC_2); break;
                    case 3: tap_code(KC_3); break;
                    case 4: tap_code(KC_4); break;
                    case 5: tap_code(KC_5); break;
                    case 6: tap_code(KC_6); break;
                    case 7: tap_code(KC_7); break;
                    case 8: tap_code(KC_8); break;
                    case 9: tap_code(KC_9); break;
                    }
				}
                break;
        }
    } else if (index == 2) { /* Third encoder */
        if (clockwise && selected_layer == HIGHEST_LAYER) { // Numpad if at top layer
                    selected_layer = _NUMPAD;
		} else if (clockwise) { // Next layer if not at top layer
			selected_layer ++;
		} else if (!clockwise && selected_layer == 0){ // Top layer if on Numpad
                    selected_layer = HIGHEST_LAYER;
		} else if (!clockwise && selected_layer != 0){ // Previous layer if not on Numpad
			selected_layer --;
				}
				layer_clear();
				layer_on(selected_layer);
    }
        }

/* Quad function tap dance.
 *
 * Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
uint8_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        // DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TRIPLE_TAP;
        else return TRIPLE_HOLD;
    } else return 8; // Magic number. At some point this method will expand to work for more presses
}

// Create an instance of 'tap' for the 'x' tap dance.
static tap xtap_state = {
    .is_press_action = true,
    .state = 0
};

// TD_A_I Quad function tap dance start
// A I F1 F9 (tap, double, hold, tap hold)
void TD_A_I_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_A); break;
        case SINGLE_HOLD: register_code(KC_F1); break;
        case DOUBLE_TAP: register_code(KC_I); break;
        case DOUBLE_HOLD: register_code(KC_F9); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case DOUBLE_SINGLE_TAP: tap_code(KC_I); register_code(KC_I);
    }
}

void TD_A_I_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP: unregister_code(KC_A); break;
        case SINGLE_HOLD: unregister_code(KC_F1); break;
        case DOUBLE_TAP: unregister_code(KC_I); break;
        case DOUBLE_HOLD: unregister_code(KC_F9);
        case DOUBLE_SINGLE_TAP: unregister_code(KC_I);
    }
    xtap_state.state = 0;
}
// TD_A_I end

// TD_N_G Quad function tap dance start
// N G F2 F10 (tap, double, hold, tap hold)
void TD_N_G_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_N); break;
        case SINGLE_HOLD: register_code(KC_F2); break;
        case DOUBLE_TAP: register_code(KC_G); break;
        case DOUBLE_HOLD: register_code(KC_F10); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case DOUBLE_SINGLE_TAP: tap_code(KC_G); register_code(KC_G);
    }
}

void TD_N_G_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP: unregister_code(KC_N); break;
        case SINGLE_HOLD: unregister_code(KC_F2); break;
        case DOUBLE_TAP: unregister_code(KC_G); break;
        case DOUBLE_HOLD: unregister_code(KC_F10);
        case DOUBLE_SINGLE_TAP: unregister_code(KC_G);
    }
    xtap_state.state = 0;
}
// TD_N_G end

// TD_X_C Quad function tap dance start
// X C F3 F11 (tap, double, hold, tap hold)
void TD_X_C_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_X); break;
        case SINGLE_HOLD: register_code(KC_F3); break;
        case DOUBLE_TAP: register_code(KC_C); break;
        case DOUBLE_HOLD: register_code(KC_F11); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case DOUBLE_SINGLE_TAP: tap_code(KC_C); register_code(KC_C);
    }
}

void TD_X_C_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP: unregister_code(KC_X); break;
        case SINGLE_HOLD: unregister_code(KC_F3); break;
        case DOUBLE_TAP: unregister_code(KC_C); break;
        case DOUBLE_HOLD: unregister_code(KC_F12);
        case DOUBLE_SINGLE_TAP: unregister_code(KC_C);
    }
    xtap_state.state = 0;
}
// TD_X_C end

// TD_V_D Quad function tap dance start
// V D F4 F12 (tap, double, hold, tap hold)
void TD_V_D_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_V); break;
        case SINGLE_HOLD: register_code(KC_F4); break;
        case DOUBLE_TAP: register_code(KC_D); break;
        case DOUBLE_HOLD: register_code(KC_F12); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case DOUBLE_SINGLE_TAP: tap_code(KC_D); register_code(KC_D);
    }
}

void TD_V_D_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP: unregister_code(KC_V); break;
        case SINGLE_HOLD: unregister_code(KC_F4); break;
        case DOUBLE_TAP: unregister_code(KC_D); break;
        case DOUBLE_HOLD: unregister_code(KC_F12);
        case DOUBLE_SINGLE_TAP: unregister_code(KC_D);
    }
    xtap_state.state = 0;
}
// TD_V_D end

// TD_V_D Quad function tap dance start
// V D F5 F13 (tap, double, hold, tap hold)
void TD_F_R_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_F); break;
        case SINGLE_HOLD: register_code(KC_F5); break;
        case DOUBLE_TAP: register_code(KC_R); break;
        case DOUBLE_HOLD: register_code(KC_F13); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case DOUBLE_SINGLE_TAP: tap_code(KC_R); register_code(KC_R);
    }
}

void TD_F_R_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP: unregister_code(KC_F); break;
        case SINGLE_HOLD: unregister_code(KC_F5); break;
        case DOUBLE_TAP: unregister_code(KC_R); break;
        case DOUBLE_HOLD: unregister_code(KC_F13);
        case DOUBLE_SINGLE_TAP: unregister_code(KC_R);
    }
    xtap_state.state = 0;
}
// TD_F_R end

// TD_S_E Quad function tap dance start
// S E F6 F14 (tap, double, hold, tap hold)
void TD_S_E_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_S); break;
        case SINGLE_HOLD: register_code(KC_F6); break;
        case DOUBLE_TAP: register_code(KC_E); break;
        case DOUBLE_HOLD: register_code(KC_F14); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case DOUBLE_SINGLE_TAP: tap_code(KC_E); register_code(KC_E);
    }
}

void TD_S_E_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP: unregister_code(KC_S); break;
        case SINGLE_HOLD: unregister_code(KC_F6); break;
        case DOUBLE_TAP: unregister_code(KC_E); break;
        case DOUBLE_HOLD: unregister_code(KC_F14);
        case DOUBLE_SINGLE_TAP: unregister_code(KC_E);
    }
    xtap_state.state = 0;
}
// TD_S_E end

// TD_P_K Quad function tap dance start
// P K F7 F15 (tap, double, hold, tap hold)
void TD_P_K_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_P); break;
        case SINGLE_HOLD: register_code(KC_F7); break;
        case DOUBLE_TAP: register_code(KC_K); break;
        case DOUBLE_HOLD: register_code(KC_F15); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case DOUBLE_SINGLE_TAP: tap_code(KC_K); register_code(KC_K);
    }
}

void TD_P_K_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP: unregister_code(KC_P); break;
        case SINGLE_HOLD: unregister_code(KC_F7); break;
        case DOUBLE_TAP: unregister_code(KC_K); break;
        case DOUBLE_HOLD: unregister_code(KC_F15);
        case DOUBLE_SINGLE_TAP: unregister_code(KC_K);
    }
    xtap_state.state = 0;
}
// TD_P_K end

// TD_L_Z Quad function tap dance start
// L Z F8 F16 (tap, double, hold, tap hold)
void TD_L_Z_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_L); break;
        case SINGLE_HOLD: register_code(KC_F8); break;
        case DOUBLE_TAP: register_code(KC_Z); break;
        case DOUBLE_HOLD: register_code(KC_F16); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case DOUBLE_SINGLE_TAP: tap_code(KC_Z); register_code(KC_Z);
    }
}

void TD_L_Z_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP: unregister_code(KC_L); break;
        case SINGLE_HOLD: unregister_code(KC_F8); break;
        case DOUBLE_TAP: unregister_code(KC_Z); break;
        case DOUBLE_HOLD: unregister_code(KC_F16);
        case DOUBLE_SINGLE_TAP: unregister_code(KC_Z);
    }
    xtap_state.state = 0;
}
// TD_L_Z end

// TD_ENT_BSPACE Quad function tap dance start
// ENTER BACKSPACE SPACE SPACE (tap, double, hold, tap hold)
void TD_ENT_BSPACE_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_ENT); break;
        case SINGLE_HOLD: register_code(KC_SPACE); break;
        case DOUBLE_TAP: register_code(KC_BSPACE); break;
        case DOUBLE_HOLD: register_code(KC_SPACE); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case DOUBLE_SINGLE_TAP: tap_code(KC_Z); register_code(KC_Z);
    }
}

void TD_ENT_BSPACE_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP: unregister_code(KC_ENT); break;
        case SINGLE_HOLD: unregister_code(KC_SPACE); break;
        case DOUBLE_TAP: unregister_code(KC_BSPACE); break;
        case DOUBLE_HOLD: unregister_code(KC_SPACE);
        case DOUBLE_SINGLE_TAP: unregister_code(KC_Z);
    }
    xtap_state.state = 0;
}
// TD_ENT_BSPACE end

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_A_I] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, TD_A_I_finished, TD_A_I_reset), // Ref Photoshop
	[TD_N_G] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, TD_N_G_finished, TD_N_G_reset), // Ref Photoshop
	[TD_X_C] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, TD_X_C_finished, TD_X_C_reset), // Ref Photoshop
	[TD_V_D] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, TD_V_D_finished, TD_V_D_reset), // Ref Photoshop
	[TD_F_R] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, TD_F_R_finished, TD_F_R_reset), // Ref Photoshop
	[TD_S_E] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, TD_S_E_finished, TD_S_E_reset), // Ref Photoshop
	[TD_P_K] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, TD_P_K_finished, TD_P_K_reset), // Ref Photoshop
	[TD_L_Z] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, TD_L_Z_finished, TD_L_Z_reset), // Ref Photoshop
	[TD_ENT_BSPACE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, TD_ENT_BSPACE_finished, TD_ENT_BSPACE_reset), // Ref Photoshop

};


#ifdef OLED_DRIVER_ENABLE

static const char *ANIMATION_NAMES[] = {
	"unknown",
	"static",
	"rainbow swirl I",
	"rainbow swirl II",
	"rainbow swirl III",
	"rainbow swirl IV",
	"rainbow swirl V",
	"rainbow swirl VI",
};

void rgblight_get_mode_name(uint16_t mode, size_t bufsize, char *buf) {
    snprintf(buf, bufsize, "%-25s", ANIMATION_NAMES[mode]);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
#ifdef LEFT_HAND
    return OLED_ROTATION_180;
#else
    return OLED_ROTATION_0;
#endif
}

void oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _NUMPAD:
            oled_write_P(PSTR("Numpad\n"), false);
            break;
        case _RGB:
            oled_write_P(PSTR("RGB\n"), false);
            break;
        case _PS:
            oled_write_P(PSTR("Photoshop\n"), false);
            break;
        case _PSDPAD:
            oled_write_P(PSTR("Arrows\n"), false);
            break;
        case _D2:
            oled_write_P(PSTR("Destiny 2\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    static char rgb_mode_name[30];
    rgblight_get_mode_name(rgblight_get_mode(), sizeof(rgb_mode_name), rgb_mode_name);

    oled_write_P(PSTR("Mode: "), false);
    oled_write_ln(rgb_mode_name, false);
}
#endif
