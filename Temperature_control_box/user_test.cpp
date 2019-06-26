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

//这个因为未包含inttohex函数，所以不使用
//char * inttohex3(int aa)
//{
//	static int i = 0;
//	if (aa < 16)            //递归结束条件 
//	{
//		if (aa < 10)        //当前数转换成字符放入字符串 
//			big_buffer[i] = aa + '0';
//		else
//			big_buffer[i] = aa - 10 + 'A';
//		big_buffer[i + 1] = '\0'; //字符串结束标志 
//	}
//	else
//	{
//		IntToHex(aa / 16);  //递归调用 
//		i++;                //字符串索引+1 
//		aa %= 16;           //计算当前值
//		if (aa < 10)        //当前数转换成字符放入字符串 
//			big_buffer[i] = aa + '0';
//		else
//			big_buffer[i] = aa - 10 + 'A';
//	}
//	return (big_buffer);
//}

int hextodec1(int aa)
{
	int he;
	int re = 0;   // 保存转换为10进制的结果
	int k = 16;   // 16进制
	int n = 1;    // 位权
	he = aa;
	//scanf("%d", &he);  // 接收用户输入的16进制数，不含0x前缀
	while (he != 0)
	{
		re += (he % 10)*n;  // 取出各位位码值，并乘以对应的位权值
		he /= 10;   // 去掉16进制数的最低位，次低位变为最低位
		n *= k;     // 位权乘以16
	}
	//printf("%d", re); // 输出转换后的结果
	return re;
}



/* 十六进制数转换为十进制数 */
long hexToDec(char *source)
{
	long sum = 0;
	long t = 1;
	int i, len;

	len = strlen(source);
	for (i = len - 1; i >= 0; i--)
	{
		sum += t * getIndexOfSigns(*(source + i));
		t *= 16;
	}

	return sum;
}

/* 返回ch字符在sign数组中的序号 */
int getIndexOfSigns(char ch)
{
	if (ch >= '0' && ch <= '9')
	{
		return ch - '0';
	}
	if (ch >= 'A' && ch <= 'F')
	{
		return ch - 'A' + 10;
	}
	if (ch >= 'a' && ch <= 'f')
	{
		return ch - 'a' + 10;
	}
	return -1;
}

