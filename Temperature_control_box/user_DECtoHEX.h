// user_DECtoHEX.h

#ifndef _USER_DECTOHEX_h
#define _USER_DECTOHEX_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

static int k;//���������Ҫ�ĳ���
static char y[10];//�������鴢��ʮ��������
//static char *intptr;

int Judge(int n);
int Detection(void);
char DEC_to_HEX(long n);

#endif

