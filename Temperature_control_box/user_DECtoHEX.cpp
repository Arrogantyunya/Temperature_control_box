// 
// 
// 

#include "user_DECtoHEX.h"


char DEC_to_HEX(long n)
{
	char x[16] = { '0','1','2','3','4','5','6','7','8',
					'9','A','B','C','D','E','F' };//十进制与十六进制对应的数组
	//int n = Detection();//输入数据检查再赋值

	//int n = 1205;
	//int k = Judge(n);//检测数组需要的长度
	//char y[k];//创建数组储存十六进制数
	k = Judge(n);//检测数组需要的长度
	memset(y, '\0', sizeof(y));//清空数组

	int i, j;
	j = 0;
	while (n >= 16)//把转换好的十六进制数依次输入数组
	{
		i = (n % 16);//先是求余
		y[j] = x[i];//把得到的余数转为十六进制数（例如“11”转“b”）
		j++;//数组下标移位
		n /= 16;//求商再赋值给它自己（方便下个循环再除）
		if (n < 16)
		{
			y[j] = x[n];
		}
	}

	//此时数组y内的十六进制数是倒过来储存的

	Serial.print("0x");
	while (j >= 0)//把储存了十六进制数的数组倒着输出
	{
		if (j > 0)//判断是不是最后一个，是的话换行
			Serial.print(y[j]);
		else
			Serial.println(y[j]);
		j--;
	}

	/*return 0;*/
	static char *intptr = y;
	return *intptr;
}

int Judge(int n)
{
	int k = 1;
	int m = n;
	while (m > 16)//如果小于16，那么1位就行了
	{
		m /= 16;//如果大于16先除与16
		k++;//加一位
	}
	return k;
}

int Detection(void)
{
	/*int n;
	while (1)
	{
		if (scanf("%d", &n) != 1 || getchar() != '\n')
		{
			printf("你输入的数据有误，请再输一遍:");
			while (getchar() != '\n');
		}
		else
			break;
	}
	return n;*/
}