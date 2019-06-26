// user_DECtoHEX.h

#ifndef _USER_DECTOHEX_h
#define _USER_DECTOHEX_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

static int k;//检测数组需要的长度
static char y[10];//创建数组储存十六进制数
//static char *intptr;

int Judge(int n);
int Detection(void);
char DEC_to_HEX(long n);

#endif

