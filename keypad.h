/*
 * keypad.h
 *
 * Created: 1/22/2023 1:57:45 PM
 *  Author: AL
 */ 

#ifndef KEYPAD_H_
#define KEYPAD_H_

int keypad_poll( void );
void keypad_init( void );
void keypad_set_leds( uint16_t mask );
char keypad_stop_pressed( void );
void keypadSet_Speed_state( void );
void keypadSet_Pressure_state( void );
int keypad_scan( void );
#define KBD_MAX_COLS 16
#define KBD_MAX_ROWS  5


typedef enum _languge {
	HPGL=1,
	G_CODE,
	GPGL
} en_language;

extern en_language Lang;


enum {
	// KEYPAD_STOP, // not a scanned key, its a reset
	// I know it's kind of dumb to put numbers next to enums but if we decide to rename them or move them around, the number should stay with the name.
		KEYPAD_F1 = 0,
        KEYPAD_F2 = 1,
        KEYPAD_1 = 2,
        KEYPAD_2 = 3,
        KEYPAD_3 = 4,
        KEYPAD_4 = 5,
        KEYPAD_5 = 6,
        KEYPAD_6 = 7,
        KEYPAD_7 = 8,
        KEYPAD_8 = 9,
        KEYPAD_9 = 10,
        KEYPAD_0 = 11,
        KEYPAD_SPACE = 12,
        KEYPAD_BACKSPACE = 13,
        KEYPAD_MOVERIGHT = 14,
        //= 15,
        KEYPAD_F3 = 16,
        KEYPAD_F4 = 17,
        KEYPAD_Q = 18,
        KEYPAD_W = 19,
        KEYPAD_E = 20,
        KEYPAD_R = 21,
        KEYPAD_T = 22,
        KEYPAD_Y = 23,
        KEYPAD_U = 24,
        KEYPAD_I = 25,
        KEYPAD_O = 26,
        KEYPAD_P = 27,
        KEYPAD_CHARDISPLAY = 28,
        KEYPAD_RESETALL = 29,
        KEYPAD_MOVELEFT = 30,
        //= 31,
        KEYPAD_F5 = 32,
        KEYPAD_F6 = 33,
        KEYPAD_A = 34,
        KEYPAD_S = 35,
        KEYPAD_D = 36,
        KEYPAD_F = 37,
        KEYPAD_G = 38,
        KEYPAD_H = 39,
        KEYPAD_J = 40,
        KEYPAD_K = 41,
        KEYPAD_L = 42,
        KEYPAD_SEMICOLON = 43,
        KEYPAD_REPEATLAST = 44,
        KEYPAD_SOUNDONOFF = 45,
        KEYPAD_CUT = 46,
        //= 47,
        KEYPAD_MATERIALSAVER = 48,
        KEYPAD_REALDIALSIZE = 49,
        KEYPAD_Z = 50,
        KEYPAD_X = 51,
        KEYPAD_C = 52,
        KEYPAD_V = 53,
        KEYPAD_B = 54,
        KEYPAD_N = 55,
        KEYPAD_M = 56,
        KEYPAD_COMMA = 57,
        KEYPAD_PERIOD = 58,
        KEYPAD_SLASH = 59,
        KEYPAD_LOADLAST = 60,
        KEYPAD_SETCUTAREA = 61,
        KEYPAD_MOVEUP = 62,
        //= 63,
        KEYPAD_SHIFT = 64,
        KEYPAD_CUT_SHIFTLOCK = 65,
        KEYPAD_MINUS = 66,
        KEYPAD_PLUS = 67,
        KEYPAD_EQUALS = 68,
        KEYPAD_LEFTBRACKET = 69,
        KEYPAD_RIGHTBRACKET = 70,
        KEYPAD_LEFTBRACE = 71,
        KEYPAD_RIGHTBRACE = 72,
        KEYPAD_QUOTE = 73,
        KEYPAD_49 = 74,
        KEYPAD_50 = 75,
        KEYPAD_LOADMAT=76,
        KEYPAD_UNLOADMAT=77,
        KEYPAD_MOVEDN = 78,
        //KEYPAD_PORTRAIT = 14,
        //KEYPAD_FLIP = 15,
        //KEYPAD_OK = 17,
        //KEYPAD_XTRA1 = 19,
        //KEYPAD_FITPAGE = 38,
        //KEYPAD_QUANTITY = 39,
        //KEYPAD_XTRA2 = 43,
        //KEYPAD_MIXMATCH = 62,
        //KEYPAD_MULTICUT = 63,
        //KEYPAD_MOVEUPLEFT = 64,
        //KEYPAD_MOVEUPRIGHT = 66,
        //KEYPAD_LINERETURN = 67,
        //KEYPAD_FITLENGTH = 86,
        //KEYPAD_CENTERPOINT = 87,
        //KEYPAD_MOVELEFT = 88,
        //KEYPAD_SETTINGS = 91,
        //KEYPAD_AUTOFILL = 110,
        //KEYPAD_MATSIZE = 111,
        //KEYPAD_MOVEDNLEFT = 112,
        //KEYPAD_MOVEDN = 113,
        //KEYPAD_MOVEDNRIGHT = 114
    } KEYS;
#endif

 /* KEYPAD_H_ */