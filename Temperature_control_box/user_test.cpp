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