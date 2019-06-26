// 
// 
// 

#include "user_test.h"
//#include <stdlib.h>

char buffer[3]; //用于存放转换好的十六进制字符串，可根据需要定义长度
char big_buffer[33]; //用于存放转换好的十六进制字符串。由于只要支持2位整数，所以长度3即可


//这个函数只能传入int类型0-255
char * inttohex1(int aa)
{
	if (aa / 16 < 10)   //计算十位，并转换成字符 
		buffer[0] = aa / 16 + '0';
	else
		buffer[0] = aa / 16 - 10 + 'A';
	if (aa % 16 < 10)   //计算个位，并转换成字符
		buffer[1] = aa % 16 + '0';
	else
		buffer[1] = aa % 16 - 10 + 'A';
	buffer[2] = '\0';   //字符串结束标志
	return (buffer);
}

//该函数的使用方法与inttohex1()函数相同，只是调用了系统封装好的函数库
//并且支持更大的,最大支持到4294967295，即FFFF FFFF
char * inttohex2(int aa)
{
	itoa(aa, big_buffer, 16);
	return (big_buffer);
}