// user_Character.h

#ifndef _USER_CHARACTER_h
#define _USER_CHARACTER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


char *Character_processing(int aa);
int chartoint(char nn);

#endif

