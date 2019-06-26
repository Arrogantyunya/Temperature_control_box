// 
// 
// 

#include "user_test.h"
//#include <stdlib.h>

char buffer[3]; //���ڴ��ת���õ�ʮ�������ַ������ɸ�����Ҫ���峤��
char big_buffer[33]; //���ڴ��ת���õ�ʮ�������ַ���������ֻҪ֧��2λ���������Գ���3����


//�������ֻ�ܴ���int����0-255
char * inttohex1(int aa)
{
	if (aa / 16 < 10)   //����ʮλ����ת�����ַ� 
		buffer[0] = aa / 16 + '0';
	else
		buffer[0] = aa / 16 - 10 + 'A';
	if (aa % 16 < 10)   //�����λ����ת�����ַ�
		buffer[1] = aa % 16 + '0';
	else
		buffer[1] = aa % 16 - 10 + 'A';
	buffer[2] = '\0';   //�ַ���������־
	return (buffer);
}

//�ú�����ʹ�÷�����inttohex1()������ͬ��ֻ�ǵ�����ϵͳ��װ�õĺ�����
//����֧�ָ����,���֧�ֵ�4294967295����FFFF FFFF
char * inttohex2(int aa)
{
	itoa(aa, big_buffer, 16);
	return (big_buffer);
}

//�����Ϊδ����inttohex���������Բ�ʹ��
//char * inttohex3(int aa)
//{
//	static int i = 0;
//	if (aa < 16)            //�ݹ�������� 
//	{
//		if (aa < 10)        //��ǰ��ת�����ַ������ַ��� 
//			big_buffer[i] = aa + '0';
//		else
//			big_buffer[i] = aa - 10 + 'A';
//		big_buffer[i + 1] = '\0'; //�ַ���������־ 
//	}
//	else
//	{
//		IntToHex(aa / 16);  //�ݹ���� 
//		i++;                //�ַ�������+1 
//		aa %= 16;           //���㵱ǰֵ
//		if (aa < 10)        //��ǰ��ת�����ַ������ַ��� 
//			big_buffer[i] = aa + '0';
//		else
//			big_buffer[i] = aa - 10 + 'A';
//	}
//	return (big_buffer);
//}

int hextodec1(int aa)
{
	int he;
	int re = 0;   // ����ת��Ϊ10���ƵĽ��
	int k = 16;   // 16����
	int n = 1;    // λȨ
	he = aa;
	//scanf("%d", &he);  // �����û������16������������0xǰ׺
	while (he != 0)
	{
		re += (he % 10)*n;  // ȡ����λλ��ֵ�������Զ�Ӧ��λȨֵ
		he /= 10;   // ȥ��16�����������λ���ε�λ��Ϊ���λ
		n *= k;     // λȨ����16
	}
	//printf("%d", re); // ���ת����Ľ��
	return re;
}



/* ʮ��������ת��Ϊʮ������ */
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

/* ����ch�ַ���sign�����е���� */
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

