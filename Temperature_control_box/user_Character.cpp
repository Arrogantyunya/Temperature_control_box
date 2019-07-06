// 
// 
// 

#include "user_Character.h"
#include "user_test.h"

String Char_buffer[2];
long c,d;
int cc,dd;
int decm[4];
static char val_buff[2];
char * pttarr = NULL;

//char buffer[3]; //���ڴ��ת���õ�ʮ�������ַ������ɸ�����Ҫ���峤��
//char big_buffer[33]; //���ڴ��ת���õ�ʮ�������ַ���������ֻҪ֧��2λ���������Գ���3����


//�������ƣ�char * Character_processing(int x)
//�������ܣ�ͨ������һ��10���Ƶ�int��,Ȼ���ֽڷ���16���Ƶ�char�����飨���磩
//���ú�����char * inttohex2(int aa)
//����˵������ʱֻ�ܴ��벻���ڵ�65535(0xFFFF)��int�ͣ�����ʱ���ȡ����ȫ��
//����ֵ������16���Ƶ�char�����飬static char val_buff[2];
char * Character_processing(int x)
{
	pttarr = inttohex2(x);//�Դ����int��10����xת����char�͵�HEX���ַ�
	/*Serial.print("inttohex2(x) = ");
	Serial.println(inttohex2(x));*/

	//1λ��16������
	if (x >= 0 && x < 16)
	{
		for (size_t i = 0; i < 1; i++)
		{
			decm[i] = chartoint(*(pttarr + i));
			/*Serial.print(String("decm[ ") + i + " ]: ");
			Serial.println(decm[i]);*/
		}
		cc = 0x00;
		dd = decm[0];
		Char_buffer[0] = String(cc);
		Char_buffer[1] = String(dd);
		long c = Char_buffer[0].toInt();
		long d = Char_buffer[1].toInt();
		val_buff[0] = c;
		val_buff[1] = d;
	}
	//2λ��16������
	else if (x >= 16 && x < 256)
	{
		for (size_t i = 0; i < 2; i++)
		{
			decm[i] = chartoint(*(pttarr + i));
			/*Serial.print(String("decm[ ") + i + " ]: ");
			Serial.println(decm[i]);*/
		}
		cc = 0x00;
		dd = decm[0] * 16 + decm[1];
		/*Serial.print("cc = ");
		Serial.println(cc);
		Serial.print("dd = ");
		Serial.println(dd,HEX);*/
		Char_buffer[0] = String(cc);
		Char_buffer[1] = String(dd);
		long c = Char_buffer[0].toInt();
		long d = Char_buffer[1].toInt();
		val_buff[0] = c;
		val_buff[1] = d;
	}
	//3λ��16������
	else if (x >= 256 && x < 4096)
	{
		for (size_t i = 0; i < 3; i++)
		{
			decm[i] = chartoint(*(pttarr + i));
			/*Serial.print(String("decm[ ") + i + " ]: ");
			Serial.println(decm[i]);*/
		}
		cc = decm[0];
		dd = decm[1] * 16 + decm[2];
		/*Serial.print("cc = ");
		Serial.println(cc);
		Serial.print("dd = ");
		Serial.println(dd);*/
		Char_buffer[0] = String(cc);
		Char_buffer[1] = String(dd);
		long c = Char_buffer[0].toInt();
		long d = Char_buffer[1].toInt();
		val_buff[0] = c;
		val_buff[1] = d;
	}
	//4λ��16������
	else if (x >= 4096 && x < 65536)
	{
		for (size_t i = 0; i < 4; i++)
		{
			decm[i] = chartoint(*(pttarr + i));
			/*Serial.print(String("decm[ ") + i + " ]: ");
			Serial.println(decm[i]);*/
		}
		cc = decm[0] * 16 + decm[1];
		dd = decm[2] * 16 + decm[3];
		/*Serial.print("cc = ");
		Serial.println(cc);
		Serial.print("dd = ");
		Serial.println(dd);*/
		Char_buffer[0] = String(cc);
		Char_buffer[1] = String(dd);
		long c = Char_buffer[0].toInt();
		long d = Char_buffer[1].toInt();
		val_buff[0] = c;
		val_buff[1] = d;
	}
	return (val_buff);
}

int chartoint(char nn)
{
	int b;
	if (('0' <= nn) && ('9' >= nn))
	{
		//Serial.println("[0-9]");
		b = nn - '0';//����ĳ�10���Ƶ�����
		/*Serial.print("b = ");
		Serial.println(b);*/
	}
	else if (('a' <= nn) && ('f' >= nn))
	{
		//Serial.println("[a-f]");
		b = nn - 'W';//����ó�ʮ���Ƶ�����
		/*Serial.print("b = ");
		Serial.println(b);*/
	}
	return b;
}

//char * inttohex1(int aa)
//{
//	if (aa / 16 < 10)   //����ʮλ����ת�����ַ� 
//		buffer[0] = aa / 16 + '0';
//	else
//		buffer[0] = aa / 16 - 10 + 'A';
//	if (aa % 16 < 10)   //�����λ����ת�����ַ�
//		buffer[1] = aa % 16 + '0';
//	else
//		buffer[1] = aa % 16 - 10 + 'A';
//	buffer[2] = '\0';   //�ַ���������־
//	return (buffer);
//}
