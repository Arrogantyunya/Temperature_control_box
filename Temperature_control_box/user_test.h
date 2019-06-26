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

/* 十六进制数转换为十进制数 */
long hexToDec(char *source);
/* 返回ch字符在sign数组中的序号 */
int getIndexOfSigns(char ch);

#endif

