// user_DECtoHEX.h

#ifndef _USER_DECTOHEX_h
#define _USER_DECTOHEX_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


int Judge(int n);
int Detection(void);
int DEC_to_HEX(long n);

#endif

