// user_test.h

#ifndef _USER_TEST_h
#define _USER_TEST_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

char * inttohex1(int aa);
char * inttohex2(int aa);


#endif

