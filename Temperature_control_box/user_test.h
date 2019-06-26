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
//char * inttohex3(int aa);

int hextodec1(int aa);

/* ʮ��������ת��Ϊʮ������ */
long hexToDec(char *source);
/* ����ch�ַ���sign�����е���� */
int getIndexOfSigns(char ch);

#endif

