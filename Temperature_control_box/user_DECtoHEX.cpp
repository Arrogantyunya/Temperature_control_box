// 
// 
// 

#include "user_DECtoHEX.h"


char DEC_to_HEX(long n)
{
	char x[16] = { '0','1','2','3','4','5','6','7','8',
					'9','A','B','C','D','E','F' };//ʮ������ʮ�����ƶ�Ӧ������
	//int n = Detection();//�������ݼ���ٸ�ֵ

	//int n = 1205;
	//int k = Judge(n);//���������Ҫ�ĳ���
	//char y[k];//�������鴢��ʮ��������
	k = Judge(n);//���������Ҫ�ĳ���
	memset(y, '\0', sizeof(y));//�������

	int i, j;
	j = 0;
	while (n >= 16)//��ת���õ�ʮ��������������������
	{
		i = (n % 16);//��������
		y[j] = x[i];//�ѵõ�������תΪʮ�������������硰11��ת��b����
		j++;//�����±���λ
		n /= 16;//�����ٸ�ֵ�����Լ��������¸�ѭ���ٳ���
		if (n < 16)
		{
			y[j] = x[n];
		}
	}

	//��ʱ����y�ڵ�ʮ���������ǵ����������

	Serial.print("0x");
	while (j >= 0)//�Ѵ�����ʮ�������������鵹�����
	{
		if (j > 0)//�ж��ǲ������һ�����ǵĻ�����
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
	while (m > 16)//���С��16����ô1λ������
	{
		m /= 16;//�������16�ȳ���16
		k++;//��һλ
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
			printf("���������������������һ��:");
			while (getchar() != '\n');
		}
		else
			break;
	}
	return n;*/
}