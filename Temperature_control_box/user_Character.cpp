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

//char buffer[3]; //用于存放转换好的十六进制字符串，可根据需要定义长度
//char big_buffer[33]; //用于存放转换好的十六进制字符串。由于只要支持2位整数，所以长度3即可


//函数名称：char * Character_processing(int x)
//函数功能：通过传入一个10进制的int型,然后按字节返回16进制的char型数组（例如）
//调用函数：char * inttohex2(int aa)
//函数说明：暂时只能传入不大于的65535(0xFFFF)的int型，超出时会截取不完全。
//返回值：返回16进制的char型数组，static char val_buff[2];
char * Character_processing(int x)
{
	pttarr = inttohex2(x);//对传入的int型10进制x转换成char型的HEX的字符
	/*Serial.print("inttohex2(x) = ");
	Serial.println(inttohex2(x));*/

	//1位的16进制数
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
	//2位的16进制数
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
	//3位的16进制数
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
	//4位的16进制数
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
		b = nn - '0';//这里的出10进制的整型
		/*Serial.print("b = ");
		Serial.println(b);*/
	}
	else if (('a' <= nn) && ('f' >= nn))
	{
		//Serial.println("[a-f]");
		b = nn - 'W';//这里得出十进制的整型
		/*Serial.print("b = ");
		Serial.println(b);*/
	}
	return b;
}

//char * inttohex1(int aa)
//{
//	if (aa / 16 < 10)   //计算十位，并转换成字符 
//		buffer[0] = aa / 16 + '0';
//	else
//		buffer[0] = aa / 16 - 10 + 'A';
//	if (aa % 16 < 10)   //计算个位，并转换成字符
//		buffer[1] = aa % 16 + '0';
//	else
//		buffer[1] = aa % 16 - 10 + 'A';
//	buffer[2] = '\0';   //字符串结束标志
//	return (buffer);
//}
