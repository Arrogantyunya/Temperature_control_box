// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
	Name:       Temperature_control_box.ino
	Created:	2019/6/12 星期三 13:40:35
	Author:     刘家辉
*/

// Define User Types below here or use a .h file
//


// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//

// The setup() function runs once each time the micro-controller starts

#include "user_Character.h"			//
#include "user_test.h"				//
#include "user_HEXtoDEC.h"			//
#include "user_DECtoHEX.h"			//
#include "user_initialization.h"	//初始化函数
#include "MODBUS_RTU_CRC16.h"		//modbusCRC16校验的函数
#include "user_DECtoHEX.h"			//
//#include "user_Binary_conversion.h"//进制转换函数，这个库有问题，添加了导致程序下载不了

//这里是从机设备地址为1的8路继电器
static unsigned char Y0_ON[8] = { 0x01,0x05,0x00,0x00,0xFF,0x00 };
static unsigned char Y0_OFF[8] = { 0x01,0x05,0x00,0x00,0x00,0x00 };
static unsigned char Y1_ON[8] = { 0x01,0x05,0x00,0x01,0xFF,0x00 };
static unsigned char Y1_OFF[8] = { 0x01,0x05,0x00,0x01,0x00,0x00 };
static unsigned char Y2_ON[8] = { 0x01,0x05,0x00,0x02,0xFF,0x00 };
static unsigned char Y2_OFF[8] = { 0x01,0x05,0x00,0x02,0x00,0x00 };
static unsigned char Y3_ON[8] = { 0x01,0x05,0x00,0x03,0xFF,0x00 };
static unsigned char Y3_OFF[8] = { 0x01,0x05,0x00,0x03,0x00,0x00 };
static unsigned char Y4_ON[8] = { 0x01,0x05,0x00,0x04,0xFF,0x00 };
static unsigned char Y4_OFF[8] = { 0x01,0x05,0x00,0x04,0x00,0x00 };
static unsigned char Y5_ON[8] = { 0x01,0x05,0x00,0x05,0xFF,0x00 };
static unsigned char Y5_OFF[8] = { 0x01,0x05,0x00,0x05,0x00,0x00 };
static unsigned char Y6_ON[8] = { 0x01,0x05,0x00,0x06,0xFF,0x00 };
static unsigned char Y6_OFF[8] = { 0x01,0x05,0x00,0x06,0x00,0x00 };
static unsigned char Y7_ON[8] = { 0x01,0x05,0x00,0x07,0xFF,0x00 };
static unsigned char Y7_OFF[8] = { 0x01,0x05,0x00,0x07,0x00,0x00 };

static unsigned char getY1[8] = { 0x01,0x01,0x00,0x00,0x00,0x08 };//01 01 0000 0008


//这里是从机设备地址为2的16路继电器
static unsigned char Y8_ON[8] = { 0x02,0x05,0x00,0x00,0xFF,0x00 };
static unsigned char Y8_OFF[8] = { 0x02,0x05,0x00,0x00,0x00,0x00 };
static unsigned char Y9_ON[8] = { 0x02,0x05,0x00,0x01,0xFF,0x00 };
static unsigned char Y9_OFF[8] = { 0x02,0x05,0x00,0x01,0x00,0x00 };
static unsigned char Y10_ON[8] = { 0x02,0x05,0x00,0x02,0xFF,0x00 };
static unsigned char Y10_OFF[8] = { 0x02,0x05,0x00,0x02,0x00,0x00 };
static unsigned char Y11_ON[8] = { 0x02,0x05,0x00,0x03,0xFF,0x00 };
static unsigned char Y11_OFF[8] = { 0x02,0x05,0x00,0x03,0x00,0x00 };
static unsigned char Y12_ON[8] = { 0x02,0x05,0x00,0x04,0xFF,0x00 };
static unsigned char Y12_OFF[8] = { 0x02,0x05,0x00,0x04,0x00,0x00 };
static unsigned char Y13_ON[8] = { 0x02,0x05,0x00,0x05,0xFF,0x00 };
static unsigned char Y13_OFF[8] = { 0x02,0x05,0x00,0x05,0x00,0x00 };
static unsigned char Y14_ON[8] = { 0x02,0x05,0x00,0x06,0xFF,0x00 };
static unsigned char Y14_OFF[8] = { 0x02,0x05,0x00,0x06,0x00,0x00 };
static unsigned char Y15_ON[8] = { 0x02,0x05,0x00,0x07,0xFF,0x00 };
static unsigned char Y15_OFF[8] = { 0x02,0x05,0x00,0x07,0x00,0x00 };
static unsigned char Y16_ON[8] = { 0x02,0x05,0x00,0x08,0xFF,0x00 };
static unsigned char Y16_OFF[8] = { 0x02,0x05,0x00,0x08,0x00,0x00 };
static unsigned char Y17_ON[8] = { 0x02,0x05,0x00,0x09,0xFF,0x00 };
static unsigned char Y17_OFF[8] = { 0x02,0x05,0x00,0x09,0x00,0x00 };
static unsigned char Y18_ON[8] = { 0x02,0x05,0x00,0x0A,0xFF,0x00 };
static unsigned char Y18_OFF[8] = { 0x02,0x05,0x00,0x0A,0x00,0x00 };
static unsigned char Y19_ON[8] = { 0x02,0x05,0x00,0x0B,0xFF,0x00 };
static unsigned char Y19_OFF[8] = { 0x02,0x05,0x00,0x0B,0x00,0x00 };
static unsigned char Y20_ON[8] = { 0x02,0x05,0x00,0x0C,0xFF,0x00 };
static unsigned char Y20_OFF[8] = { 0x02,0x05,0x00,0x0C,0x00,0x00 };
static unsigned char Y21_ON[8] = { 0x02,0x05,0x00,0x0D,0xFF,0x00 };
static unsigned char Y21_OFF[8] = { 0x02,0x05,0x00,0x0D,0x00,0x00 };
static unsigned char Y22_ON[8] = { 0x02,0x05,0x00,0x0E,0xFF,0x00 };
static unsigned char Y22_OFF[8] = { 0x02,0x05,0x00,0x0E,0x00,0x00 };
static unsigned char Y23_ON[8] = { 0x02,0x05,0x00,0x0F,0xFF,0x00 };
static unsigned char Y23_OFF[8] = { 0x02,0x05,0x00,0x0F,0x00,0x00 };
static unsigned char getY2_1[8] = { 0x02,0x01,0x00,0x00,0x00,0x08 };//01 01 0000 0008
static unsigned char getY2_2[8] = { 0x02,0x01,0x00,0x08,0x00,0x08 };//01 01 0008 0008



//这是设备地址为3的温度控制通道的指令
static unsigned char upplimit_3[8] = { 0x03,0x06,0x00,0x05 };//设置设备地址3的上限值
static unsigned char lowlimit_3[8] = { 0x03,0x06,0x00,0x04 };//设置设备地址3的下限值

//这是设置设备地址3的8通道的加热指令
static unsigned char heat3_1[8] = { 0x03,0x06,0x00,0x11,0x00,0x00 };
static unsigned char heat3_2[8] = { 0x03,0x06,0x00,0x1B,0x00,0x00 };
static unsigned char heat3_3[8] = { 0x03,0x06,0x00,0x25,0x00,0x00 };
static unsigned char heat3_4[8] = { 0x03,0x06,0x00,0x2F,0x00,0x00 };
static unsigned char heat3_5[8] = { 0x03,0x06,0x00,0x39,0x00,0x00 };
static unsigned char heat3_6[8] = { 0x03,0x06,0x00,0x43,0x00,0x00 };
static unsigned char heat3_7[8] = { 0x03,0x06,0x00,0x4D,0x00,0x00 };
static unsigned char heat3_8[8] = { 0x03,0x06,0x00,0x57,0x00,0x00 };

//这是设置设备地址3的8通道的制冷指令
static unsigned char cool3_1[8] = { 0x03,0x06,0x00,0x11,0x00,0x01 };
static unsigned char cool3_2[8] = { 0x03,0x06,0x00,0x1B,0x00,0x01 };
static unsigned char cool3_3[8] = { 0x03,0x06,0x00,0x25,0x00,0x01 };
static unsigned char cool3_4[8] = { 0x03,0x06,0x00,0x2F,0x00,0x01 };
static unsigned char cool3_5[8] = { 0x03,0x06,0x00,0x39,0x00,0x01 };
static unsigned char cool3_6[8] = { 0x03,0x06,0x00,0x43,0x00,0x01 };
static unsigned char cool3_7[8] = { 0x03,0x06,0x00,0x4D,0x00,0x01 };
static unsigned char cool3_8[8] = { 0x03,0x06,0x00,0x57,0x00,0x01 };

//这是设置设备地址3的8通道期望温度指令
static unsigned char Temp3_1[8] = { 0x03,0x06,0x00,0x09 };
static unsigned char Temp3_2[8] = { 0x03,0x06,0x00,0x13 };
static unsigned char Temp3_3[8] = { 0x03,0x06,0x00,0x1D };
static unsigned char Temp3_4[8] = { 0x03,0x06,0x00,0x27 };
static unsigned char Temp3_5[8] = { 0x03,0x06,0x00,0x31 };
static unsigned char Temp3_6[8] = { 0x03,0x06,0x00,0x3B };
static unsigned char Temp3_7[8] = { 0x03,0x06,0x00,0x45 };
static unsigned char Temp3_8[8] = { 0x03,0x06,0x00,0x4F };

//这是读取设备地址3的8通道测量温度的指令
static unsigned char getT3_1[8] = { 0x03,0x03,0x10,0x01,0x00,0x01 };
static unsigned char getT3_2[8] = { 0x03,0x03,0x10,0x02,0x00,0x01 };
static unsigned char getT3_3[8] = { 0x03,0x03,0x10,0x03,0x00,0x01 };
static unsigned char getT3_4[8] = { 0x03,0x03,0x10,0x04,0x00,0x01 };
static unsigned char getT3_5[8] = { 0x03,0x03,0x10,0x05,0x00,0x01 };
static unsigned char getT3_6[8] = { 0x03,0x03,0x10,0x06,0x00,0x01 };
static unsigned char getT3_7[8] = { 0x03,0x03,0x10,0x07,0x00,0x01 };
static unsigned char getT3_8[8] = { 0x03,0x03,0x10,0x08,0x00,0x01 };
//======================================================================

//这是设备地址为4的温度控制通道的指令
static unsigned char upplimit_4[8] = { 0x04,0x06,0x00,0x05 };//设置设备地址4的上限值
static unsigned char lowlimit_4[8] = { 0x04,0x06,0x00,0x04 };//设置设备地址4的下限值

//这是设置设备地址4的8通道的加热指令
static unsigned char heat4_1[8] = { 0x04,0x06,0x00,0x11,0x00,0x00 };
static unsigned char heat4_2[8] = { 0x04,0x06,0x00,0x1B,0x00,0x00 };
static unsigned char heat4_3[8] = { 0x04,0x06,0x00,0x25,0x00,0x00 };
static unsigned char heat4_4[8] = { 0x04,0x06,0x00,0x2F,0x00,0x00 };
static unsigned char heat4_5[8] = { 0x04,0x06,0x00,0x39,0x00,0x00 };
static unsigned char heat4_6[8] = { 0x04,0x06,0x00,0x43,0x00,0x00 };
static unsigned char heat4_7[8] = { 0x04,0x06,0x00,0x4D,0x00,0x00 };
static unsigned char heat4_8[8] = { 0x04,0x06,0x00,0x57,0x00,0x00 };

//这是设置设备地址4的8通道的制冷指令
static unsigned char cool4_1[8] = { 0x04,0x06,0x00,0x11,0x00,0x01 };
static unsigned char cool4_2[8] = { 0x04,0x06,0x00,0x1B,0x00,0x01 };
static unsigned char cool4_3[8] = { 0x04,0x06,0x00,0x25,0x00,0x01 };
static unsigned char cool4_4[8] = { 0x04,0x06,0x00,0x2F,0x00,0x01 };
static unsigned char cool4_5[8] = { 0x04,0x06,0x00,0x39,0x00,0x01 };
static unsigned char cool4_6[8] = { 0x04,0x06,0x00,0x43,0x00,0x01 };
static unsigned char cool4_7[8] = { 0x04,0x06,0x00,0x4D,0x00,0x01 };
static unsigned char cool4_8[8] = { 0x04,0x06,0x00,0x57,0x00,0x01 };

//这是设置设备地址4的8通道期望温度指令
static unsigned char Temp4_1[8] = { 0x04,0x06,0x00,0x09 };
static unsigned char Temp4_2[8] = { 0x04,0x06,0x00,0x13 };
static unsigned char Temp4_3[8] = { 0x04,0x06,0x00,0x1D };
static unsigned char Temp4_4[8] = { 0x04,0x06,0x00,0x27 };
static unsigned char Temp4_5[8] = { 0x04,0x06,0x00,0x31 };
static unsigned char Temp4_6[8] = { 0x04,0x06,0x00,0x3B };
static unsigned char Temp4_7[8] = { 0x04,0x06,0x00,0x45 };
static unsigned char Temp4_8[8] = { 0x04,0x06,0x00,0x4F };

//这是读取设备地址4的8通道测量温度的指令
static unsigned char getT4_1[8] = { 0x04,0x03,0x10,0x01,0x00,0x01 };
static unsigned char getT4_2[8] = { 0x04,0x03,0x10,0x02,0x00,0x01 };
static unsigned char getT4_3[8] = { 0x04,0x03,0x10,0x03,0x00,0x01 };
static unsigned char getT4_4[8] = { 0x04,0x03,0x10,0x04,0x00,0x01 };
static unsigned char getT4_5[8] = { 0x04,0x03,0x10,0x05,0x00,0x01 };
static unsigned char getT4_6[8] = { 0x04,0x03,0x10,0x06,0x00,0x01 };
static unsigned char getT4_7[8] = { 0x04,0x03,0x10,0x07,0x00,0x01 };
static unsigned char getT4_8[8] = { 0x04,0x03,0x10,0x08,0x00,0x01 };

//这是控制485模拟输出
static unsigned char AnalogV_output1[8] = { 0x05,0x06,0x01,0x00 };
static unsigned char AnalogV_output2[8] = { 0x05,0x06,0x01,0x01 };


String str_usb;

static unsigned short length = 6;

static int modbus_CRC = 0x00;
static int RS485_CRC = 0x00;
static int RS485_Temp = 0;
static int MacStatus = 0;
static unsigned char RS485REceive_Data[50];
static int RS485REceive_Length = 0;
static unsigned char USBREceive_Data[50];
static int USBREceive_Length = 0;
static unsigned char LORAEceive_Data[50];
static int LORAREceive_Length = 0;
static int TempDesired = 0;		//温度期望值
static int TempUppLimit = 0;	//温度上限值
static int TempLowLimit = 0;	//温度下限值
static int Temp_Measure = 0;	//温度测量值
static long FlowDesired = 0;		//流量期望值
static float Flow_Measure = 0;	//流量测量值
static float flow_measure[5];	//流量测量值数组
static char * ptrc = NULL;


//相关函数的定义
int RS485Receive_information();					//RS485接收函数
int LORAReceive_information();					//LORA接收函数
int USB_Serial_reception();						//USB串口的接收函数
void USB_Judge(unsigned char *USBREceive_Data);	//USB判断函数



void setup()
{
	Initialization();//初始化函数
}

// Add the main program code into the continuous loop() function
void loop()
{
	//RS485REceive_Length = 0;
	//modbus_CRC = N_CRC16(Y0_ON, length);//得到modbus_CRC的值
	//Y0_ON[6] = modbus_CRC >> 8;
	//Y0_ON[7] = modbus_CRC;

	//Serial2.write(Y0_ON,8);
	////Serial2.flush();

	//while (Serial2.available() > 0)//RS485串口接收到数据
	//{
	//	RS485REceive_Data[RS485REceive_Length++] = Serial2.read();
	//	Serial.print(RS485REceive_Data[RS485REceive_Length - 1], HEX);
	//	Serial.print(" ");
	//	delay(1);
	//}

	//if (RS485REceive_Length > 0)
	//{
	//	Serial.println("");
	//	Serial.print("RS485REceive_Length = ");
	//	Serial.println(RS485REceive_Length);
	//	for (int i = 0; i < RS485REceive_Length; i++)
	//	{
	//		Serial.print(String("RS485REceive_Data") + "[ " + i + " ] ");
	//		Serial.println(RS485REceive_Data[i], HEX);
	//	}
	//	RS485REceive_Length = 0;
	//}
	//Serial.println("");
	//delay(5000);



	//modbus_CRC = N_CRC16(Y0_OFF, length);//得到modbus_CRC的值
	//Y0_OFF[6] = modbus_CRC >> 8;
	//Y0_OFF[7] = modbus_CRC;

	//Serial2.write(Y0_OFF, 8);
	////Serial2.flush();

	//while (Serial2.available() > 0)//RS485串口接收到数据
	//{
	//	RS485REceive_Data[RS485REceive_Length++] = Serial2.read();
	//	Serial.print(RS485REceive_Data[RS485REceive_Length - 1], HEX);
	//	Serial.print(" ");
	//	delay(1);
	//}
	//if (RS485REceive_Length > 0)
	//{
	//	Serial.println("");
	//	Serial.print("RS485REceive_Length = ");
	//	Serial.println(RS485REceive_Length);
	//	for (int i = 0; i < RS485REceive_Length; i++)
	//	{
	//		Serial.print(String("RS485REceive_Data") + "[ " + i + " ] ");
	//		Serial.println(RS485REceive_Data[i], HEX);
	//	}
	//	RS485REceive_Length = 0;
	//}
	//Serial.println("");
	//delay(5000);

//==============以下为正常程序===================================

	USB_Serial_reception();		//USB串口接收函数
	RS485Receive_information();	//RS485的接收函数
	//Analog_input1();
}

void Analog_input1(void)
{
	int analogRead1 = analogRead(V1);
	//Serial.println(analogRead1);
	float ar = (analogRead1 * 0.8056)*11;
	Serial.println(String("ar = ") + ar + String("mV"));
	float Flow_Value = ar / 25;//(ar/5000)*200
	//float Flow_Value = (ar - 680)/25;
	Serial.println(String("Flow_Value = ") + Flow_Value + String("sccm"));
	Serial.println("---------------");
	delay(500);
}

int RS485Receive_information(void)
{
	RS485REceive_Length = 0;
	delay(500);
	while (Serial2.available() > 0)
	{
		RS485REceive_Data[RS485REceive_Length++] = Serial2.read();
		/*Serial.print(RS485REceive_Data[RS485REceive_Length - 1], HEX);
		Serial.print(" ");*/
	}
	if (RS485REceive_Length > 0)
	{
		/*Serial.println("");
		Serial.print("RS485REceive_Length = ");
		Serial.println(RS485REceive_Length);
		for (int i = 0; i < RS485REceive_Length; i++)
		{
			Serial.print(String("RS485REceive_Data") + "[ " + i + " ] =");
			Serial.println(RS485REceive_Data[i], HEX);
		}*/

		RS485_CRC = N_CRC16(RS485REceive_Data, RS485REceive_Length - 2);
		/*Serial.print("RS485_CRC = ");
		Serial.println(RS485_CRC, HEX);*/

		RS485REceive_Length = 0;
	}
	return RS485_CRC;
}

int RS485Receive_Temp(void)
{
	RS485REceive_Length = 0;
	delay(500);
	while (Serial2.available() > 0)
	{
		RS485REceive_Data[RS485REceive_Length++] = Serial2.read();
		/*Serial.print(RS485REceive_Data[RS485REceive_Length - 1], HEX);
		Serial.print(" ");*/
	}
	if (RS485REceive_Length > 0)
	{
		/*Serial.println("");
		Serial.print("RS485REceive_Length = ");
		Serial.println(RS485REceive_Length);*/
		/*for (int i = 0; i < RS485REceive_Length; i++)
		{
			Serial.print(String("RS485REceive_Data") + "[ " + i + " ] =");
			Serial.println(RS485REceive_Data[i], HEX);
		}*/

		RS485_CRC = N_CRC16(RS485REceive_Data, RS485REceive_Length - 2);
		//-----------测试使用-------------
		//RS485_CRC = 0xC101;
		//-------------------------------
		/*Serial.print("RS485_CRC = ");
		Serial.println(RS485_CRC, HEX);*/

		String STRRS485_CRC = String(RS485_CRC, HEX);//将int型16进制的RS485_CRC的值转换为string类型

		/*int STRRS485_length = STRRS485_CRC.length();
		Serial.print("STRRS485_length = ");
		Serial.println(STRRS485_length);*/

		//-----------测试使用-----------
		//RS485REceive_Data[5] = 0xC1;
		//RS485REceive_Data[6] = 0x01;
		//-----------------------------
		String strrs485_crc = String(RS485REceive_Data[5], HEX) + String(RS485REceive_Data[6], HEX);//将设备返回的啥转换为string类型

		/*strrs485_crc = String(0, HEX) + String(0, HEX) + String(0, HEX) + String(0, HEX);
		Serial.print("strrs485_crc = ");
		Serial.println(strrs485_crc);
		Serial.println("------------------");*/

		//str.length()为str字符串的长度

		//boolean startssWith(string)	开始
		//Serial.println(str.startsWith("FE"));//判断字符串是否是以FE开始

		//判断字符串中是否包含有其他的字符或者字符串
		//indexOf(string)	indexOf(string,n)	string为需要查找的字符串，n为从第几位开始查
		//从左到右匹配字符串，一旦遇到查找的目标，会立刻返回整型的数字
		//这个数字代表了要查的字符串的位置编号，也叫作索引值
		//如果什么都没有找到，返回-1

		/*Serial.print("STRRS485_CRC = ");
		Serial.println(STRRS485_CRC);
		Serial.print("strrs485_crc = ");
		Serial.println(strrs485_crc);*/

		//这里是为了消除strrs485_crc第0位的0，假如为校验码为00C1，则RS485_CRC = C1，但是strrs485_crc = 0c1
		//所以就将strrs485_crc第0位的0删除
		if (strrs485_crc.startsWith("0"))
		{
			//Serial.println("strrs485_crc.startsWith(0)");
			strrs485_crc.remove(0, 1);
		}

		//Serial.println(str.substring(0, 3));//从索引值0开始截取到3的字符串，不包含3的字符
		//Serial.print("索引值：=");
		//Serial.println(STRRS485_CRC.substring(2, 3));

		//这里是为了消除STRRS485_CRC第2位的0，假如为校验码为C101，则STRRS485_CRC = C101，但是strrs485_crc = c11
		//所以就将STRRS485_CRC第2位的0删除，改为c11
		if (STRRS485_CRC.length() == 4)//字符串长度为4
		{
			if ((STRRS485_CRC.substring(2, 3)) == String(0))
			{
				//Serial.println("(STRRS485_CRC.substring(2, 3)) == String(0)");
				STRRS485_CRC.remove(2, 1);
			}
		}
		//这里是为了消除STRRS485_CRC第1位的0，假如为校验码为0101，则STRRS485_CRC = 101，但是strrs485_crc = 11
		//所以就将STRRS485_CRC第1位的0删除，改为11
		else if (STRRS485_CRC.length() == 3)//字符串长度为3
		{
			if ((STRRS485_CRC.substring(1, 2)) == String(0))
			{
				//Serial.println("(STRRS485_CRC.substring(1, 2)) == String(0)");
				STRRS485_CRC.remove(1, 1);
			}
		}


		//=======================测试所用的代码=====================================
		//int count = 0;//用于计数，如果crc校验码出现了4个0，则为了不被while循环全部清除
		//while ((strrs485_crc.startsWith("0")) && (count != 1))
		//{
		//	Serial.println("000000000000000");
		//	strrs485_crc.remove(0, 1);
		//	count++;
		//}
		//if (count == 4)
		//{
		//	strrs485_crc = String(0, HEX);
		//}
		//=======================================================================


		/*Serial.print("STRRS485_CRC = ");
		Serial.println(STRRS485_CRC);
		Serial.print("strrs485_crc = ");
		Serial.println(strrs485_crc);*/

		//str.equals用于验证两个字符串是否相等，相同返回真，不同返回假
		if (STRRS485_CRC == strrs485_crc)
		{
			//Serial.println("crc校验通过");

			String strabc;
			//char const *c = str.c_str();
			strabc = String(RS485REceive_Data[3], HEX) + String(RS485REceive_Data[4], HEX);

			int strabc_length = strabc.length();
			char shuzu2[4];
			strabc.toCharArray(shuzu2, (strabc_length + 1));//只能处理到4个字符 
			/*for (int i = 0; i < strabc_length; i++)
			{
				Serial.print(String("shuzu2") + "[ " + i + " ] =");
				Serial.println(shuzu2[i]);
			}*/
			RS485_Temp = charhex_to_dec(shuzu2);//int charhex_to_dec(char *chr)
			/*Serial.print("RS485_Temp = ");
			Serial.println(RS485_Temp);*/

			RS485REceive_Length = 0;

			return RS485_Temp;
		}
	}
	return -1;
}

//得到继电器1-16的状态
int RS485Receive_MacStatus(int x)
{
	int Status = 0;
	RS485REceive_Length = 0;
	delay(500);
	while (Serial2.available() > 0)
	{
		RS485REceive_Data[RS485REceive_Length++] = Serial2.read();
		/*Serial.print(RS485REceive_Data[RS485REceive_Length - 1], HEX);
		Serial.print(" ");*/
	}
	if (RS485REceive_Length > 0)
	{
		/*Serial.println("");
		Serial.print("RS485REceive_Length = ");
		Serial.println(RS485REceive_Length);*/
		/*for (int i = 0; i < RS485REceive_Length; i++)
		{
			Serial.print(String("RS485REceive_Data") + "[ " + i + " ] =");
			Serial.println(RS485REceive_Data[i], HEX);
		}*/

		RS485_CRC = N_CRC16(RS485REceive_Data, RS485REceive_Length - 2);
		/*Serial.print("RS485_CRC = ");
		Serial.println(RS485_CRC, HEX);*/

		String STRRS485_CRC = String(RS485_CRC, HEX);//将int型16进制的RS485_CRC的值转换为string类型
		String strrs485_crc = String(RS485REceive_Data[4], HEX) + String(RS485REceive_Data[5], HEX);//将设备返回的啥转换为string类型

		if (strrs485_crc.startsWith("0"))
		{
			strrs485_crc.remove(0, 1);
		}
		if (STRRS485_CRC.length() == 4)//字符串长度为4
		{
			if ((STRRS485_CRC.substring(2, 3)) == String(0))
			{
				//Serial.println("(STRRS485_CRC.substring(2, 3)) == String(0)");
				STRRS485_CRC.remove(2, 1);
			}
		}
		//这里是为了消除STRRS485_CRC第1位的0，假如为校验码为0101，则STRRS485_CRC = 101，但是strrs485_crc = 11
		//所以就将STRRS485_CRC第1位的0删除，改为11
		else if (STRRS485_CRC.length() == 3)//字符串长度为3
		{
			if ((STRRS485_CRC.substring(1, 2)) == String(0))
			{
				//Serial.println("(STRRS485_CRC.substring(1, 2)) == String(0)");
				STRRS485_CRC.remove(1, 1);
			}
		}

		/*Serial.print("STRRS485_CRC = ");
		Serial.println(STRRS485_CRC);
		Serial.print("strrs485_crc = ");
		Serial.println(strrs485_crc);*/

		//str.equals用于验证两个字符串是否相等，相同返回真，不同返回假
		if (STRRS485_CRC == strrs485_crc)
		{
			//Serial.println("crc校验通过");

			String strbcd;
			//char const *c = str.c_str();
			strbcd = String(RS485REceive_Data[3], BIN);
			int strbcd_length = strbcd.length();
			/*Serial.print("strbcd = ");
			Serial.println(strbcd);*/

			//数组创建为9位是为了将/0包含，方便getBytes处理
			unsigned char shuzu1[9] = { '0','0','0','0','0','0','0','0',0 };//用来存放getbytes处理后的数据
			unsigned char shu1zu[9] = { '0','0','0','0','0','0','0','0',0 };//用来反序的数组，一个桶
			unsigned char shuzu2[9] = { '0','0','0','0','0','0','0','0',0 };//反序后存放真正需要数据的数组
			//unsigned char shuzu1[8] = { '0','0','0','0','0','0','0','0'};//用来存放getbytes处理后的数据
			//unsigned char shu1zu[8] = { '0','0','0','0','0','0','0','0'};//用来反序的数组，一个桶
			//unsigned char shuzu2[8] = { '0','0','0','0','0','0','0','0'};//反序后存放真正需要数据的数组

			/*for (int i = 0; i < 8; i++)
			{
				Serial.print(String("shuzu2") + "[ " + i + " ] =");
				Serial.println(shuzu2[i]);
			}
			Serial.println("--------------------------");*/

			strbcd.getBytes(shuzu1, 9);//只能处理到8个字符，因为结尾需要处理/0 
			for (int i = 0; i < strbcd_length; i++)
			{
				/*Serial.print(String("shuzu1") + "[ " + i + " ] =");
				Serial.println(shuzu1[i]);*/
				shu1zu[strbcd_length - (i + 1)] = shuzu1[i];//倒序
				//shuzu2[i] = shuzu1[i];
				delay(5);
			}
			//Serial.println("--------------------------");
			for (int i = 0; i < strbcd_length; i++)
			{
				/*Serial.print(String("shu1zu") + "[ " + i + " ] =");
				Serial.println(shu1zu[i]);*/
				shuzu2[i] = shu1zu[i];
			}
			//Serial.println();
			//Serial.println("=====================");
			/*for (int i = 0; i < 8; i++)
			{
				Serial.print(String("shuzu2") + "[ " + i + " ] =");
				Serial.println(shuzu2[i]);
			}*/

			Status = shuzu2[x - 1] - '0';

			RS485REceive_Length = 0;

			return Status;
		}
	}
	return -1;
}

int LORAReceive_information(void)
{
	return 0;
}

int USB_Serial_reception(void)
{
	USBREceive_Length = 0;
	while (Serial.available() > 0)
	{
		USBREceive_Data[USBREceive_Length++] = Serial.read();
	}
	if (USBREceive_Length > 0)
	{
		//Serial.print(String("USB REceive_Data = "));//输出USB接收数据的长度
		//Serial.println(USBREceive_Length);

		//Serial.println("USB串口接收到的数据为：");

		//for (int i = 0; i < USBREceive_Length; i++)
		//{
		//	//Serial.print(String("USBREceive_Data") + "[ " + i + " ] ");
		//	Serial.print(USBREceive_Data[i], HEX);
		//	Serial.print("");
		//}
		//Serial.println("");

		USB_Judge(USBREceive_Data);//进入USB_Judge函数
	}
	return 0;
}
void USB_Judge(unsigned char *USBREceive_Data)
{
	//if (USBREceive_Data[0] == '3' && USBREceive_Data[1] == '_' && USBREceive_Data[2] == '2')
	//{
	//	Serial.println("输入的指令为Temp3_2");

	//	modbus_CRC = N_CRC16(Temp3_2, length);//得到modbus_CRC的值
	//	Temp3_2[6] = modbus_CRC >> 8;
	//	Temp3_2[7] = modbus_CRC;

	//	Serial2.write(Temp3_2, 8);//发送Temp3_2
	//}
	//else if (USBREceive_Data[0] == '4' && USBREceive_Data[1] == '_' && USBREceive_Data[2] == '2')
	//{
	//	Serial.println("输入的指令为Temp4_2");

	//	modbus_CRC = N_CRC16(Temp4_2, length);//得到modbus_CRC的值
	//	Temp4_2[6] = modbus_CRC >> 8;
	//	Temp4_2[7] = modbus_CRC;

	//	Serial2.write(Temp4_2, 8);//发送Temp4_2
	//}

	//这是测试模拟输入的代码
	if (USBREceive_Data[0] == 'V' && USBREceive_Data[1] == '1')
	{
		Analog_input1();
	}

	//========================================================================================================
	if (USBREceive_Data[0] == 'S' && USBREceive_Data[1] == 'E' && USBREceive_Data[2] == 'T' &&
		USBREceive_Data[3] == '_')
		//在这里判断进入了SET的命令
	{
		if (USBREceive_Data[4] == 'M' && USBREceive_Data[5] == 'a' && USBREceive_Data[6] == 'c' &&
			USBREceive_Data[7] == 'V' && USBREceive_Data[8] == 'a' && USBREceive_Data[9] == 'l' &&
			USBREceive_Data[10] == 'v' && USBREceive_Data[11] == 'e' && USBREceive_Data[12] == '_')
			//在这里判断进入了继电器的设置
		{
			if ((USBREceive_Data[15] == 'O' && USBREceive_Data[16] == 'N') || (USBREceive_Data[16] == 'O' && USBREceive_Data[17] == 'N'))
				//在这里判断进入了ON的指令
			{
				if (USBREceive_Data[13] == '1' && USBREceive_Data[14] == '_')
					//在这里判断进入了1继电器开
				{
					//Serial.println("输入的指令为Y0_ON");

					modbus_CRC = N_CRC16(Y0_ON, length);//得到modbus_CRC的值
					Y0_ON[6] = modbus_CRC >> 8;
					Y0_ON[7] = modbus_CRC;

					Serial2.write(Y0_ON, 8);//发送Y0_ON

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_1_ON");//回执信息
					}
					else
					{

					}
				}
				else if (USBREceive_Data[13] == '2' && USBREceive_Data[14] == '_')
					//在这里判断进入了2继电器开
				{
					//Serial.println("输入的指令为Y1_ON");

					modbus_CRC = N_CRC16(Y1_ON, length);//得到modbus_CRC的值
					Y1_ON[6] = modbus_CRC >> 8;
					Y1_ON[7] = modbus_CRC;

					Serial2.write(Y1_ON, 8);//发送Y1_ON

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_2_ON");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '3' && USBREceive_Data[14] == '_')
					//在这里判断进入了3继电器开
				{
					//Serial.println("输入的指令为Y2_ON");

					modbus_CRC = N_CRC16(Y2_ON, length);//得到modbus_CRC的值
					Y2_ON[6] = modbus_CRC >> 8;
					Y2_ON[7] = modbus_CRC;

					Serial2.write(Y2_ON, 8);//发送Y2_ON

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_3_ON");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '4' && USBREceive_Data[14] == '_')
					//在这里判断进入了4继电器开
				{
					//Serial.println("输入的指令为Y3_ON");

					modbus_CRC = N_CRC16(Y3_ON, length);//得到modbus_CRC的值
					Y3_ON[6] = modbus_CRC >> 8;
					Y3_ON[7] = modbus_CRC;

					Serial2.write(Y3_ON, 8);//发送Y3_ON

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_4_ON");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '5' && USBREceive_Data[14] == '_')
					//在这里判断进入了5继电器开
				{
					//Serial.println("输入的指令为Y4_ON");

					modbus_CRC = N_CRC16(Y4_ON, length);//得到modbus_CRC的值
					Y4_ON[6] = modbus_CRC >> 8;
					Y4_ON[7] = modbus_CRC;

					Serial2.write(Y4_ON, 8);//发送Y4_ON

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_5_ON");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '6' && USBREceive_Data[14] == '_')
					//在这里判断进入了6继电器开
				{
					//Serial.println("输入的指令为Y5_ON");

					modbus_CRC = N_CRC16(Y5_ON, length);//得到modbus_CRC的值
					Y5_ON[6] = modbus_CRC >> 8;
					Y5_ON[7] = modbus_CRC;

					Serial2.write(Y5_ON, 8);//发送Y5_ON

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_6_ON");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '7' && USBREceive_Data[14] == '_')
					//在这里判断进入了7继电器开
				{
					//Serial.println("输入的指令为Y6_ON");

					modbus_CRC = N_CRC16(Y6_ON, length);//得到modbus_CRC的值
					Y6_ON[6] = modbus_CRC >> 8;
					Y6_ON[7] = modbus_CRC;

					Serial2.write(Y6_ON, 8);//发送Y6_ON

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_7_ON");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '8' && USBREceive_Data[14] == '_')
					//在这里判断进入了8继电器开
				{
					//Serial.println("输入的指令为Y7_ON");

					modbus_CRC = N_CRC16(Y7_ON, length);//得到modbus_CRC的值
					Y7_ON[6] = modbus_CRC >> 8;
					Y7_ON[7] = modbus_CRC;

					Serial2.write(Y7_ON, 8);//发送Y7_ON

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_8_ON");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '9' && USBREceive_Data[14] == '_')
					//在这里判断进入了9继电器开
				{
					//Serial.println("输入的指令为Y8_ON");

					modbus_CRC = N_CRC16(Y8_ON, length);//得到modbus_CRC的值
					Y8_ON[6] = modbus_CRC >> 8;
					Y8_ON[7] = modbus_CRC;

					Serial2.write(Y8_ON, 8);//发送Y8_ON

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_9_ON");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '1' && USBREceive_Data[14] == '0' && USBREceive_Data[15] == '_')
					//在这里判断进入了10继电器开
				{
					//Serial.println("输入的指令为Y9_ON");

					modbus_CRC = N_CRC16(Y9_ON, length);//得到modbus_CRC的值
					Y9_ON[6] = modbus_CRC >> 8;
					Y9_ON[7] = modbus_CRC;

					Serial2.write(Y9_ON, 8);//发送Y9_ON

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_10_ON");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '1' && USBREceive_Data[14] == '1' && USBREceive_Data[15] == '_')
					//在这里判断进入了11继电器开
				{
					//Serial.println("输入的指令为Y10_ON");

					modbus_CRC = N_CRC16(Y10_ON, length);//得到modbus_CRC的值
					Y10_ON[6] = modbus_CRC >> 8;
					Y10_ON[7] = modbus_CRC;

					Serial2.write(Y10_ON, 8);//发送Y10_ON

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_11_ON");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '1' && USBREceive_Data[14] == '2' && USBREceive_Data[15] == '_')
					//在这里判断进入了12继电器开
				{
					//Serial.println("输入的指令为Y11_ON");

					modbus_CRC = N_CRC16(Y11_ON, length);//得到modbus_CRC的值
					Y11_ON[6] = modbus_CRC >> 8;
					Y11_ON[7] = modbus_CRC;

					Serial2.write(Y11_ON, 8);//发送Y11_ON

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_12_ON");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '1' && USBREceive_Data[14] == '3' && USBREceive_Data[15] == '_')
					//在这里判断进入了13继电器开
				{
					//Serial.println("输入的指令为Y12_ON");

					modbus_CRC = N_CRC16(Y12_ON, length);//得到modbus_CRC的值
					Y12_ON[6] = modbus_CRC >> 8;
					Y12_ON[7] = modbus_CRC;

					Serial2.write(Y12_ON, 8);//发送Y12_ON

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_13_ON");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '1' && USBREceive_Data[14] == '4' && USBREceive_Data[15] == '_')
					//在这里判断进入了14继电器开
				{
					//Serial.println("输入的指令为Y13_ON");

					modbus_CRC = N_CRC16(Y13_ON, length);//得到modbus_CRC的值
					Y13_ON[6] = modbus_CRC >> 8;
					Y13_ON[7] = modbus_CRC;

					Serial2.write(Y13_ON, 8);//发送Y13_ON

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_14_ON");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '1' && USBREceive_Data[14] == '5' && USBREceive_Data[15] == '_')
					//在这里判断进入了15继电器开
				{
					//Serial.println("输入的指令为Y14_ON");

					modbus_CRC = N_CRC16(Y14_ON, length);//得到modbus_CRC的值
					Y14_ON[6] = modbus_CRC >> 8;
					Y14_ON[7] = modbus_CRC;

					Serial2.write(Y14_ON, 8);//发送Y14_ON

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_15_ON");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '1' && USBREceive_Data[14] == '6' && USBREceive_Data[15] == '_')
					//在这里判断进入了16继电器开
				{
					//Serial.println("输入的指令为Y15_ON");

					modbus_CRC = N_CRC16(Y15_ON, length);//得到modbus_CRC的值
					Y15_ON[6] = modbus_CRC >> 8;
					Y15_ON[7] = modbus_CRC;

					Serial2.write(Y15_ON, 8);//发送Y15_ON

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_16_ON");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '1' && USBREceive_Data[14] == '7' && USBREceive_Data[15] == '_')
					//在这里判断进入了17继电器开
				{
					//Serial.println("输入的指令为Y16_ON");

					modbus_CRC = N_CRC16(Y16_ON, length);//得到modbus_CRC的值
					Y16_ON[6] = modbus_CRC >> 8;
					Y16_ON[7] = modbus_CRC;

					Serial2.write(Y16_ON, 8);//发送Y16_ON

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_17_ON");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '1' && USBREceive_Data[14] == '8' && USBREceive_Data[15] == '_')
					//在这里判断进入了18继电器开
				{
					//Serial.println("输入的指令为Y17_ON");

					modbus_CRC = N_CRC16(Y17_ON, length);//得到modbus_CRC的值
					Y17_ON[6] = modbus_CRC >> 8;
					Y17_ON[7] = modbus_CRC;

					Serial2.write(Y17_ON, 8);//发送Y17_ON

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_18_ON");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '1' && USBREceive_Data[14] == '9' && USBREceive_Data[15] == '_')
					//在这里判断进入了19继电器开
				{
					//Serial.println("输入的指令为Y18_ON");

					modbus_CRC = N_CRC16(Y18_ON, length);//得到modbus_CRC的值
					Y18_ON[6] = modbus_CRC >> 8;
					Y18_ON[7] = modbus_CRC;

					Serial2.write(Y18_ON, 8);//发送Y18_ON

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_19_ON");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '2' && USBREceive_Data[14] == '0' && USBREceive_Data[15] == '_')
					//在这里判断进入了20继电器开
				{
					//Serial.println("输入的指令为Y19_ON");

					modbus_CRC = N_CRC16(Y19_ON, length);//得到modbus_CRC的值
					Y19_ON[6] = modbus_CRC >> 8;
					Y19_ON[7] = modbus_CRC;

					Serial2.write(Y19_ON, 8);//发送Y19_ON

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_20_ON");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '2' && USBREceive_Data[14] == '1' && USBREceive_Data[15] == '_')
					//在这里判断进入了21继电器开
				{
					//Serial.println("输入的指令为Y20_ON");

					modbus_CRC = N_CRC16(Y20_ON, length);//得到modbus_CRC的值
					Y20_ON[6] = modbus_CRC >> 8;
					Y20_ON[7] = modbus_CRC;

					Serial2.write(Y20_ON, 8);//发送Y20_ON

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_21_ON");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '2' && USBREceive_Data[14] == '2' && USBREceive_Data[15] == '_')
					//在这里判断进入了22继电器开
				{
					//Serial.println("输入的指令为Y21_ON");

					modbus_CRC = N_CRC16(Y21_ON, length);//得到modbus_CRC的值
					Y21_ON[6] = modbus_CRC >> 8;
					Y21_ON[7] = modbus_CRC;

					Serial2.write(Y21_ON, 8);//发送Y21_ON

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_22_ON");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '2' && USBREceive_Data[14] == '3' && USBREceive_Data[15] == '_')
					//在这里判断进入了23继电器开
				{
					//Serial.println("输入的指令为Y22_ON");

					modbus_CRC = N_CRC16(Y22_ON, length);//得到modbus_CRC的值
					Y22_ON[6] = modbus_CRC >> 8;
					Y22_ON[7] = modbus_CRC;

					Serial2.write(Y22_ON, 8);//发送Y22_ON

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_23_ON");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '2' && USBREceive_Data[14] == '4' && USBREceive_Data[15] == '_')
					//在这里判断进入了24继电器开
				{
					//Serial.println("输入的指令为Y23_ON");

					modbus_CRC = N_CRC16(Y23_ON, length);//得到modbus_CRC的值
					Y23_ON[6] = modbus_CRC >> 8;
					Y23_ON[7] = modbus_CRC;

					Serial2.write(Y23_ON, 8);//发送Y23_ON

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_24_ON");//回执信息
					}
				}
			}

			//在这里判断进入了OFF命令
			else if ((USBREceive_Data[15] == 'O' && USBREceive_Data[16] == 'F' && USBREceive_Data[17] == 'F') ||
				(USBREceive_Data[16] == 'O' && USBREceive_Data[17] == 'F' && USBREceive_Data[18] == 'F'))
			{
				if (USBREceive_Data[13] == '1' && USBREceive_Data[14] == '_')
					//在这里判断进入了1继电器关
				{
					//Serial.println("输入的指令为Y0_OFF");

					modbus_CRC = N_CRC16(Y0_OFF, length);//得到modbus_CRC的值
					Y0_OFF[6] = modbus_CRC >> 8;
					Y0_OFF[7] = modbus_CRC;

					Serial2.write(Y0_OFF, 8);//发送Y0_OFF
					modbus_CRC = RS485Receive_information();

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_1_OFF");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '2' && USBREceive_Data[14] == '_')
					//在这里判断进入了2继电器关
				{
					//Serial.println("输入的指令为Y1_OFF");

					modbus_CRC = N_CRC16(Y1_OFF, length);//得到modbus_CRC的值
					Y1_OFF[6] = modbus_CRC >> 8;
					Y1_OFF[7] = modbus_CRC;

					Serial2.write(Y1_OFF, 8);//发送Y1_OFF

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_2_OFF");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '3' && USBREceive_Data[14] == '_')
					//在这里判断进入了3继电器关
				{
					//Serial.println("输入的指令为Y2_OFF");

					modbus_CRC = N_CRC16(Y2_OFF, length);//得到modbus_CRC的值
					Y2_OFF[6] = modbus_CRC >> 8;
					Y2_OFF[7] = modbus_CRC;

					Serial2.write(Y2_OFF, 8);//发送Y2_OFF

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_3_OFF");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '4' && USBREceive_Data[14] == '_')
					//在这里判断进入了4继电器关
				{
					//Serial.println("输入的指令为Y3_OFF");

					modbus_CRC = N_CRC16(Y3_OFF, length);//得到modbus_CRC的值
					Y3_OFF[6] = modbus_CRC >> 8;
					Y3_OFF[7] = modbus_CRC;

					Serial2.write(Y3_OFF, 8);//发送Y3_OFF

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_4_OFF");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '5' && USBREceive_Data[14] == '_')
					//在这里判断进入了5继电器关
				{
					//Serial.println("输入的指令为Y4_OFF");

					modbus_CRC = N_CRC16(Y4_OFF, length);//得到modbus_CRC的值
					Y4_OFF[6] = modbus_CRC >> 8;
					Y4_OFF[7] = modbus_CRC;

					Serial2.write(Y4_OFF, 8);//发送Y4_OFF

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_5_OFF");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '6' && USBREceive_Data[14] == '_')
					//在这里判断进入了6继电器关
				{
					//Serial.println("输入的指令为Y5_OFF");

					modbus_CRC = N_CRC16(Y5_OFF, length);//得到modbus_CRC的值
					Y5_OFF[6] = modbus_CRC >> 8;
					Y5_OFF[7] = modbus_CRC;

					Serial2.write(Y5_OFF, 8);//发送Y5_OFF

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_6_OFF");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '7' && USBREceive_Data[14] == '_')
					//在这里判断进入了7继电器关
				{
					//Serial.println("输入的指令为Y6_OFF");

					modbus_CRC = N_CRC16(Y6_OFF, length);//得到modbus_CRC的值
					Y6_OFF[6] = modbus_CRC >> 8;
					Y6_OFF[7] = modbus_CRC;

					Serial2.write(Y6_OFF, 8);//发送Y6_OFF

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_7_OFF");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '8' && USBREceive_Data[14] == '_')
					//在这里判断进入了8继电器关
				{
					//Serial.println("输入的指令为Y7_OFF");

					modbus_CRC = N_CRC16(Y7_OFF, length);//得到modbus_CRC的值
					Y7_OFF[6] = modbus_CRC >> 8;
					Y7_OFF[7] = modbus_CRC;

					Serial2.write(Y7_OFF, 8);//发送Y7_OFF

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_8_OFF");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '9' && USBREceive_Data[14] == '_')
					//在这里判断进入了9继电器关
				{
					//Serial.println("输入的指令为Y8_OFF");

					modbus_CRC = N_CRC16(Y8_OFF, length);//得到modbus_CRC的值
					Y8_OFF[6] = modbus_CRC >> 8;
					Y8_OFF[7] = modbus_CRC;

					Serial2.write(Y8_OFF, 8);//发送Y8_OFF

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_9_OFF");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '1' && USBREceive_Data[14] == '0' && USBREceive_Data[15] == '_')
					//在这里判断进入了10继电器关
				{
					//Serial.println("输入的指令为Y9_OFF");

					modbus_CRC = N_CRC16(Y9_OFF, length);//得到modbus_CRC的值
					Y9_OFF[6] = modbus_CRC >> 8;
					Y9_OFF[7] = modbus_CRC;

					Serial2.write(Y9_OFF, 8);//发送Y9_OFF

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_10_OFF");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '1' && USBREceive_Data[14] == '1' && USBREceive_Data[15] == '_')
					//在这里判断进入了11继电器关
				{
					//Serial.println("输入的指令为Y10_OFF");

					modbus_CRC = N_CRC16(Y10_OFF, length);//得到modbus_CRC的值
					Y10_OFF[6] = modbus_CRC >> 8;
					Y10_OFF[7] = modbus_CRC;

					Serial2.write(Y10_OFF, 8);//发送Y10_OFF

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_11_OFF");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '1' && USBREceive_Data[14] == '2' && USBREceive_Data[15] == '_')
					//在这里判断进入了12继电器关
				{
					//Serial.println("输入的指令为Y11_OFF");

					modbus_CRC = N_CRC16(Y11_OFF, length);//得到modbus_CRC的值
					Y11_OFF[6] = modbus_CRC >> 8;
					Y11_OFF[7] = modbus_CRC;

					Serial2.write(Y11_OFF, 8);//发送Y11_OFF

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_12_OFF");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '1' && USBREceive_Data[14] == '3' && USBREceive_Data[15] == '_')
					//在这里判断进入了13继电器关
				{
					//Serial.println("输入的指令为Y12_OFF");

					modbus_CRC = N_CRC16(Y12_OFF, length);//得到modbus_CRC的值
					Y12_OFF[6] = modbus_CRC >> 8;
					Y12_OFF[7] = modbus_CRC;

					Serial2.write(Y12_OFF, 8);//发送Y12_OFF

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_13_OFF");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '1' && USBREceive_Data[14] == '4' && USBREceive_Data[15] == '_')
					//在这里判断进入了14继电器关
				{
					//Serial.println("输入的指令为Y13_OFF");

					modbus_CRC = N_CRC16(Y13_OFF, length);//得到modbus_CRC的值
					Y13_OFF[6] = modbus_CRC >> 8;
					Y13_OFF[7] = modbus_CRC;

					Serial2.write(Y13_OFF, 8);//发送Y13_OFF

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_14_OFF");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '1' && USBREceive_Data[14] == '5' && USBREceive_Data[15] == '_')
					//在这里判断进入了15继电器关
				{
					//Serial.println("输入的指令为Y14_OFF");

					modbus_CRC = N_CRC16(Y14_OFF, length);//得到modbus_CRC的值
					Y14_OFF[6] = modbus_CRC >> 8;
					Y14_OFF[7] = modbus_CRC;

					Serial2.write(Y14_OFF, 8);//发送Y14_OFF

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_15_OFF");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '1' && USBREceive_Data[14] == '6' && USBREceive_Data[15] == '_')
					//在这里判断进入了16继电器关
				{
					//Serial.println("输入的指令为Y15_OFF");

					modbus_CRC = N_CRC16(Y15_OFF, length);//得到modbus_CRC的值
					Y15_OFF[6] = modbus_CRC >> 8;
					Y15_OFF[7] = modbus_CRC;

					Serial2.write(Y15_OFF, 8);//发送Y15_OFF

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_16_OFF");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '1' && USBREceive_Data[14] == '7' && USBREceive_Data[15] == '_')
					//在这里判断进入了17继电器关
				{
					//Serial.println("输入的指令为Y16_OFF");

					modbus_CRC = N_CRC16(Y16_OFF, length);//得到modbus_CRC的值
					Y16_OFF[6] = modbus_CRC >> 8;
					Y16_OFF[7] = modbus_CRC;

					Serial2.write(Y16_OFF, 8);//发送Y16_OFF

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_17_OFF");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '1' && USBREceive_Data[14] == '8' && USBREceive_Data[15] == '_')
					//在这里判断进入了18继电器关
				{
					//Serial.println("输入的指令为Y17_OFF");

					modbus_CRC = N_CRC16(Y17_OFF, length);//得到modbus_CRC的值
					Y17_OFF[6] = modbus_CRC >> 8;
					Y17_OFF[7] = modbus_CRC;

					Serial2.write(Y17_OFF, 8);//发送Y17_OFF

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_18_OFF");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '1' && USBREceive_Data[14] == '9' && USBREceive_Data[15] == '_')
					//在这里判断进入了19继电器关
				{
					//Serial.println("输入的指令为Y18_OFF");

					modbus_CRC = N_CRC16(Y18_OFF, length);//得到modbus_CRC的值
					Y18_OFF[6] = modbus_CRC >> 8;
					Y18_OFF[7] = modbus_CRC;

					Serial2.write(Y18_OFF, 8);//发送Y18_OFF

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_19_OFF");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '2' && USBREceive_Data[14] == '0' && USBREceive_Data[15] == '_')
					//在这里判断进入了20继电器关
				{
					//Serial.println("输入的指令为Y19_OFF");

					modbus_CRC = N_CRC16(Y19_OFF, length);//得到modbus_CRC的值
					Y19_OFF[6] = modbus_CRC >> 8;
					Y19_OFF[7] = modbus_CRC;

					Serial2.write(Y19_OFF, 8);//发送Y19_OFF

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_20_OFF");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '2' && USBREceive_Data[14] == '1' && USBREceive_Data[15] == '_')
					//在这里判断进入了21继电器关
				{
					//Serial.println("输入的指令为Y20_OFF");

					modbus_CRC = N_CRC16(Y20_OFF, length);//得到modbus_CRC的值
					Y20_OFF[6] = modbus_CRC >> 8;
					Y20_OFF[7] = modbus_CRC;

					Serial2.write(Y20_OFF, 8);//发送Y20_OFF

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_21_OFF");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '2' && USBREceive_Data[14] == '2' && USBREceive_Data[15] == '_')
					//在这里判断进入了22继电器关
				{
					//Serial.println("输入的指令为Y21_OFF");

					modbus_CRC = N_CRC16(Y21_OFF, length);//得到modbus_CRC的值
					Y21_OFF[6] = modbus_CRC >> 8;
					Y21_OFF[7] = modbus_CRC;

					Serial2.write(Y21_OFF, 8);//发送Y21_OFF

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_22_OFF");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '2' && USBREceive_Data[14] == '3' && USBREceive_Data[15] == '_')
					//在这里判断进入了23继电器关
				{
					//Serial.println("输入的指令为Y22_OFF");

					modbus_CRC = N_CRC16(Y22_OFF, length);//得到modbus_CRC的值
					Y22_OFF[6] = modbus_CRC >> 8;
					Y22_OFF[7] = modbus_CRC;

					Serial2.write(Y22_OFF, 8);//发送Y22_OFF

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_23_OFF");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '2' && USBREceive_Data[14] == '4' && USBREceive_Data[15] == '_')
					//在这里判断进入了24继电器关
				{
					//Serial.println("输入的指令为Y23_OFF");

					modbus_CRC = N_CRC16(Y23_OFF, length);//得到modbus_CRC的值
					Y23_OFF[6] = modbus_CRC >> 8;
					Y23_OFF[7] = modbus_CRC;

					Serial2.write(Y23_OFF, 8);//发送Y23_OFF

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println(String("RESP_MacValve_24_OFF"));//回执信息
					}
				}
			}
		}
		//判断进入了温控通道
		else if (USBREceive_Data[4] == 'H'	&& USBREceive_Data[5] == 'e'	&& USBREceive_Data[6] == 'a'	&&
				 USBREceive_Data[7] == 't'	&& USBREceive_Data[8] == 'i'	&& USBREceive_Data[9] == 'n'	&&
				 USBREceive_Data[10] == 'g'	&& USBREceive_Data[11] == 'J'	&& USBREceive_Data[12] == 'a'	&&
				 USBREceive_Data[13] == 'c'	&& USBREceive_Data[14] == 'k'	&& USBREceive_Data[15] == 'e'	&&
				 USBREceive_Data[16] == 't'	&& USBREceive_Data[17] == 's'	&& USBREceive_Data[18] == '_')
		{
			//判断进入设置通道的温度值
			if ((USBREceive_Data[21] == 'T'	&& USBREceive_Data[22] == 'e'	&& USBREceive_Data[23] == 'm'	&&
				 USBREceive_Data[24] == 'p'	&& USBREceive_Data[25] == 'D'	&& USBREceive_Data[26] == 'e'	&&
				 USBREceive_Data[27] == 's'	&& USBREceive_Data[28] == 'i'	&& USBREceive_Data[29] == 'r'	&&
				 USBREceive_Data[30] == 'e'	&& USBREceive_Data[31] == 'd'	&& USBREceive_Data[32] == '_')  ||
				(USBREceive_Data[22] == 'T'	&& USBREceive_Data[23] == 'e'	&& USBREceive_Data[24] == 'm'	&&
				 USBREceive_Data[25] == 'p'	&& USBREceive_Data[26] == 'D'	&& USBREceive_Data[27] == 'e'	&&
				 USBREceive_Data[28] == 's'	&& USBREceive_Data[29] == 'i'	&& USBREceive_Data[30] == 'r'	&&
				 USBREceive_Data[31] == 'e'	&& USBREceive_Data[32] == 'd'	&& USBREceive_Data[33] == '_'))
			{
				//判断进入了1通道的温度期望设定
				if (USBREceive_Data[19] == '1' && USBREceive_Data[20] == '_')
				{
					TempDesired = ((USBREceive_Data[33] - 48) * 1000) + ((USBREceive_Data[34] - 48) * 100) + ((USBREceive_Data[35] - 48) * 10) + (USBREceive_Data[36] - 48);
					//Serial.print("TempDesired = ");//输出TempDesired
					//Serial.println(TempDesired);

					ptrc = Character_processing(TempDesired);//输出TempDesired

					Temp3_1[4] = *(ptrc + 0);
					/*Serial.print("Temp3_1[4] = ");
					Serial.println(Temp3_1[4]);*/
					Temp3_1[5] = *(ptrc + 1);
					/*Serial.print("Temp3_1[5] = ");
					Serial.println(Temp3_1[5]);*/

					modbus_CRC = N_CRC16(Temp3_1, length);//得到modbus_CRC的值
					Temp3_1[6] = modbus_CRC >> 8;
					Temp3_1[7] = modbus_CRC;

					Serial2.write(Temp3_1, 8);//发送Temp3_1

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println(String("RESP_HeatingJackets_1_TempDesired_OK"));//回执信息
					}
				}
				//判断进入了2通道温度期望的设定
				else if (USBREceive_Data[19] == '2' && USBREceive_Data[20] == '_')
				{
					TempDesired = ((USBREceive_Data[33] - 48) * 1000) + ((USBREceive_Data[34] - 48) * 100) + ((USBREceive_Data[35] - 48) * 10) + (USBREceive_Data[36] - 48);
					//Serial.print("TempDesired = ");//输出TempDesired
					//Serial.println(TempDesired);

					ptrc = Character_processing(TempDesired);//输出TempDesired

					Temp3_2[4] = *(ptrc + 0);
					/*Serial.print("Temp3_1[4] = ");
					Serial.println(Temp3_1[4]);*/
					Temp3_2[5] = *(ptrc + 1);
					/*Serial.print("Temp3_1[5] = ");
					Serial.println(Temp3_1[5]);*/

					modbus_CRC = N_CRC16(Temp3_2, length);//得到modbus_CRC的值
					Temp3_2[6] = modbus_CRC >> 8;
					Temp3_2[7] = modbus_CRC;

					Serial2.write(Temp3_2, 8);//发送Temp3_2

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println(String("RESP_HeatingJackets_2_TempDesired_OK"));//回执信息
					}
				}
				//判断进入了3通道温度期望的设定
				else if (USBREceive_Data[19] == '3' && USBREceive_Data[20] == '_')
				{
					TempDesired = ((USBREceive_Data[33] - 48) * 1000) + ((USBREceive_Data[34] - 48) * 100) + ((USBREceive_Data[35] - 48) * 10) + (USBREceive_Data[36] - 48);
					//Serial.print("TempDesired = ");//输出TempDesired
					//Serial.println(TempDesired);

					ptrc = Character_processing(TempDesired);//输出TempDesired

					Temp3_3[4] = *(ptrc + 0);
					/*Serial.print("Temp3_1[4] = ");
					Serial.println(Temp3_1[4]);*/
					Temp3_3[5] = *(ptrc + 1);
					/*Serial.print("Temp3_1[5] = ");
					Serial.println(Temp3_1[5]);*/

					modbus_CRC = N_CRC16(Temp3_3, length);//得到modbus_CRC的值
					Temp3_3[6] = modbus_CRC >> 8;
					Temp3_3[7] = modbus_CRC;

					Serial2.write(Temp3_3, 8);//发送Temp3_3

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println(String("RESP_HeatingJackets_3_TempDesired_OK"));//回执信息
					}
				}
				//判断进入了4通道温度期望的设定
				else if (USBREceive_Data[19] == '4' && USBREceive_Data[20] == '_')
				{
					TempDesired = ((USBREceive_Data[33] - 48) * 1000) + ((USBREceive_Data[34] - 48) * 100) + ((USBREceive_Data[35] - 48) * 10) + (USBREceive_Data[36] - 48);
					//Serial.print("TempDesired = ");//输出TempDesired
					//Serial.println(TempDesired);

					ptrc = Character_processing(TempDesired);//得到16进制的按字节的char数组

					Temp3_4[4] = *(ptrc + 0);
					/*Serial.print("Temp3_1[4] = ");
					Serial.println(Temp3_1[4]);*/
					Temp3_4[5] = *(ptrc + 1);
					/*Serial.print("Temp3_1[5] = ");
					Serial.println(Temp3_1[5]);*/

					modbus_CRC = N_CRC16(Temp3_4, length);//得到modbus_CRC的值
					Temp3_4[6] = modbus_CRC >> 8;
					Temp3_4[7] = modbus_CRC;

					Serial2.write(Temp3_4, 8);//发送Temp3_4

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println(String("RESP_HeatingJackets_4_TempDesired_OK"));//回执信息
					}
				}
				//判断进入了5通道温度期望的设定
				else if (USBREceive_Data[19] == '5' && USBREceive_Data[20] == '_')
				{
					TempDesired = ((USBREceive_Data[33] - 48) * 1000) + ((USBREceive_Data[34] - 48) * 100) + ((USBREceive_Data[35] - 48) * 10) + (USBREceive_Data[36] - 48);
					//Serial.print("TempDesired = ");//输出TempDesired
					//Serial.println(TempDesired);

					ptrc = Character_processing(TempDesired);//得到16进制的byte数组

					Temp3_5[4] = *(ptrc + 0);
					/*Serial.print("Temp3_1[4] = ");
					Serial.println(Temp3_1[4]);*/
					Temp3_5[5] = *(ptrc + 1);
					/*Serial.print("Temp3_1[5] = ");
					Serial.println(Temp3_1[5]);*/

					modbus_CRC = N_CRC16(Temp3_5, length);//得到modbus_CRC的值
					Temp3_5[6] = modbus_CRC >> 8;
					Temp3_5[7] = modbus_CRC;

					Serial2.write(Temp3_5, 8);//发送Temp3_5

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println(String("RESP_HeatingJackets_5_TempDesired_OK"));//回执信息
					}
				}
				//判断进入了6通道温度期望的设定
				else if (USBREceive_Data[19] == '6' && USBREceive_Data[20] == '_')
				{
					TempDesired = ((USBREceive_Data[33] - 48) * 1000) + ((USBREceive_Data[34] - 48) * 100) + ((USBREceive_Data[35] - 48) * 10) + (USBREceive_Data[36] - 48);
					//Serial.print("TempDesired = ");//输出TempDesired
					//Serial.println(TempDesired);

					ptrc = Character_processing(TempDesired);//得到16进制的byte数组

					Temp3_6[4] = *(ptrc + 0);
					/*Serial.print("Temp3_1[4] = ");
					Serial.println(Temp3_1[4]);*/
					Temp3_6[5] = *(ptrc + 1);
					/*Serial.print("Temp3_1[5] = ");
					Serial.println(Temp3_1[5]);*/

					modbus_CRC = N_CRC16(Temp3_6, length);//得到modbus_CRC的值
					Temp3_6[6] = modbus_CRC >> 8;
					Temp3_6[7] = modbus_CRC;

					Serial2.write(Temp3_6, 8);//发送Temp3_6

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println(String("RESP_HeatingJackets_6_TempDesired_OK"));//回执信息
					}
				}
				//判断进入了7通道温度期望的设定
				else if (USBREceive_Data[19] == '7' && USBREceive_Data[20] == '_')
				{
					TempDesired = ((USBREceive_Data[33] - 48) * 1000) + ((USBREceive_Data[34] - 48) * 100) + ((USBREceive_Data[35] - 48) * 10) + (USBREceive_Data[36] - 48);
					//Serial.print("TempDesired = ");//输出TempDesired
					//Serial.println(TempDesired);

					ptrc = Character_processing(TempDesired);//得到16进制的byte数组

					Temp3_7[4] = *(ptrc + 0);
					/*Serial.print("Temp3_1[4] = ");
					Serial.println(Temp3_1[4]);*/
					Temp3_7[5] = *(ptrc + 1);
					/*Serial.print("Temp3_1[5] = ");
					Serial.println(Temp3_1[5]);*/

					modbus_CRC = N_CRC16(Temp3_7, length);//得到modbus_CRC的值
					Temp3_7[6] = modbus_CRC >> 8;
					Temp3_7[7] = modbus_CRC;

					Serial2.write(Temp3_7, 8);//发送Temp3_7

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println(String("RESP_HeatingJackets_7_TempDesired_OK"));//回执信息
					}
				}
				//判断进入了8通道温度期望的设定
				else if (USBREceive_Data[19] == '8' && USBREceive_Data[20] == '_')
				{
					TempDesired = ((USBREceive_Data[33] - 48) * 1000) + ((USBREceive_Data[34] - 48) * 100) + ((USBREceive_Data[35] - 48) * 10) + (USBREceive_Data[36] - 48);
					//Serial.print("TempDesired = ");//输出TempDesired
					//Serial.println(TempDesired);

					ptrc = Character_processing(TempDesired);//得到16进制的byte数组

					Temp3_8[4] = *(ptrc + 0);
					/*Serial.print("Temp3_1[4] = ");
					Serial.println(Temp3_1[4]);*/
					Temp3_8[5] = *(ptrc + 1);
					/*Serial.print("Temp3_1[5] = ");
					Serial.println(Temp3_1[5]);*/

					modbus_CRC = N_CRC16(Temp3_8, length);//得到modbus_CRC的值
					Temp3_8[6] = modbus_CRC >> 8;
					Temp3_8[7] = modbus_CRC;

					Serial2.write(Temp3_8, 8);//发送Temp3_8

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println(String("RESP_HeatingJackets_8_TempDesired_OK"));//回执信息
					}
				}
				//判断进入了9通道温度期望的设定
				else if (USBREceive_Data[19] == '9' && USBREceive_Data[20] == '_')
				{
					TempDesired = ((USBREceive_Data[33] - 48) * 1000) + ((USBREceive_Data[34] - 48) * 100) + ((USBREceive_Data[35] - 48) * 10) + (USBREceive_Data[36] - 48);
					//Serial.print("TempDesired = ");//输出TempDesired
					//Serial.println(TempDesired);

					ptrc = Character_processing(TempDesired);//得到16进制的byte数组

					Temp4_1[4] = *(ptrc + 0);
					/*Serial.print("Temp3_1[4] = ");
					Serial.println(Temp3_1[4]);*/
					Temp4_1[5] = *(ptrc + 1);
					/*Serial.print("Temp3_1[5] = ");
					Serial.println(Temp3_1[5]);*/

					modbus_CRC = N_CRC16(Temp4_1, length);//得到modbus_CRC的值
					Temp4_1[6] = modbus_CRC >> 8;
					Temp4_1[7] = modbus_CRC;

					Serial2.write(Temp4_1, 8);//发送Temp4_1

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println(String("RESP_HeatingJackets_9_TempDesired_OK"));//回执信息
					}
				}
				//判断进入了10通道温度期望的设定
				else if (USBREceive_Data[19] == '1' && USBREceive_Data[20] == '0' && USBREceive_Data[21] == '_')
				{
					TempDesired = ((USBREceive_Data[34] - 48) * 1000) + ((USBREceive_Data[35] - 48) * 100) + ((USBREceive_Data[36] - 48) * 10) + (USBREceive_Data[37] - 48);
					//Serial.print("TempDesired = ");//输出TempDesired
					//Serial.println(TempDesired);

					ptrc = Character_processing(TempDesired);//得到16进制的byte数组

					Temp4_2[4] = *(ptrc + 0);
					/*Serial.print("Temp3_1[4] = ");
					Serial.println(Temp3_1[4]);*/
					Temp4_2[5] = *(ptrc + 1);
					/*Serial.print("Temp3_1[5] = ");
					Serial.println(Temp3_1[5]);*/

					modbus_CRC = N_CRC16(Temp4_2, length);//得到modbus_CRC的值
					Temp4_2[6] = modbus_CRC >> 8;
					Temp4_2[7] = modbus_CRC;

					Serial2.write(Temp4_2, 8);//发送Temp4_2

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println(String("RESP_HeatingJackets_10_TempDesired_OK"));//回执信息
					}
				}
				//判断进入了11通道温度期望的设定
				else if (USBREceive_Data[19] == '1' && USBREceive_Data[20] == '1' && USBREceive_Data[21] == '_')
				{
					TempDesired = ((USBREceive_Data[34] - 48) * 1000) + ((USBREceive_Data[35] - 48) * 100) + ((USBREceive_Data[36] - 48) * 10) + (USBREceive_Data[37] - 48);
					//Serial.print("TempDesired = ");//输出TempDesired
					//Serial.println(TempDesired);

					ptrc = Character_processing(TempDesired);//得到16进制的byte数组

					Temp4_3[4] = *(ptrc + 0);
					/*Serial.print("Temp3_1[4] = ");
					Serial.println(Temp3_1[4]);*/
					Temp4_3[5] = *(ptrc + 1);
					/*Serial.print("Temp3_1[5] = ");
					Serial.println(Temp3_1[5]);*/

					modbus_CRC = N_CRC16(Temp4_3, length);//得到modbus_CRC的值
					Temp4_3[6] = modbus_CRC >> 8;
					Temp4_3[7] = modbus_CRC;

					Serial2.write(Temp4_3, 8);//发送Temp4_3

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println(String("RESP_HeatingJackets_11_TempDesired_OK"));//回执信息
					}
				}
				//判断进入了12通道温度期望的设定
				else if (USBREceive_Data[19] == '1' && USBREceive_Data[20] == '2' && USBREceive_Data[21] == '_')
				{
					TempDesired = ((USBREceive_Data[34] - 48) * 1000) + ((USBREceive_Data[35] - 48) * 100) + ((USBREceive_Data[36] - 48) * 10) + (USBREceive_Data[37] - 48);
					//Serial.print("TempDesired = ");//输出TempDesired
					//Serial.println(TempDesired);

					ptrc = Character_processing(TempDesired);//得到16进制的byte数组

					Temp4_4[4] = *(ptrc + 0);
					/*Serial.print("Temp3_1[4] = ");
					Serial.println(Temp3_1[4]);*/
					Temp4_4[5] = *(ptrc + 1);
					/*Serial.print("Temp3_1[5] = ");
					Serial.println(Temp3_1[5]);*/

					modbus_CRC = N_CRC16(Temp4_4, length);//得到modbus_CRC的值
					Temp4_4[6] = modbus_CRC >> 8;
					Temp4_4[7] = modbus_CRC;

					Serial2.write(Temp4_4, 8);//发送Temp4_4

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println(String("RESP_HeatingJackets_12_TempDesired_OK"));//回执信息
					}
				}
				//判断进入了13通道温度期望的设定
				else if (USBREceive_Data[19] == '1' && USBREceive_Data[20] == '3' && USBREceive_Data[21] == '_')
				{
					TempDesired = ((USBREceive_Data[34] - 48) * 1000) + ((USBREceive_Data[35] - 48) * 100) + ((USBREceive_Data[36] - 48) * 10) + (USBREceive_Data[37] - 48);
					//Serial.print("TempDesired = ");//输出TempDesired
					//Serial.println(TempDesired);

					ptrc = Character_processing(TempDesired);//得到16进制的byte数组

					Temp4_5[4] = *(ptrc + 0);
					/*Serial.print("Temp3_1[4] = ");
					Serial.println(Temp3_1[4]);*/
					Temp4_5[5] = *(ptrc + 1);
					/*Serial.print("Temp3_1[5] = ");
					Serial.println(Temp3_1[5]);*/

					modbus_CRC = N_CRC16(Temp4_5, length);//得到modbus_CRC的值
					Temp4_5[6] = modbus_CRC >> 8;
					Temp4_5[7] = modbus_CRC;

					Serial2.write(Temp4_5, 8);//发送Temp4_5

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println(String("RESP_HeatingJackets_13_TempDesired_OK"));//回执信息
					}
				}
				//判断进入了14通道温度期望的设定
				else if (USBREceive_Data[19] == '1' && USBREceive_Data[20] == '4' && USBREceive_Data[21] == '_')
				{
					TempDesired = ((USBREceive_Data[34] - 48) * 1000) + ((USBREceive_Data[35] - 48) * 100) + ((USBREceive_Data[36] - 48) * 10) + (USBREceive_Data[37] - 48);
					//Serial.print("TempDesired = ");//输出TempDesired
					//Serial.println(TempDesired);

					ptrc = Character_processing(TempDesired);//得到16进制的byte数组

					Temp4_6[4] = *(ptrc + 0);
					/*Serial.print("Temp3_1[4] = ");
					Serial.println(Temp3_1[4]);*/
					Temp4_6[5] = *(ptrc + 1);
					/*Serial.print("Temp3_1[5] = ");
					Serial.println(Temp3_1[5]);*/

					modbus_CRC = N_CRC16(Temp4_6, length);//得到modbus_CRC的值
					Temp4_6[6] = modbus_CRC >> 8;
					Temp4_6[7] = modbus_CRC;

					Serial2.write(Temp4_6, 8);//发送Temp4_6

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println(String("RESP_HeatingJackets_14_TempDesired_OK"));//回执信息
					}
				}
				//判断进入了15通道温度期望的设定
				else if (USBREceive_Data[19] == '1' && USBREceive_Data[20] == '5' && USBREceive_Data[21] == '_')
				{
					TempDesired = ((USBREceive_Data[34] - 48) * 1000) + ((USBREceive_Data[35] - 48) * 100) + ((USBREceive_Data[36] - 48) * 10) + (USBREceive_Data[37] - 48);
					//Serial.print("TempDesired = ");//输出TempDesired
					//Serial.println(TempDesired);

					ptrc = Character_processing(TempDesired);//得到16进制的byte数组

					Temp4_7[4] = *(ptrc + 0);
					/*Serial.print("Temp3_1[4] = ");
					Serial.println(Temp3_1[4]);*/
					Temp4_7[5] = *(ptrc + 1);
					/*Serial.print("Temp3_1[5] = ");
					Serial.println(Temp3_1[5]);*/

					modbus_CRC = N_CRC16(Temp4_7, length);//得到modbus_CRC的值
					Temp4_7[6] = modbus_CRC >> 8;
					Temp4_7[7] = modbus_CRC;

					Serial2.write(Temp4_7, 8);//发送Temp4_7

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println(String("RESP_HeatingJackets_15_TempDesired_OK"));//回执信息
					}
				}
				//判断进入了16通道温度期望的设定
				else if (USBREceive_Data[19] == '1' && USBREceive_Data[20] == '6' && USBREceive_Data[21] == '_')
				{
					TempDesired = ((USBREceive_Data[34] - 48) * 1000) + ((USBREceive_Data[35] - 48) * 100) + ((USBREceive_Data[36] - 48) * 10) + (USBREceive_Data[37] - 48);
					//Serial.print("TempDesired = ");//输出TempDesired
					//Serial.println(TempDesired);

					ptrc = Character_processing(TempDesired);//得到16进制的byte数组

					Temp4_8[4] = *(ptrc + 0);
					/*Serial.print("Temp3_1[4] = ");
					Serial.println(Temp3_1[4]);*/
					Temp4_8[5] = *(ptrc + 1);
					/*Serial.print("Temp3_1[5] = ");
					Serial.println(Temp3_1[5]);*/

					modbus_CRC = N_CRC16(Temp4_8, length);//得到modbus_CRC的值
					Temp4_8[6] = modbus_CRC >> 8;
					Temp4_8[7] = modbus_CRC;

					Serial2.write(Temp4_8, 8);//发送Temp4_8

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println(String("RESP_HeatingJackets_16_TempDesired_OK"));//回执信息
					}
				}
			}
			//判断进入设置上限值
			else if (USBREceive_Data[19] == 'T'	&& USBREceive_Data[20] == 'e'	&& USBREceive_Data[21] == 'm'	&&
				USBREceive_Data[22] == 'p'	&& USBREceive_Data[23] == 'U'	&& USBREceive_Data[24] == 'p'	&&
				USBREceive_Data[25] == 'p'	&& USBREceive_Data[26] == 'L'	&& USBREceive_Data[27] == 'i'	&&
				USBREceive_Data[28] == 'm'	&& USBREceive_Data[29] == 'i'	&& USBREceive_Data[30] == 't'	&&
				USBREceive_Data[31] == '_')
			{
				TempUppLimit = ((USBREceive_Data[32] - 48) * 1000) + ((USBREceive_Data[33] - 48) * 100) + ((USBREceive_Data[34] - 48) * 10) + (USBREceive_Data[35] - 48);
				/*Serial.print("TempUppLimit = ");
				Serial.println(TempUppLimit);*/
			}
			//判断进入设置下限值
			else if (USBREceive_Data[19] == 'T'	&& USBREceive_Data[20] == 'e'	&& USBREceive_Data[21] == 'm'	&&
				USBREceive_Data[22] == 'p'	&& USBREceive_Data[23] == 'L'	&& USBREceive_Data[24] == 'o'	&&
				USBREceive_Data[25] == 'w'	&& USBREceive_Data[26] == 'L'	&& USBREceive_Data[27] == 'i'	&&
				USBREceive_Data[28] == 'm'	&& USBREceive_Data[29] == 'i'	&& USBREceive_Data[30] == 't'	&&
				USBREceive_Data[31] == '_')
			{
				TempLowLimit = ((USBREceive_Data[32] - 48) * 1000) + ((USBREceive_Data[33] - 48) * 100) + ((USBREceive_Data[34] - 48) * 10) + (USBREceive_Data[35] - 48);
				/*Serial.print("TempLowLimit = ");
				Serial.println(TempLowLimit);*/
			}
			//判断进入设置加热模式
			else if (USBREceive_Data[21] == 'H'	&& USBREceive_Data[22] == 'e'	&& USBREceive_Data[23] == 'a'	&&
				USBREceive_Data[24] == 't'	&& USBREceive_Data[25] == 'i'	&& USBREceive_Data[26] == 'n'	&&
				USBREceive_Data[27] == 'g'	&& USBREceive_Data[28] == '_')
			{
				//判断进入了1通道加热的设定
				if (USBREceive_Data[19] == '1' && USBREceive_Data[20] == '_')
				{

				}
				//判断进入了2通道加热的设定
				else if (USBREceive_Data[19] == '2' && USBREceive_Data[20] == '_')
				{

				}
			}
			//判断进入设置制冷模式
			else if (USBREceive_Data[21] == 'C'	&& USBREceive_Data[22] == 'o'	&& USBREceive_Data[23] == 'o'	&&
				USBREceive_Data[24] == 'l'	&& USBREceive_Data[25] == 'i'	&& USBREceive_Data[26] == 'n'	&&
				USBREceive_Data[27] == 'g'	&& USBREceive_Data[28] == '_')
			{
				//判断进入了1通道制冷的设定
				if (USBREceive_Data[19] == '1' && USBREceive_Data[20] == '_')
				{

				}
				//判断进入了2通道制冷的设定
				else if (USBREceive_Data[19] == '2' && USBREceive_Data[20] == '_')
				{

				}
			}
		}
		//这里判断进入了MFC的设置
		else if (USBREceive_Data[4] == 'M'	&& USBREceive_Data[5] == 'F'	&& USBREceive_Data[6] == 'C'	&&
				 USBREceive_Data[7] == '_')
		{
			//这里判断进入了MFC_OPEN
			if (USBREceive_Data[10] == 'O'	&& USBREceive_Data[11] == 'p'	&& USBREceive_Data[12] == 'e'	&&
				USBREceive_Data[13] == 'n')
			{
				if (USBREceive_Data[8] == '1' && USBREceive_Data[9] == '_')
				{
					digitalWrite(LED1, LOW);//控制开阀
					digitalWrite(LED2, HIGH);
					if (digitalRead(LED1) == LOW && digitalRead(LED2) == HIGH)
					{
						Serial.println(String("RESP_MFC_1_Open"));//回执信息
					}
				}
				else if (USBREceive_Data[8] == '2' && USBREceive_Data[9] == '_')
				{
					
					Serial.println(String("RESP_MFC_2_Open"));//回执信息
				}
				else if (USBREceive_Data[8] == '3' && USBREceive_Data[9] == '_')
				{
					
					Serial.println(String("RESP_MFC_3_Open"));//回执信息
				}
			}
			//这里判断进入了MFC_close
			else if (USBREceive_Data[10] == 'C'	&& USBREceive_Data[11] == 'l'	&& USBREceive_Data[12] == 'o'	&&
					 USBREceive_Data[13] == 's'	&& USBREceive_Data[14] == 'e')
			{
				if (USBREceive_Data[8] == '1' && USBREceive_Data[9] == '_')
				{
					digitalWrite(LED1, HIGH);
					digitalWrite(LED2, LOW);//控制关阀
					if (digitalRead(LED1) == HIGH && digitalRead(LED2) == LOW)
					{
						Serial.println(String("RESP_MFC_1_Close"));//回执信息
					}
				}
				else if (USBREceive_Data[8] == '2' && USBREceive_Data[9] == '_')
				{

					Serial.println(String("RESP_MFC_2_Close"));//回执信息
				}
				else if (USBREceive_Data[8] == '3' && USBREceive_Data[9] == '_')
				{

					Serial.println(String("RESP_MFC_3_Close"));//回执信息
				}
			}
			//这里判断进入了MFC_GAS
			else if (USBREceive_Data[10] == 'G'	&& USBREceive_Data[11] == 'A'	&& USBREceive_Data[12] == 'S'	&&
					 USBREceive_Data[13] == '_')
			{
				if (USBREceive_Data[8] == '1' && USBREceive_Data[9] == '_')
				{

					FlowDesired = ((USBREceive_Data[14] - 48) * 100000) + ((USBREceive_Data[15] - 48) * 10000) + ((USBREceive_Data[16] - 48) * 1000) + 
								  ((USBREceive_Data[17] - 48) * 100)	+ ((USBREceive_Data[18] - 48) * 10) +     (USBREceive_Data[19] - 48);
					//Serial.print("FlowDesired = ");//输出FlowDesired
					//Serial.println(FlowDesired);
					int flow_V = (FlowDesired*1024) / 50000;//((FlowDesired / 200000) * 5000)*(4096/5000)
					//Serial.print("flow_V = ");//输出FlowDesired
					//Serial.println(flow_V);
					ptrc = Character_processing(flow_V);//输出FlowDesired

					AnalogV_output1[4] = *(ptrc + 0);
					/*Serial.print("AnalogV_output1[4] = ");
					Serial.println(AnalogV_output1[4],HEX);*/
					AnalogV_output1[5] = *(ptrc + 1);
					/*Serial.print("AnalogV_output1[5] = ");
					Serial.println(AnalogV_output1[5],HEX);*/

					modbus_CRC = N_CRC16(AnalogV_output1, length);//得到modbus_CRC的值
					AnalogV_output1[6] = modbus_CRC >> 8;
					AnalogV_output1[7] = modbus_CRC;

					Serial2.write(AnalogV_output1, 8);//发送AnalogV_output1

					if (RS485Receive_information() == modbus_CRC)
					{
						Serial.println(String("RESP_MFC_1_GAS_") + String(FlowDesired));//回执信息
					}
					for (size_t i = 0; i < 19; i++)
					{
						USBREceive_Data[i] = 0;//将数值清零
					}
				}
			}
		}
	}
	//这里判断进入了GET命令
	else if (USBREceive_Data[0] == 'G' && USBREceive_Data[1] == 'E' && USBREceive_Data[2] == 'T' &&
			 USBREceive_Data[3] == '_')
	{
		//在这里判断进入了继电器的查询
		if (USBREceive_Data[4] == 'M'	&& USBREceive_Data[5] == 'a' && USBREceive_Data[6] == 'c' &&
			USBREceive_Data[7] == 'V'	&& USBREceive_Data[8] == 'a' && USBREceive_Data[9] == 'l' &&
			USBREceive_Data[10] == 'v'	&& USBREceive_Data[11] == 'e' && USBREceive_Data[12] == '_')
		{
			//这里判断为1继电器的查询
			if (USBREceive_Data[13] == '1'	&& USBREceive_Data[14] == '_'	&& USBREceive_Data[15] == 'S'	&&
				USBREceive_Data[16] == 't'	&& USBREceive_Data[17] == 'a'	&& USBREceive_Data[18] == 't'	&&
				USBREceive_Data[19] == 'u'	&& USBREceive_Data[20] == 's')
			{
				//Serial.println("读取继电器1当前的状态");
				modbus_CRC = N_CRC16(getY1, length);//得到modbus_CRC的值
				getY1[6] = modbus_CRC >> 8;
				getY1[7] = modbus_CRC;
				Serial2.write(getY1, 8);//发送继电器的查询指令
				MacStatus = RS485Receive_MacStatus(1);

				if (MacStatus == 1)
				{
					//RESP_MacValve_1_Value
					Serial.println(String("RESP_MacValve_1_ON"));//回执信息
				}
				else if (MacStatus == 0)
				{
					Serial.println(String("RESP_MacValve_1_OFF"));//回执信息
				}
				else if (MacStatus == -1)
				{
					//RESP_MacValve_1_ERROR
					Serial.println(String("RESP_MacValve_1_ERROR"));//回执信息
				}
				else
				{
					Serial.println(String("aaaaaaaaaaaaa"));//回执信息
				}
				//Serial.print("MacStatus = ");
				//Serial.println(MacStatus);
			}
			//这里判断为2继电器的查询
			else if (USBREceive_Data[13] == '2'	&& USBREceive_Data[14] == '_'	&& USBREceive_Data[15] == 'S'	&&
					 USBREceive_Data[16] == 't'	&& USBREceive_Data[17] == 'a'	&& USBREceive_Data[18] == 't'	&&
					 USBREceive_Data[19] == 'u'	&& USBREceive_Data[20] == 's')
			{
				//Serial.println("读取继电器2当前的状态");
				modbus_CRC = N_CRC16(getY1, length);//得到modbus_CRC的值
				getY1[6] = modbus_CRC >> 8;
				getY1[7] = modbus_CRC;
				Serial2.write(getY1, 8);//发送继电器的查询指令
				MacStatus = RS485Receive_MacStatus(2);

				if (MacStatus == 1)
				{
					//RESP_MacValve_2_Value
					Serial.println(String("RESP_MacValve_2_ON"));//回执信息
				}
				else if (MacStatus == 0)
				{
					Serial.println(String("RESP_MacValve_2_OFF"));//回执信息
				}
				else if (MacStatus == -1)
				{
					//RESP_MacValve_2_ERROR
					Serial.println(String("RESP_MacValve_2_ERROR"));//回执信息
				}
				//Serial.print("MacStatus = ");
				//Serial.println(MacStatus)
			}
			//这里判断为3继电器的查询
			else if (USBREceive_Data[13] == '3'	&& USBREceive_Data[14] == '_'	&& USBREceive_Data[15] == 'S'	&&
					 USBREceive_Data[16] == 't'	&& USBREceive_Data[17] == 'a'	&& USBREceive_Data[18] == 't'	&&
					 USBREceive_Data[19] == 'u'	&& USBREceive_Data[20] == 's')
			{
				//Serial.println("读取继电器3当前的状态");
				modbus_CRC = N_CRC16(getY1, length);//得到modbus_CRC的值
				getY1[6] = modbus_CRC >> 8;
				getY1[7] = modbus_CRC;
				Serial2.write(getY1, 8);//发送继电器的查询指令
				MacStatus = RS485Receive_MacStatus(3);

				if (MacStatus == 1)
				{
					//RESP_MacValve_3_Value
					Serial.println(String("RESP_MacValve_3_ON"));//回执信息
				}
				else if (MacStatus == 0)
				{
					Serial.println(String("RESP_MacValve_3_OFF"));//回执信息
				}
				else if (MacStatus == -1)
				{
					//RESP_MacValve_3_ERROR
					Serial.println(String("RESP_MacValve_3_ERROR"));//回执信息
				}
				//Serial.print("MacStatus = ");
				//Serial.println(MacStatus)
			}
			//这里判断为4继电器的查询
			else if (USBREceive_Data[13] == '4'	&& USBREceive_Data[14] == '_'	&& USBREceive_Data[15] == 'S'	&&
					 USBREceive_Data[16] == 't'	&& USBREceive_Data[17] == 'a'	&& USBREceive_Data[18] == 't'	&&
					 USBREceive_Data[19] == 'u'	&& USBREceive_Data[20] == 's')
			{
				//Serial.println("读取继电器4当前的状态");
				modbus_CRC = N_CRC16(getY1, length);//得到modbus_CRC的值
				getY1[6] = modbus_CRC >> 8;
				getY1[7] = modbus_CRC;
				Serial2.write(getY1, 8);//发送继电器的查询指令
				MacStatus = RS485Receive_MacStatus(4);

				if (MacStatus == 1)
				{
					//RESP_MacValve_4_Value
					Serial.println(String("RESP_MacValve_4_ON"));//回执信息
				}
				else if (MacStatus == 0)
				{
					Serial.println(String("RESP_MacValve_4_OFF"));//回执信息
				}
				else if (MacStatus == -1)
				{
					//RESP_MacValve_4_ERROR
					Serial.println(String("RESP_MacValve_4_ERROR"));//回执信息
				}
				//Serial.print("MacStatus = ");
				//Serial.println(MacStatus)
			}
			//这里判断为5继电器的查询
			else if (USBREceive_Data[13] == '5'	&& USBREceive_Data[14] == '_'	&& USBREceive_Data[15] == 'S'	&&
					 USBREceive_Data[16] == 't'	&& USBREceive_Data[17] == 'a'	&& USBREceive_Data[18] == 't'	&&
					 USBREceive_Data[19] == 'u'	&& USBREceive_Data[20] == 's')
			{
				//Serial.println("读取继电器5当前的状态");
				modbus_CRC = N_CRC16(getY1, length);//得到modbus_CRC的值
				getY1[6] = modbus_CRC >> 8;
				getY1[7] = modbus_CRC;
				Serial2.write(getY1, 8);//发送继电器的查询指令
				MacStatus = RS485Receive_MacStatus(5);

				if (MacStatus == 1)
				{
					//RESP_MacValve_5_Value
					Serial.println(String("RESP_MacValve_5_ON"));//回执信息
				}
				else if (MacStatus == 0)
				{
					Serial.println(String("RESP_MacValve_5_OFF"));//回执信息
				}
				else if (MacStatus == -1)
				{
					//RESP_MacValve_4_ERROR
					Serial.println(String("RESP_MacValve_5_ERROR"));//回执信息
				}
				//Serial.print("MacStatus = ");
				//Serial.println(MacStatus)
			}
			//这里判断为6继电器的查询
			else if (USBREceive_Data[13] == '6'	&& USBREceive_Data[14] == '_'	&& USBREceive_Data[15] == 'S'	&&
					 USBREceive_Data[16] == 't'	&& USBREceive_Data[17] == 'a'	&& USBREceive_Data[18] == 't'	&&
					 USBREceive_Data[19] == 'u'	&& USBREceive_Data[20] == 's')
			{
				//Serial.println("读取继电器6当前的状态");
				modbus_CRC = N_CRC16(getY1, length);//得到modbus_CRC的值
				getY1[6] = modbus_CRC >> 8;
				getY1[7] = modbus_CRC;
				Serial2.write(getY1, 8);//发送继电器的查询指令
				MacStatus = RS485Receive_MacStatus(6);

				if (MacStatus == 1)
				{
					//RESP_MacValve_6_Value
					Serial.println(String("RESP_MacValve_6_ON"));//回执信息
				}
				else if (MacStatus == 0)
				{
					Serial.println(String("RESP_MacValve_6_OFF"));//回执信息
				}
				else if (MacStatus == -1)
				{
					//RESP_MacValve_6_ERROR
					Serial.println(String("RESP_MacValve_6_ERROR"));//回执信息
				}
				//Serial.print("MacStatus = ");
				//Serial.println(MacStatus)
			}
			//这里判断为7继电器的查询
			else if (USBREceive_Data[13] == '7'	&& USBREceive_Data[14] == '_'	&& USBREceive_Data[15] == 'S'	&&
					 USBREceive_Data[16] == 't'	&& USBREceive_Data[17] == 'a'	&& USBREceive_Data[18] == 't'	&&
					 USBREceive_Data[19] == 'u'	&& USBREceive_Data[20] == 's')
			{
				//Serial.println("读取继电器7当前的状态");
				modbus_CRC = N_CRC16(getY1, length);//得到modbus_CRC的值
				getY1[6] = modbus_CRC >> 8;
				getY1[7] = modbus_CRC;
				Serial2.write(getY1, 8);//发送继电器的查询指令
				MacStatus = RS485Receive_MacStatus(7);

				if (MacStatus == 1)
				{
					//RESP_MacValve_7_Value
					Serial.println(String("RESP_MacValve_7_ON"));//回执信息
				}
				else if (MacStatus == 0)
				{
					Serial.println(String("RESP_MacValve_7_OFF"));//回执信息
				}
				else if (MacStatus == -1)
				{
					//RESP_MacValve_7_ERROR
					Serial.println(String("RESP_MacValve_7_ERROR"));//回执信息
				}
				//Serial.print("MacStatus = ");
				//Serial.println(MacStatus)
			}
			//这里判断为8继电器的查询
			else if (USBREceive_Data[13] == '8'	&& USBREceive_Data[14] == '_'	&& USBREceive_Data[15] == 'S'	&&
					 USBREceive_Data[16] == 't'	&& USBREceive_Data[17] == 'a'	&& USBREceive_Data[18] == 't'	&&
					 USBREceive_Data[19] == 'u'	&& USBREceive_Data[20] == 's')
			{
				//Serial.println("读取继电器8当前的状态");
				modbus_CRC = N_CRC16(getY1, length);//得到modbus_CRC的值
				getY1[6] = modbus_CRC >> 8;
				getY1[7] = modbus_CRC;
				Serial2.write(getY1, 8);//发送继电器的查询指令
				MacStatus = RS485Receive_MacStatus(8);

				if (MacStatus == 1)
				{
					//RESP_MacValve_8_Value
					Serial.println(String("RESP_MacValve_8_ON"));//回执信息
				}
				else if (MacStatus == 0)
				{
					Serial.println(String("RESP_MacValve_8_OFF"));//回执信息
				}
				else if (MacStatus == -1)
				{
					//RESP_MacValve_8_ERROR
					Serial.println(String("RESP_MacValve_8_ERROR"));//回执信息
				}
				//Serial.print("MacStatus = ");
				//Serial.println(MacStatus)
			}
			//这里判断为9继电器的查询
			else if (USBREceive_Data[13] == '9'	&& USBREceive_Data[14] == '_'	&& USBREceive_Data[15] == 'S'	&&
					 USBREceive_Data[16] == 't'	&& USBREceive_Data[17] == 'a'	&& USBREceive_Data[18] == 't'	&&
					 USBREceive_Data[19] == 'u'	&& USBREceive_Data[20] == 's')
			{
				//Serial.println("读取继电器9当前的状态");
				modbus_CRC = N_CRC16(getY2_1, length);//得到modbus_CRC的值
				getY2_1[6] = modbus_CRC >> 8;
				getY2_1[7] = modbus_CRC;
				Serial2.write(getY2_1, 8);//发送继电器的查询指令
				MacStatus = RS485Receive_MacStatus(1);

				if (MacStatus == 1)
				{
					//RESP_MacValve_9_Value
					Serial.println(String("RESP_MacValve_9_ON"));//回执信息
				}
				else if (MacStatus == 0)
				{
					Serial.println(String("RESP_MacValve_9_OFF"));//回执信息
				}
				else if (MacStatus == -1)
				{
					//RESP_MacValve_9_ERROR
					Serial.println(String("RESP_MacValve_9_ERROR"));//回执信息
				}
				//Serial.print("MacStatus = ");
				//Serial.println(MacStatus)
			}
			//这里判断为10继电器的查询
			else if (USBREceive_Data[13] == '1'	&&	USBREceive_Data[14] == '0'	&&	USBREceive_Data[15] == '_'	&&
					 USBREceive_Data[16] == 'S'	&&	USBREceive_Data[17] == 't'	&&	USBREceive_Data[18] == 'a'	&&
					 USBREceive_Data[19] == 't'	&&	USBREceive_Data[20] == 'u'	&&	USBREceive_Data[21] == 's')
			{
				//Serial.println("读取继电器10当前的状态");
				modbus_CRC = N_CRC16(getY2_1, length);//得到modbus_CRC的值
				getY2_1[6] = modbus_CRC >> 8;
				getY2_1[7] = modbus_CRC;
				Serial2.write(getY2_1, 8);//发送继电器的查询指令
				MacStatus = RS485Receive_MacStatus(2);

				if (MacStatus == 1)
				{
					//RESP_MacValve_10_Value
					Serial.println(String("RESP_MacValve_10_ON"));//回执信息
				}
				else if (MacStatus == 0)
				{
					Serial.println(String("RESP_MacValve_10_OFF"));//回执信息
				}
				else if (MacStatus == -1)
				{
					//RESP_MacValve_10_ERROR
					Serial.println(String("RESP_MacValve_10_ERROR"));//回执信息
				}
				//Serial.print("MacStatus = ");
				//Serial.println(MacStatus)
			}
			//这里判断为11继电器的查询
			else if (USBREceive_Data[13] == '1'	&&	USBREceive_Data[14] == '1'	&&	USBREceive_Data[15] == '_'	&&
					 USBREceive_Data[16] == 'S'	&&	USBREceive_Data[17] == 't'	&&	USBREceive_Data[18] == 'a'	&&
					 USBREceive_Data[19] == 't'	&&	USBREceive_Data[20] == 'u'	&&	USBREceive_Data[21] == 's')
			{
				//Serial.println("读取继电器11当前的状态");
				modbus_CRC = N_CRC16(getY2_1, length);//得到modbus_CRC的值
				getY2_1[6] = modbus_CRC >> 8;
				getY2_1[7] = modbus_CRC;
				Serial2.write(getY2_1, 8);//发送继电器的查询指令
				MacStatus = RS485Receive_MacStatus(3);

				if (MacStatus == 1)
				{
					//RESP_MacValve_11_Value
					Serial.println(String("RESP_MacValve_11_ON"));//回执信息
				}
				else if (MacStatus == 0)
				{
					Serial.println(String("RESP_MacValve_11_OFF"));//回执信息
				}
				else if (MacStatus == -1)
				{
					//RESP_MacValve_11_ERROR
					Serial.println(String("RESP_MacValve_11_ERROR"));//回执信息
				}
				//Serial.print("MacStatus = ");
				//Serial.println(MacStatus)
			}
			//这里判断为12继电器的查询
			else if (USBREceive_Data[13] == '1'	&&	USBREceive_Data[14] == '2'	&&	USBREceive_Data[15] == '_'	&&
					 USBREceive_Data[16] == 'S'	&&	USBREceive_Data[17] == 't'	&&	USBREceive_Data[18] == 'a'	&&
					 USBREceive_Data[19] == 't'	&&	USBREceive_Data[20] == 'u'	&&	USBREceive_Data[21] == 's')
			{
				//Serial.println("读取继电器12当前的状态");
				modbus_CRC = N_CRC16(getY2_1, length);//得到modbus_CRC的值
				getY2_1[6] = modbus_CRC >> 8;
				getY2_1[7] = modbus_CRC;
				Serial2.write(getY2_1, 8);//发送继电器的查询指令
				MacStatus = RS485Receive_MacStatus(4);

				if (MacStatus == 1)
				{
					//RESP_MacValve_12_Value
					Serial.println(String("RESP_MacValve_12_ON"));//回执信息
				}
				else if (MacStatus == 0)
				{
					Serial.println(String("RESP_MacValve_12_OFF"));//回执信息
				}
				else if (MacStatus == -1)
				{
					//RESP_MacValve_12_ERROR
					Serial.println(String("RESP_MacValve_12_ERROR"));//回执信息
				}
				//Serial.print("MacStatus = ");
				//Serial.println(MacStatus)
			}
			//这里判断为13继电器的查询
			else if (USBREceive_Data[13] == '1'	&&	USBREceive_Data[14] == '3'	&&	USBREceive_Data[15] == '_'	&&
					 USBREceive_Data[16] == 'S'	&&	USBREceive_Data[17] == 't'	&&	USBREceive_Data[18] == 'a'	&&
					 USBREceive_Data[19] == 't'	&&	USBREceive_Data[20] == 'u'	&&	USBREceive_Data[21] == 's')
			{
				//Serial.println("读取继电器13当前的状态");
				modbus_CRC = N_CRC16(getY2_1, length);//得到modbus_CRC的值
				getY2_1[6] = modbus_CRC >> 8;
				getY2_1[7] = modbus_CRC;
				Serial2.write(getY2_1, 8);//发送继电器的查询指令
				MacStatus = RS485Receive_MacStatus(5);

				if (MacStatus == 1)
				{
					//RESP_MacValve_13_Value
					Serial.println(String("RESP_MacValve_13_ON"));//回执信息
				}
				else if (MacStatus == 0)
				{
					Serial.println(String("RESP_MacValve_13_OFF"));//回执信息
				}
				else if (MacStatus == -1)
				{
					//RESP_MacValve_13_ERROR
					Serial.println(String("RESP_MacValve_13_ERROR"));//回执信息
				}
				//Serial.print("MacStatus = ");
				//Serial.println(MacStatus)
			}
			//这里判断为14继电器的查询
			else if (USBREceive_Data[13] == '1'	&&	USBREceive_Data[14] == '4'	&&	USBREceive_Data[15] == '_'	&&
					 USBREceive_Data[16] == 'S'	&&	USBREceive_Data[17] == 't'	&&	USBREceive_Data[18] == 'a'	&&
					 USBREceive_Data[19] == 't'	&&	USBREceive_Data[20] == 'u'	&&	USBREceive_Data[21] == 's')
			{
				//Serial.println("读取继电器14当前的状态");
				modbus_CRC = N_CRC16(getY2_1, length);//得到modbus_CRC的值
				getY2_1[6] = modbus_CRC >> 8;
				getY2_1[7] = modbus_CRC;
				Serial2.write(getY2_1, 8);//发送继电器的查询指令
				MacStatus = RS485Receive_MacStatus(6);

				if (MacStatus == 1)
				{
					//RESP_MacValve_14_Value
					Serial.println(String("RESP_MacValve_14_ON"));//回执信息
				}
				else if (MacStatus == 0)
				{
					Serial.println(String("RESP_MacValve_14_OFF"));//回执信息
				}
				else if (MacStatus == -1)
				{
					//RESP_MacValve_14_ERROR
					Serial.println(String("RESP_MacValve_14_ERROR"));//回执信息
				}
				//Serial.print("MacStatus = ");
				//Serial.println(MacStatus)
			}
			//这里判断为15继电器的查询
			else if (USBREceive_Data[13] == '1'	&&	USBREceive_Data[14] == '5'	&&	USBREceive_Data[15] == '_'	&&
					 USBREceive_Data[16] == 'S'	&&	USBREceive_Data[17] == 't'	&&	USBREceive_Data[18] == 'a'	&&
					 USBREceive_Data[19] == 't'	&&	USBREceive_Data[20] == 'u'	&&	USBREceive_Data[21] == 's')
			{
				//Serial.println("读取继电器15当前的状态");
				modbus_CRC = N_CRC16(getY2_1, length);//得到modbus_CRC的值
				getY2_1[6] = modbus_CRC >> 8;
				getY2_1[7] = modbus_CRC;
				Serial2.write(getY2_1, 8);//发送继电器的查询指令
				MacStatus = RS485Receive_MacStatus(7);

				if (MacStatus == 1)
				{
					//RESP_MacValve_15_Value
					Serial.println(String("RESP_MacValve_15_ON"));//回执信息
				}
				else if (MacStatus == 0)
				{
					Serial.println(String("RESP_MacValve_15_OFF"));//回执信息
				}
				else if (MacStatus == -1)
				{
					//RESP_MacValve_15_ERROR
					Serial.println(String("RESP_MacValve_15_ERROR"));//回执信息
				}
				//Serial.print("MacStatus = ");
				//Serial.println(MacStatus)
			}
			//这里判断为16继电器的查询
			else if (USBREceive_Data[13] == '1'	&&	USBREceive_Data[14] == '6'	&&	USBREceive_Data[15] == '_'	&&
					 USBREceive_Data[16] == 'S'	&&	USBREceive_Data[17] == 't'	&&	USBREceive_Data[18] == 'a'	&&
					 USBREceive_Data[19] == 't'	&&	USBREceive_Data[20] == 'u'	&&	USBREceive_Data[21] == 's')
			{
				//Serial.println("读取继电器16当前的状态");
				modbus_CRC = N_CRC16(getY2_1, length);//得到modbus_CRC的值
				getY2_1[6] = modbus_CRC >> 8;
				getY2_1[7] = modbus_CRC;
				Serial2.write(getY2_1, 8);//发送继电器的查询指令
				MacStatus = RS485Receive_MacStatus(8);

				if (MacStatus == 1)
				{
					//RESP_MacValve_16_Value
					Serial.println(String("RESP_MacValve_16_ON"));//回执信息
				}
				else if (MacStatus == 0)
				{
					Serial.println(String("RESP_MacValve_16_OFF"));//回执信息
				}
				else if (MacStatus == -1)
				{
					//RESP_MacValve_16_ERROR
					Serial.println(String("RESP_MacValve_16_ERROR"));//回执信息
				}
				//Serial.print("MacStatus = ");
				//Serial.println(MacStatus)
			}
			//这里判断为17继电器的查询
			else if (USBREceive_Data[13] == '1'	&&	USBREceive_Data[14] == '7'	&&	USBREceive_Data[15] == '_'	&&
					 USBREceive_Data[16] == 'S'	&&	USBREceive_Data[17] == 't'	&&	USBREceive_Data[18] == 'a'	&&
					 USBREceive_Data[19] == 't'	&&	USBREceive_Data[20] == 'u'	&&	USBREceive_Data[21] == 's')
			{
				//Serial.println("读取继电器17当前的状态");
				modbus_CRC = N_CRC16(getY2_2, length);//得到modbus_CRC的值
				getY2_2[6] = modbus_CRC >> 8;
				getY2_2[7] = modbus_CRC;
				Serial2.write(getY2_2, 8);//发送继电器的查询指令
				MacStatus = RS485Receive_MacStatus(1);

				if (MacStatus == 1)
				{
					//RESP_MacValve_17_Value
					Serial.println(String("RESP_MacValve_17_ON"));//回执信息
				}
				else if (MacStatus == 0)
				{
					Serial.println(String("RESP_MacValve_17_OFF"));//回执信息
				}
				else if (MacStatus == -1)
				{
					//RESP_MacValve_17_ERROR
					Serial.println(String("RESP_MacValve_17_ERROR"));//回执信息
				}
				//Serial.print("MacStatus = ");
				//Serial.println(MacStatus)
			}
			//这里判断为18继电器的查询
			else if (USBREceive_Data[13] == '1'	&&	USBREceive_Data[14] == '8'	&&	USBREceive_Data[15] == '_'	&&
					USBREceive_Data[16] == 'S'	&&	USBREceive_Data[17] == 't'	&&	USBREceive_Data[18] == 'a'	&&
					USBREceive_Data[19] == 't'	&&	USBREceive_Data[20] == 'u'	&&	USBREceive_Data[21] == 's')
			{
				//Serial.println("读取继电器18当前的状态");
				modbus_CRC = N_CRC16(getY2_2, length);//得到modbus_CRC的值
				getY2_2[6] = modbus_CRC >> 8;
				getY2_2[7] = modbus_CRC;
				Serial2.write(getY2_2, 8);//发送继电器的查询指令
				MacStatus = RS485Receive_MacStatus(2);

				if (MacStatus == 1)
				{
					//RESP_MacValve_18_Value
					Serial.println(String("RESP_MacValve_18_ON"));//回执信息
				}
				else if (MacStatus == 0)
				{
					Serial.println(String("RESP_MacValve_18_OFF"));//回执信息
				}
				else if (MacStatus == -1)
				{
					//RESP_MacValve_18_ERROR
					Serial.println(String("RESP_MacValve_18_ERROR"));//回执信息
				}
				//Serial.print("MacStatus = ");
				//Serial.println(MacStatus)
			}
			//这里判断为19继电器的查询
			else if (USBREceive_Data[13] == '1'	&&	USBREceive_Data[14] == '9'	&&	USBREceive_Data[15] == '_'	&&
					 USBREceive_Data[16] == 'S'	&&	USBREceive_Data[17] == 't'	&&	USBREceive_Data[18] == 'a'	&&
					 USBREceive_Data[19] == 't'	&&	USBREceive_Data[20] == 'u'	&&	USBREceive_Data[21] == 's')
			{
				//Serial.println("读取继电器19当前的状态");
				modbus_CRC = N_CRC16(getY2_2, length);//得到modbus_CRC的值
				getY2_2[6] = modbus_CRC >> 8;
				getY2_2[7] = modbus_CRC;
				Serial2.write(getY2_2, 8);//发送继电器的查询指令
				MacStatus = RS485Receive_MacStatus(3);

				if (MacStatus == 1)
				{
					//RESP_MacValve_19_Value
					Serial.println(String("RESP_MacValve_19_ON"));//回执信息
				}
				else if (MacStatus == 0)
				{
					Serial.println(String("RESP_MacValve_19_OFF"));//回执信息
				}
				else if (MacStatus == -1)
				{
					//RESP_MacValve_19_ERROR
					Serial.println(String("RESP_MacValve_19_ERROR"));//回执信息
				}
				//Serial.print("MacStatus = ");
				//Serial.println(MacStatus)
			}
			//这里判断为20继电器的查询
			else if (USBREceive_Data[13] == '2'	&&	USBREceive_Data[14] == '0'	&&	USBREceive_Data[15] == '_'	&&
					 USBREceive_Data[16] == 'S'	&&	USBREceive_Data[17] == 't'	&&	USBREceive_Data[18] == 'a'	&&
					 USBREceive_Data[19] == 't'	&&	USBREceive_Data[20] == 'u'	&&	USBREceive_Data[21] == 's')
			{
				//Serial.println("读取继电器20当前的状态");
				modbus_CRC = N_CRC16(getY2_2, length);//得到modbus_CRC的值
				getY2_2[6] = modbus_CRC >> 8;
				getY2_2[7] = modbus_CRC;
				Serial2.write(getY2_2, 8);//发送继电器的查询指令
				MacStatus = RS485Receive_MacStatus(4);

				if (MacStatus == 1)
				{
					//RESP_MacValve_20_Value
					Serial.println(String("RESP_MacValve_20_ON"));//回执信息
				}
				else if (MacStatus == 0)
				{
					Serial.println(String("RESP_MacValve_20_OFF"));//回执信息
				}
				else if (MacStatus == -1)
				{
					//RESP_MacValve_20_ERROR
					Serial.println(String("RESP_MacValve_20_ERROR"));//回执信息
				}
				//Serial.print("MacStatus = ");
				//Serial.println(MacStatus)
			}
			//这里判断为21继电器的查询
			else if (USBREceive_Data[13] == '2'	&&	USBREceive_Data[14] == '1'	&&	USBREceive_Data[15] == '_'	&&
					 USBREceive_Data[16] == 'S'	&&	USBREceive_Data[17] == 't'	&&	USBREceive_Data[18] == 'a'	&&
					 USBREceive_Data[19] == 't'	&&	USBREceive_Data[20] == 'u'	&&	USBREceive_Data[21] == 's')
			{
				//Serial.println("读取继电器21当前的状态");
				modbus_CRC = N_CRC16(getY2_2, length);//得到modbus_CRC的值
				getY2_2[6] = modbus_CRC >> 8;
				getY2_2[7] = modbus_CRC;
				Serial2.write(getY2_2, 8);//发送继电器的查询指令
				MacStatus = RS485Receive_MacStatus(5);

				if (MacStatus == 1)
				{
					//RESP_MacValve_21_Value
					Serial.println(String("RESP_MacValve_21_ON"));//回执信息
				}
				else if (MacStatus == 0)
				{
					Serial.println(String("RESP_MacValve_21_OFF"));//回执信息
				}
				else if (MacStatus == -1)
				{
					//RESP_MacValve_21_ERROR
					Serial.println(String("RESP_MacValve_21_ERROR"));//回执信息
				}
				//Serial.print("MacStatus = ");
				//Serial.println(MacStatus)
			}
			//这里判断为22继电器的查询
			else if (USBREceive_Data[13] == '2'	&&	USBREceive_Data[14] == '2'	&&	USBREceive_Data[15] == '_'	&&
					 USBREceive_Data[16] == 'S'	&&	USBREceive_Data[17] == 't'	&&	USBREceive_Data[18] == 'a'	&&
					 USBREceive_Data[19] == 't'	&&	USBREceive_Data[20] == 'u'	&&	USBREceive_Data[21] == 's')
			{
				//Serial.println("读取继电器22当前的状态");
				modbus_CRC = N_CRC16(getY2_2, length);//得到modbus_CRC的值
				getY2_2[6] = modbus_CRC >> 8;
				getY2_2[7] = modbus_CRC;
				Serial2.write(getY2_2, 8);//发送继电器的查询指令
				MacStatus = RS485Receive_MacStatus(6);

				if (MacStatus == 1)
				{
					//RESP_MacValve_22_Value
					Serial.println(String("RESP_MacValve_22_ON"));//回执信息
				}
				else if (MacStatus == 0)
				{
					Serial.println(String("RESP_MacValve_22_OFF"));//回执信息
				}
				else if (MacStatus == -1)
				{
					//RESP_MacValve_22_ERROR
					Serial.println(String("RESP_MacValve_22_ERROR"));//回执信息
				}
				//Serial.print("MacStatus = ");
				//Serial.println(MacStatus)
			}
			//这里判断为23继电器的查询
			else if (USBREceive_Data[13] == '2'	&&	USBREceive_Data[14] == '3'	&&	USBREceive_Data[15] == '_'	&&
					 USBREceive_Data[16] == 'S'	&&	USBREceive_Data[17] == 't'	&&	USBREceive_Data[18] == 'a'	&&
					 USBREceive_Data[19] == 't'	&&	USBREceive_Data[20] == 'u'	&&	USBREceive_Data[21] == 's')
			{
				//Serial.println("读取继电器23当前的状态");
				modbus_CRC = N_CRC16(getY2_2, length);//得到modbus_CRC的值
				getY2_2[6] = modbus_CRC >> 8;
				getY2_2[7] = modbus_CRC;
				Serial2.write(getY2_2, 8);//发送继电器的查询指令
				MacStatus = RS485Receive_MacStatus(7);

				if (MacStatus == 1)
				{
					//RESP_MacValve_23_Value
					Serial.println(String("RESP_MacValve_23_ON"));//回执信息
				}
				else if (MacStatus == 0)
				{
					Serial.println(String("RESP_MacValve_23_OFF"));//回执信息
				}
				else if (MacStatus == -1)
				{
					//RESP_MacValve_23_ERROR
					Serial.println(String("RESP_MacValve_23_ERROR"));//回执信息
				}
				//Serial.print("MacStatus = ");
				//Serial.println(MacStatus)
			}
			//这里判断为24继电器的查询
			else if (USBREceive_Data[13] == '2'	&&	USBREceive_Data[14] == '4'	&&	USBREceive_Data[15] == '_'	&&
					 USBREceive_Data[16] == 'S'	&&	USBREceive_Data[17] == 't'	&&	USBREceive_Data[18] == 'a'	&&
					 USBREceive_Data[19] == 't'	&&	USBREceive_Data[20] == 'u'	&&	USBREceive_Data[21] == 's')
			{
				//Serial.println("读取继电器24当前的状态");
				modbus_CRC = N_CRC16(getY2_2, length);//得到modbus_CRC的值
				getY2_2[6] = modbus_CRC >> 8;
				getY2_2[7] = modbus_CRC;
				Serial2.write(getY2_2, 8);//发送继电器的查询指令
				MacStatus = RS485Receive_MacStatus(8);

				if (MacStatus == 1)
				{
					//RESP_MacValve_24_Value
					Serial.println(String("RESP_MacValve_24_ON"));//回执信息
				}
				else if (MacStatus == 0)
				{
					Serial.println(String("RESP_MacValve_24_OFF"));//回执信息
				}
				else if (MacStatus == -1)
				{
					//RESP_MacValve_24_ERROR
					Serial.println(String("RESP_MacValve_24_ERROR"));//回执信息
				}
				//Serial.print("MacStatus = ");
				//Serial.println(MacStatus)
			}
		}
		//这里判断进入了温度通道
		else if (USBREceive_Data[4] == 'H'	&& USBREceive_Data[5] == 'e'	&& USBREceive_Data[6] == 'a'	&&
			USBREceive_Data[7] == 't'	&& USBREceive_Data[8] == 'i'	&& USBREceive_Data[9] == 'n'	&&
			USBREceive_Data[10] == 'g'	&& USBREceive_Data[11] == 'J'	&& USBREceive_Data[12] == 'a'	&&
			USBREceive_Data[13] == 'c'	&& USBREceive_Data[14] == 'k'	&& USBREceive_Data[15] == 'e'	&&
			USBREceive_Data[16] == 't'	&& USBREceive_Data[17] == 's'	&& USBREceive_Data[18] == '_')
		{
			//这里判断进入查询温度1通道
			if (USBREceive_Data[19] == '1' && USBREceive_Data[20] == '_')
			{
				//读取1通道当前的温度
				if (USBREceive_Data[21] == 'T' && USBREceive_Data[22] == 'e' && USBREceive_Data[23] == 'm' &&
					USBREceive_Data[24] == 'p')
				{
					//Serial.println("读取1通道当前的温度");
					modbus_CRC = N_CRC16(getT3_1, length);//得到modbus_CRC的值
					getT3_1[6] = modbus_CRC >> 8;
					getT3_1[7] = modbus_CRC;
					Serial2.write(getT3_1, 8);//发送温度1通道的查询指令
					Temp_Measure = RS485Receive_Temp();
					if (Temp_Measure != -1)
					{
						if (Temp_Measure == 0x7FFF)
						{
							/*Serial.println("HH超上量程");
							Serial.println("0x7FFF")*/;
							//RESP_HeatingJackets_1_Temp_HH
							//通道1温度的回执，HH表示超出上量程，请检查接线
							Serial.println(String("RESP_HeatingJackets_1_Temp_HH"));//回执信息
						}
						else if (Temp_Measure == 0x7F00)
						{
							/*Serial.println("LL超下量程");
							Serial.println("0x7F00");*/
							//RESP_HeatingJackets_1_Temp_LL		
							//通道1温度的回执，LL表示超出下量程，请检查接线
							Serial.println(String("RESP_HeatingJackets_1_Temp_LL"));//回执信息
						}
						else
						{
							/*Serial.print("Temp_Measure = ");
							Serial.println(Temp_Measure);*/
							//RESP_HeatingJackets_1_Temp_Value 	
							//通道1温度的回执，Value = 溫度數值
							Serial.println(String("RESP_HeatingJackets_1_Temp_" + String(Temp_Measure)));//回执信息
						}
					}
					else
					{
						//Serial.println("crc校验未通过，无法得到数据");
						//RESP_HeatingJackets_1_Temp_ERROR	
						//通道1温度的回执，ERROR表示失败，请重新读取
						Serial.println(String("RESP_HeatingJackets_1_Temp_ERROR"));//回执信息
					}
				}
			}
			//这里判断进入查询温度2通道
			else if (USBREceive_Data[19] == '2' && USBREceive_Data[20] == '_')
			{
				if (USBREceive_Data[21] == 'T' && USBREceive_Data[22] == 'e' && USBREceive_Data[23] == 'm' &&
					USBREceive_Data[24] == 'p')
				{
					//Serial.println("读取2通道当前的温度");
					modbus_CRC = N_CRC16(getT3_2, length);//得到modbus_CRC的值
					getT3_2[6] = modbus_CRC >> 8;
					getT3_2[7] = modbus_CRC;
					Serial2.write(getT3_2, 8);//发送温度2通道的查询指令
					Temp_Measure = RS485Receive_Temp();
					if (Temp_Measure != -1)
					{
						if (Temp_Measure == 0x7FFF)
						{
							/*Serial.println("HH超上量程");
							Serial.println("0x7FFF");*/
							//RESP_HeatingJackets_2_Temp_HH
							//通道2温度的回执，HH表示超出上量程，请检查接线
							Serial.println(String("RESP_HeatingJackets_2_Temp_HH"));//回执信息
						}
						else if (Temp_Measure == 0x7F00)
						{
							/*Serial.println("LL超下量程");
							Serial.println("0x7F00");*/
							//RESP_HeatingJackets_2_Temp_LL		
							//通道1温度的回执，LL表示超出下量程，请检查接线
							Serial.println(String("RESP_HeatingJackets_2_Temp_LL"));//回执信息
						}
						else
						{
							/*Serial.print("Temp_Measure = ");
							Serial.println(Temp_Measure);*/
							//RESP_HeatingJackets_2_Temp_Value 	
							//通道2温度的回执，Value = 溫度數值
							Serial.println(String("RESP_HeatingJackets_2_Temp_" + String(Temp_Measure)));//回执信息
						}
					}
					else
					{
						//Serial.println("crc校验未通过，无法得到数据");
						//RESP_HeatingJackets_2_Temp_ERROR	
						//通道1温度的回执，ERROR表示失败，请重新读取
						Serial.println(String("RESP_HeatingJackets_2_Temp_ERROR"));//回执信息
					}
				}
			}
			//这里判断进入查询温度3通道
			else if (USBREceive_Data[19] == '3' && USBREceive_Data[20] == '_')
			{
				if (USBREceive_Data[21] == 'T' && USBREceive_Data[22] == 'e' && USBREceive_Data[23] == 'm' &&
					USBREceive_Data[24] == 'p')
				{
					//Serial.println("读取3通道当前的温度");
					modbus_CRC = N_CRC16(getT3_3, length);//得到modbus_CRC的值
					getT3_3[6] = modbus_CRC >> 8;
					getT3_3[7] = modbus_CRC;
					Serial2.write(getT3_3, 8);//发送温度3通道的查询指令
					Temp_Measure = RS485Receive_Temp();
					if (Temp_Measure != -1)
					{
						if (Temp_Measure == 0x7FFF)
						{
							/*Serial.println("HH超上量程");
							Serial.println("0x7FFF");*/
							//RESP_HeatingJackets_3_Temp_HH
							//通道1温度的回执，HH表示超出上量程，请检查接线
							Serial.println(String("RESP_HeatingJackets_3_Temp_HH"));//回执信息
						}
						else if (Temp_Measure == 0x7F00)
						{
							/*Serial.println("LL超下量程");
							Serial.println("0x7F00");*/
							//RESP_HeatingJackets_1_Temp_LL		
							//通道1温度的回执，LL表示超出下量程，请检查接线
							Serial.println(String("RESP_HeatingJackets_3_Temp_LL"));//回执信息
						}
						else
						{
							/*Serial.print("Temp_Measure = ");
							Serial.println(Temp_Measure);*/
							//RESP_HeatingJackets_3_Temp_Value 	
							//通道1温度的回执，Value = 溫度數值
							Serial.println(String("RESP_HeatingJackets_3_Temp_" + String(Temp_Measure)));//回执信息
						}
					}
					else
					{
						//Serial.println("crc校验未通过，无法得到数据");
						//RESP_HeatingJackets_3_Temp_ERROR	
						//通道1温度的回执，ERROR表示失败，请重新读取
						Serial.println(String("RESP_HeatingJackets_3_Temp_ERROR"));//回执信息
					}
				}
			}
			//这里判断进入查询温度4通道
			else if (USBREceive_Data[19] == '4' && USBREceive_Data[20] == '_')
			{
				if (USBREceive_Data[21] == 'T' && USBREceive_Data[22] == 'e' && USBREceive_Data[23] == 'm' &&
					USBREceive_Data[24] == 'p')
				{
					//Serial.println("读取4通道当前的温度");
					modbus_CRC = N_CRC16(getT3_4, length);//得到modbus_CRC的值
					getT3_4[6] = modbus_CRC >> 8;
					getT3_4[7] = modbus_CRC;
					Serial2.write(getT3_4, 8);//发送温度4通道的查询指令
					Temp_Measure = RS485Receive_Temp();
					if (Temp_Measure != -1)
					{
						if (Temp_Measure == 0x7FFF)
						{
							/*Serial.println("HH超上量程");
							Serial.println("0x7FFF");*/
							//RESP_HeatingJackets_4_Temp_HH
							//通道1温度的回执，HH表示超出上量程，请检查接线
							Serial.println(String("RESP_HeatingJackets_4_Temp_HH"));//回执信息
						}
						else if (Temp_Measure == 0x7F00)
						{
							/*Serial.println("LL超下量程");
							Serial.println("0x7F00");*/
							//RESP_HeatingJackets_4_Temp_LL		
							//通道1温度的回执，LL表示超出下量程，请检查接线
							Serial.println(String("RESP_HeatingJackets_4_Temp_LL"));//回执信息
						}
						else
						{
							/*Serial.print("Temp_Measure = ");
							Serial.println(Temp_Measure);*/
							//RESP_HeatingJackets_4_Temp_Value 	
							//通道1温度的回执，Value = 溫度數值
							Serial.println(String("RESP_HeatingJackets_4_Temp_" + String(Temp_Measure)));//回执信息
						}
					}
					else
					{
						//Serial.println("crc校验未通过，无法得到数据");
						//RESP_HeatingJackets_4_Temp_ERROR	
						//通道1温度的回执，ERROR表示失败，请重新读取
						Serial.println(String("RESP_HeatingJackets_4_Temp_ERROR"));//回执信息
					}
				}
			}
			//这里判断进入查询温度5通道
			else if (USBREceive_Data[19] == '5' && USBREceive_Data[20] == '_')
			{
				if (USBREceive_Data[21] == 'T' && USBREceive_Data[22] == 'e' && USBREceive_Data[23] == 'm' &&
					USBREceive_Data[24] == 'p')
				{
					//Serial.println("读取5通道当前的温度");
					modbus_CRC = N_CRC16(getT3_5, length);//得到modbus_CRC的值
					getT3_5[6] = modbus_CRC >> 8;
					getT3_5[7] = modbus_CRC;
					Serial2.write(getT3_5, 8);//发送温度5通道的查询指令
					Temp_Measure = RS485Receive_Temp();
					if (Temp_Measure != -1)
					{
						if (Temp_Measure == 0x7FFF)
						{
							/*Serial.println("HH超上量程");
							Serial.println("0x7FFF");*/
							//RESP_HeatingJackets_5_Temp_HH
							//通道1温度的回执，HH表示超出上量程，请检查接线
							Serial.println(String("RESP_HeatingJackets_5_Temp_HH"));//回执信息
						}
						else if (Temp_Measure == 0x7F00)
						{
							/*Serial.println("LL超下量程");
							Serial.println("0x7F00");*/
							//RESP_HeatingJackets_5_Temp_LL		
							//通道1温度的回执，LL表示超出下量程，请检查接线
							Serial.println(String("RESP_HeatingJackets_5_Temp_LL"));//回执信息
						}
						else
						{
							/*Serial.print("Temp_Measure = ");
							Serial.println(Temp_Measure);*/
							//RESP_HeatingJackets_5_Temp_Value 	
							//通道1温度的回执，Value = 溫度數值
							Serial.println(String("RESP_HeatingJackets_5_Temp_" + String(Temp_Measure)));//回执信息
						}
					}
					else
					{
						//Serial.println("crc校验未通过，无法得到数据");
						//RESP_HeatingJackets__Temp_ERROR	
						//通道1温度的回执，ERROR表示失败，请重新读取
						Serial.println(String("RESP_HeatingJackets_5_Temp_ERROR"));//回执信息
					}
				}
			}
			//这里判断进入查询温度6通道
			else if (USBREceive_Data[19] == '6' && USBREceive_Data[20] == '_')
			{
				if (USBREceive_Data[21] == 'T' && USBREceive_Data[22] == 'e' && USBREceive_Data[23] == 'm' &&
					USBREceive_Data[24] == 'p')
				{
					//Serial.println("读取6通道当前的温度");
					modbus_CRC = N_CRC16(getT3_6, length);//得到modbus_CRC的值
					getT3_6[6] = modbus_CRC >> 8;
					getT3_6[7] = modbus_CRC;
					Serial2.write(getT3_6, 8);//发送温度6通道的查询指令
					Temp_Measure = RS485Receive_Temp();
					if (Temp_Measure != -1)
					{
						if (Temp_Measure == 0x7FFF)
						{
							/*Serial.println("HH超上量程");
							Serial.println("0x7FFF");*/
							//RESP_HeatingJackets_6_Temp_HH
							//通道1温度的回执，HH表示超出上量程，请检查接线
							Serial.println(String("RESP_HeatingJackets_6_Temp_HH"));//回执信息
						}
						else if (Temp_Measure == 0x7F00)
						{
							/*Serial.println("LL超下量程");
							Serial.println("0x7F00");*/
							//RESP_HeatingJackets_6_Temp_LL		
							//通道1温度的回执，LL表示超出下量程，请检查接线
							Serial.println(String("RESP_HeatingJackets_6_Temp_LL"));//回执信息
						}
						else
						{
							/*Serial.print("Temp_Measure = ");
							Serial.println(Temp_Measure);*/
							//RESP_HeatingJackets_6_Temp_Value 	
							//通道1温度的回执，Value = 溫度數值
							Serial.println(String("RESP_HeatingJackets_6_Temp_" + String(Temp_Measure)));//回执信息
						}
					}
					else
					{
						//Serial.println("crc校验未通过，无法得到数据");
						//RESP_HeatingJackets_6_Temp_ERROR	
						//通道1温度的回执，ERROR表示失败，请重新读取
						Serial.println(String("RESP_HeatingJackets_6_Temp_ERROR"));//回执信息
					}
				}
			}
			//这里判断进入查询温度7通道
			else if (USBREceive_Data[19] == '7' && USBREceive_Data[20] == '_')
			{
				if (USBREceive_Data[21] == 'T' && USBREceive_Data[22] == 'e' && USBREceive_Data[23] == 'm' &&
					USBREceive_Data[24] == 'p')
				{
					//Serial.println("读取7通道当前的温度");
					modbus_CRC = N_CRC16(getT3_7, length);//得到modbus_CRC的值
					getT3_7[6] = modbus_CRC >> 8;
					getT3_7[7] = modbus_CRC;
					Serial2.write(getT3_7, 8);//发送温度7通道的查询指令
					Temp_Measure = RS485Receive_Temp();
					if (Temp_Measure != -1)
					{
						if (Temp_Measure == 0x7FFF)
						{
							/*Serial.println("HH超上量程");
							Serial.println("0x7FFF");*/
							//RESP_HeatingJackets_7_Temp_HH
							//通道1温度的回执，HH表示超出上量程，请检查接线
							Serial.println(String("RESP_HeatingJackets_7_Temp_HH"));//回执信息
						}
						else if (Temp_Measure == 0x7F00)
						{
							/*Serial.println("LL超下量程");
							Serial.println("0x7F00");*/
							//RESP_HeatingJackets_7_Temp_LL		
							//通道7温度的回执，LL表示超出下量程，请检查接线
							Serial.println(String("RESP_HeatingJackets_7_Temp_LL"));//回执信息
						}
						else
						{
							/*Serial.print("Temp_Measure = ");
							Serial.println(Temp_Measure);*/
							//RESP_HeatingJackets_7_Temp_Value 	
							//通道7温度的回执，Value = 溫度數值
							Serial.println(String("RESP_HeatingJackets_7_Temp_" + String(Temp_Measure)));//回执信息
						}
					}
					else
					{
						//Serial.println("crc校验未通过，无法得到数据");
						//RESP_HeatingJackets_7_Temp_ERROR	
						//通道7温度的回执，ERROR表示失败，请重新读取
						Serial.println(String("RESP_HeatingJackets_7_Temp_ERROR"));//回执信息
					}
				}
			}
			//这里判断进入查询温度8通道
			else if (USBREceive_Data[19] == '8' && USBREceive_Data[20] == '_')
			{
				if (USBREceive_Data[21] == 'T' && USBREceive_Data[22] == 'e' && USBREceive_Data[23] == 'm' &&
					USBREceive_Data[24] == 'p')
				{
					//Serial.println("读取8通道当前的温度");
					modbus_CRC = N_CRC16(getT3_8, length);//得到modbus_CRC的值
					getT3_8[6] = modbus_CRC >> 8;
					getT3_8[7] = modbus_CRC;
					Serial2.write(getT3_8, 8);//发送温度8通道的查询指令
					Temp_Measure = RS485Receive_Temp();
					if (Temp_Measure != -1)
					{
						if (Temp_Measure == 0x7FFF)
						{
							/*Serial.println("HH超上量程");
							Serial.println("0x7FFF");*/
							//RESP_HeatingJackets_8_Temp_HH
							//通道1温度的回执，HH表示超出上量程，请检查接线
							Serial.println(String("RESP_HeatingJackets_8_Temp_HH"));//回执信息
						}
						else if (Temp_Measure == 0x7F00)
						{
							/*Serial.println("LL超下量程");
							Serial.println("0x7F00");*/
							//RESP_HeatingJackets_8_Temp_LL		
							//通道1温度的回执，LL表示超出下量程，请检查接线
							Serial.println(String("RESP_HeatingJackets_8_Temp_LL"));//回执信息
						}
						else
						{
							/*Serial.print("Temp_Measure = ");
							Serial.println(Temp_Measure);*/
							//RESP_HeatingJackets_8_Temp_Value 	
							//通道1温度的回执，Value = 溫度數值
							Serial.println(String("RESP_HeatingJackets_8_Temp_" + String(Temp_Measure)));//回执信息
						}
					}
					else
					{
						//Serial.println("crc校验未通过，无法得到数据");
						//RESP_HeatingJackets_8_Temp_ERROR	
						//通道1温度的回执，ERROR表示失败，请重新读取
						Serial.println(String("RESP_HeatingJackets_8_Temp_ERROR"));//回执信息
					}
				}
			}
			//这里判断进入查询温度9通道
			else if (USBREceive_Data[19] == '9' && USBREceive_Data[20] == '_')
			{
				if (USBREceive_Data[21] == 'T' && USBREceive_Data[22] == 'e' && USBREceive_Data[23] == 'm' &&
					USBREceive_Data[24] == 'p')
				{
					//Serial.println("读取9通道当前的温度");
					modbus_CRC = N_CRC16(getT4_1, length);//得到modbus_CRC的值
					getT4_1[6] = modbus_CRC >> 8;
					getT4_1[7] = modbus_CRC;
					Serial2.write(getT4_1, 8);//发送温度8通道的查询指令
					Temp_Measure = RS485Receive_Temp();
					if (Temp_Measure != -1)
					{
						if (Temp_Measure == 0x7FFF)
						{
							/*Serial.println("HH超上量程");
							Serial.println("0x7FFF");*/
							//RESP_HeatingJackets_9_Temp_HH
							//通道1温度的回执，HH表示超出上量程，请检查接线
							Serial.println(String("RESP_HeatingJackets_9_Temp_HH"));//回执信息
						}
						else if (Temp_Measure == 0x7F00)
						{
							/*Serial.println("LL超下量程");
							Serial.println("0x7F00");*/
							//RESP_HeatingJackets_9_Temp_LL		
							//通道1温度的回执，LL表示超出下量程，请检查接线
							Serial.println(String("RESP_HeatingJackets_9_Temp_LL"));//回执信息
						}
						else
						{
							/*Serial.print("Temp_Measure = ");
							Serial.println(Temp_Measure);*/
							//RESP_HeatingJackets_9_Temp_Value 	
							//通道1温度的回执，Value = 溫度數值
							Serial.println(String("RESP_HeatingJackets_9_Temp_" + String(Temp_Measure)));//回执信息
						}
					}
					else
					{
						//Serial.println("crc校验未通过，无法得到数据");
						//RESP_HeatingJackets_9_Temp_ERROR	
						//通道1温度的回执，ERROR表示失败，请重新读取
						Serial.println(String("RESP_HeatingJackets_9_Temp_ERROR"));//回执信息
					}
				}
			}
			//这里判断进入查询温度10通道
			else if (USBREceive_Data[19] == '1' && USBREceive_Data[20] == '0' && USBREceive_Data[21] == '_')
			{
				if (USBREceive_Data[22] == 'T' && USBREceive_Data[23] == 'e' && USBREceive_Data[24] == 'm' &&
					USBREceive_Data[25] == 'p')
				{
					//Serial.println("读取10通道当前的温度");
					modbus_CRC = N_CRC16(getT4_2, length);//得到modbus_CRC的值
					getT4_2[6] = modbus_CRC >> 8;
					getT4_2[7] = modbus_CRC;
					Serial2.write(getT4_2, 8);//发送温度8通道的查询指令
					Temp_Measure = RS485Receive_Temp();
					if (Temp_Measure != -1)
					{
						if (Temp_Measure == 0x7FFF)
						{
							//Serial.println("HH超上量程");
							//Serial.println("0x7FFF");
							//RESP_HeatingJackets_10_Temp_HH
							//通道1温度的回执，HH表示超出上量程，请检查接线
							Serial.println(String("RESP_HeatingJackets_10_Temp_HH"));//回执信息
						}
						else if (Temp_Measure == 0x7F00)
						{
							//Serial.println("LL超下量程");
							//Serial.println("0x7F00");
							//RESP_HeatingJackets_10_Temp_LL		
							//通道1温度的回执，LL表示超出下量程，请检查接线
							Serial.println(String("RESP_HeatingJackets_10_Temp_LL"));//回执信息
						}
						else
						{
							//Serial.print("Temp_Measure = ");
							//Serial.println(Temp_Measure);
							//RESP_HeatingJackets_10_Temp_Value 	
							//通道1温度的回执，Value = 溫度數值
							Serial.println(String("RESP_HeatingJackets_10_Temp_" + String(Temp_Measure)));//回执信息
						}
					}
					else
					{
						//Serial.println("crc校验未通过，无法得到数据");
						//RESP_HeatingJackets_10_Temp_ERROR	
						//通道1温度的回执，ERROR表示失败，请重新读取
						Serial.println(String("RESP_HeatingJackets_10_Temp_ERROR"));//回执信息
					}
				}
			}
			//这里判断进入查询温度11通道
			else if (USBREceive_Data[19] == '1' && USBREceive_Data[20] == '1' && USBREceive_Data[21] == '_')
			{
				if (USBREceive_Data[22] == 'T' && USBREceive_Data[23] == 'e' && USBREceive_Data[24] == 'm' &&
					USBREceive_Data[25] == 'p')
				{
					//Serial.println("读取11通道当前的温度");
					modbus_CRC = N_CRC16(getT4_3, length);//得到modbus_CRC的值
					getT4_3[6] = modbus_CRC >> 8;
					getT4_3[7] = modbus_CRC;
					Serial2.write(getT4_3, 8);//发送温度8通道的查询指令
					Temp_Measure = RS485Receive_Temp();
					if (Temp_Measure != -1)
					{
						if (Temp_Measure == 0x7FFF)
						{
							/*Serial.println("HH超上量程");
							Serial.println("0x7FFF");*/
							//RESP_HeatingJackets_11_Temp_HH
							//通道1温度的回执，HH表示超出上量程，请检查接线
							Serial.println(String("RESP_HeatingJackets_11_Temp_HH"));//回执信息
						}
						else if (Temp_Measure == 0x7F00)
						{
							/*Serial.println("LL超下量程");
							Serial.println("0x7F00");*/
							//RESP_HeatingJackets_11_Temp_LL		
							//通道1温度的回执，LL表示超出下量程，请检查接线
							Serial.println(String("RESP_HeatingJackets_11_Temp_LL"));//回执信息
						}
						else
						{
							/*Serial.print("Temp_Measure = ");
							Serial.println(Temp_Measure);*/
							//RESP_HeatingJackets_11_Temp_Value 	
							//通道1温度的回执，Value = 溫度數值
							Serial.println(String("RESP_HeatingJackets_11_Temp_" + String(Temp_Measure)));//回执信息
						}
					}
					else
					{
						//Serial.println("crc校验未通过，无法得到数据");
						//RESP_HeatingJackets_11_Temp_ERROR	
						//通道1温度的回执，ERROR表示失败，请重新读取
						Serial.println(String("RESP_HeatingJackets_11_Temp_ERROR"));//回执信息
					}
				}
			}
			//这里判断进入查询温度12通道
			else if (USBREceive_Data[19] == '1' && USBREceive_Data[20] == '2' && USBREceive_Data[21] == '_')
			{
				if (USBREceive_Data[22] == 'T' && USBREceive_Data[23] == 'e' && USBREceive_Data[24] == 'm' &&
					USBREceive_Data[25] == 'p')
				{
					//Serial.println("读取12通道当前的温度");
					modbus_CRC = N_CRC16(getT4_4, length);//得到modbus_CRC的值
					getT4_4[6] = modbus_CRC >> 8;
					getT4_4[7] = modbus_CRC;
					Serial2.write(getT4_4, 8);//发送温度8通道的查询指令
					Temp_Measure = RS485Receive_Temp();
					if (Temp_Measure != -1)
					{
						if (Temp_Measure == 0x7FFF)
						{
							/*Serial.println("HH超上量程");
							Serial.println("0x7FFF");*/
							//RESP_HeatingJackets_12_Temp_HH
							//通道1温度的回执，HH表示超出上量程，请检查接线
							Serial.println(String("RESP_HeatingJackets_12_Temp_HH"));//回执信息
						}
						else if (Temp_Measure == 0x7F00)
						{
							/*Serial.println("LL超下量程");
							Serial.println("0x7F00");*/
							//RESP_HeatingJackets_12_Temp_LL		
							//通道1温度的回执，LL表示超出下量程，请检查接线
							Serial.println(String("RESP_HeatingJackets_12_Temp_LL"));//回执信息
						}
						else
						{
							//Serial.print("Temp_Measure = ");
							//Serial.println(Temp_Measure);
							//RESP_HeatingJackets_12_Temp_Value 	
							//通道1温度的回执，Value = 溫度數值
							Serial.println(String("RESP_HeatingJackets_12_Temp_" + String(Temp_Measure)));//回执信息
						}
					}
					else
					{
						//Serial.println("crc校验未通过，无法得到数据");
						//RESP_HeatingJackets_12_Temp_ERROR	
						//通道1温度的回执，ERROR表示失败，请重新读取
						Serial.println(String("RESP_HeatingJackets_12_Temp_ERROR"));//回执信息
					}
				}
			}
			//这里判断进入查询温度13通道
			else if (USBREceive_Data[19] == '1' && USBREceive_Data[20] == '3' && USBREceive_Data[21] == '_')
			{
				if (USBREceive_Data[22] == 'T' && USBREceive_Data[23] == 'e' && USBREceive_Data[24] == 'm' &&
					USBREceive_Data[25] == 'p')
				{
					//Serial.println("读取12通道当前的温度");
					modbus_CRC = N_CRC16(getT4_5, length);//得到modbus_CRC的值
					getT4_5[6] = modbus_CRC >> 8;
					getT4_5[7] = modbus_CRC;
					Serial2.write(getT4_5, 8);//发送温度8通道的查询指令
					Temp_Measure = RS485Receive_Temp();
					if (Temp_Measure != -1)
					{
						if (Temp_Measure == 0x7FFF)
						{
							//Serial.println("HH超上量程");
							//Serial.println("0x7FFF");
							//RESP_HeatingJackets_13_Temp_HH
							//通道1温度的回执，HH表示超出上量程，请检查接线
							Serial.println(String("RESP_HeatingJackets_13_Temp_HH"));//回执信息
						}
						else if (Temp_Measure == 0x7F00)
						{
							//Serial.println("LL超下量程");
							//Serial.println("0x7F00");
							//RESP_HeatingJackets_13_Temp_LL		
							//通道1温度的回执，LL表示超出下量程，请检查接线
							Serial.println(String("RESP_HeatingJackets_13_Temp_LL"));//回执信息
						}
						else
						{
							Serial.print("Temp_Measure = ");
							Serial.println(Temp_Measure);
							//RESP_HeatingJackets_13_Temp_Value 	
							//通道1温度的回执，Value = 溫度數值
							Serial.println(String("RESP_HeatingJackets_13_Temp_" + String(Temp_Measure)));//回执信息
						}
					}
					else
					{
						//Serial.println("crc校验未通过，无法得到数据");
						//RESP_HeatingJackets_13_Temp_ERROR	
						//通道1温度的回执，ERROR表示失败，请重新读取
						Serial.println(String("RESP_HeatingJackets_13_Temp_ERROR"));//回执信息
					}
				}
			}
			//这里判断进入查询温度14通道
			else if (USBREceive_Data[19] == '1' && USBREceive_Data[20] == '4' && USBREceive_Data[21] == '_')
			{
				if (USBREceive_Data[22] == 'T' && USBREceive_Data[23] == 'e' && USBREceive_Data[24] == 'm' &&
					USBREceive_Data[25] == 'p')
				{
					//Serial.println("读取14通道当前的温度");
					modbus_CRC = N_CRC16(getT4_6, length);//得到modbus_CRC的值
					getT4_6[6] = modbus_CRC >> 8;
					getT4_6[7] = modbus_CRC;
					Serial2.write(getT4_6, 8);//发送温度8通道的查询指令
					Temp_Measure = RS485Receive_Temp();
					if (Temp_Measure != -1)
					{
						if (Temp_Measure == 0x7FFF)
						{
							//Serial.println("HH超上量程");
							//Serial.println("0x7FFF");
							//RESP_HeatingJackets_14_Temp_HH
							//通道1温度的回执，HH表示超出上量程，请检查接线
							Serial.println(String("RESP_HeatingJackets_14_Temp_HH"));//回执信息
						}
						else if (Temp_Measure == 0x7F00)
						{
							//Serial.println("LL超下量程");
							//Serial.println("0x7F00");
							//RESP_HeatingJackets_14_Temp_LL		
							//通道1温度的回执，LL表示超出下量程，请检查接线
							Serial.println(String("RESP_HeatingJackets_14_Temp_LL"));//回执信息
						}
						else
						{
							//Serial.print("Temp_Measure = ");
							//Serial.println(Temp_Measure);
							//RESP_HeatingJackets_14_Temp_Value 	
							//通道1温度的回执，Value = 溫度數值
							Serial.println(String("RESP_HeatingJackets_14_Temp_" + String(Temp_Measure)));//回执信息
						}
					}
					else
					{
						//Serial.println("crc校验未通过，无法得到数据");
						//RESP_HeatingJackets_14_Temp_ERROR	
						//通道1温度的回执，ERROR表示失败，请重新读取
						Serial.println(String("RESP_HeatingJackets_14_Temp_ERROR"));//回执信息
					}
				}
			}
			//这里判断进入查询温度15通道
			else if (USBREceive_Data[19] == '1' && USBREceive_Data[20] == '5' && USBREceive_Data[21] == '_')
			{
				if (USBREceive_Data[22] == 'T' && USBREceive_Data[23] == 'e' && USBREceive_Data[24] == 'm' &&
					USBREceive_Data[25] == 'p')
				{
					//Serial.println("读取15通道当前的温度");
					modbus_CRC = N_CRC16(getT4_7, length);//得到modbus_CRC的值
					getT4_7[6] = modbus_CRC >> 8;
					getT4_7[7] = modbus_CRC;
					Serial2.write(getT4_7, 8);//发送温度8通道的查询指令
					Temp_Measure = RS485Receive_Temp();
					if (Temp_Measure != -1)
					{
						if (Temp_Measure == 0x7FFF)
						{
							//Serial.println("HH超上量程");
							//Serial.println("0x7FFF");
							//RESP_HeatingJackets_15_Temp_HH
							//通道1温度的回执，HH表示超出上量程，请检查接线
							Serial.println(String("RESP_HeatingJackets_15_Temp_HH"));//回执信息
						}
						else if (Temp_Measure == 0x7F00)
						{
							//Serial.println("LL超下量程");
							//Serial.println("0x7F00");
							//RESP_HeatingJackets_15_Temp_LL		
							//通道1温度的回执，LL表示超出下量程，请检查接线
							Serial.println(String("RESP_HeatingJackets_15_Temp_LL"));//回执信息
						}
						else
						{
							//Serial.print("Temp_Measure = ");
							//Serial.println(Temp_Measure);
							//RESP_HeatingJackets_15_Temp_Value 	
							//通道1温度的回执，Value = 溫度數值
							Serial.println(String("RESP_HeatingJackets_15_Temp_" + String(Temp_Measure)));//回执信息
						}
					}
					else
					{
						//Serial.println("crc校验未通过，无法得到数据");
						//RESP_HeatingJackets_15_Temp_ERROR	
						//通道1温度的回执，ERROR表示失败，请重新读取
						Serial.println(String("RESP_HeatingJackets_15_Temp_ERROR"));//回执信息
					}
				}
			}
			//这里判断进入查询温度16通道
			else if (USBREceive_Data[19] == '1' && USBREceive_Data[20] == '6' && USBREceive_Data[21] == '_')
			{
				if (USBREceive_Data[22] == 'T' && USBREceive_Data[23] == 'e' && USBREceive_Data[24] == 'm' &&
					USBREceive_Data[25] == 'p')
				{
					//Serial.println("读取16通道当前的温度");
					modbus_CRC = N_CRC16(getT4_8, length);//得到modbus_CRC的值
					getT4_8[6] = modbus_CRC >> 8;
					getT4_8[7] = modbus_CRC;
					Serial2.write(getT4_8, 8);//发送温度8通道的查询指令
					Temp_Measure = RS485Receive_Temp();
					if (Temp_Measure != -1)
					{
						if (Temp_Measure == 0x7FFF)
						{
							/*Serial.println("HH超上量程");
							Serial.println("0x7FFF");*/
							//RESP_HeatingJackets_16_Temp_HH
							//通道1温度的回执，HH表示超出上量程，请检查接线
							Serial.println(String("RESP_HeatingJackets_16_Temp_HH"));//回执信息
						}
						else if (Temp_Measure == 0x7F00)
						{
							/*Serial.println("LL超下量程");
							Serial.println("0x7F00");*/
							//RESP_HeatingJackets_16_Temp_LL		
							//通道1温度的回执，LL表示超出下量程，请检查接线
							Serial.println(String("RESP_HeatingJackets_16_Temp_LL"));//回执信息
						}
						else
						{
							/*Serial.print("Temp_Measure = ");
							Serial.println(Temp_Measure);*/
							//RESP_HeatingJackets_16_Temp_Value 	
							//通道1温度的回执，Value = 溫度數值
							Serial.println(String("RESP_HeatingJackets_16_Temp_" + String(Temp_Measure)));//回执信息
						}
					}
					else
					{
						//Serial.println("crc校验未通过，无法得到数据");
						//RESP_HeatingJackets_16_Temp_ERROR	
						//通道1温度的回执，ERROR表示失败，请重新读取
						Serial.println(String("RESP_HeatingJackets_16_Temp_ERROR"));//回执信息
					}
				}
			}
		}
		else if (USBREceive_Data[4] == 'M'	&& USBREceive_Data[5] == 'F'	&& USBREceive_Data[6] == 'C'	&&
				 USBREceive_Data[7] == '_')
		{
			//进入了GAS流量查询
			if (USBREceive_Data[10] == 'G'	&& USBREceive_Data[11] == 'A'	&& USBREceive_Data[12] == 'S')
			{
				if (USBREceive_Data[8] == '1'	&& USBREceive_Data[9] == '_')
				{
					//Serial.println((analogRead(V1)*0.8056));//66.86
					for (size_t i = 0; i < 5; i++)
					{
						flow_measure[i] = (((analogRead(V1)*0.8056)-68) * 11) / 25;//连续采集5次，每次间隔10ms
						if (flow_measure[i] >= 0)
						{

						}
						else
						{
							flow_measure[i] = 0;
						}
						delay(10);
					}
					Flow_Measure = (flow_measure[0] + flow_measure[1] + flow_measure[2] + flow_measure[3] + flow_measure[4]) / 5;//取平均值
					long flow_shuchu = Flow_Measure * 1000;
					//flow_measure	Flow_Measure
					if (Flow_Measure >= 0 && Flow_Measure <= 250)
					{
						//Serial.println(Flow_Measure);
						Serial.println(String("RESP_MFC_1_GAS_") + String(flow_shuchu));//回执信息
					}
					else
					{
						Serial.println(String("RESP_MFC_1_GAS_ERROR"));//回执信息
					}
				}
				else if (USBREceive_Data[8] == '2'	&& USBREceive_Data[9] == '_')
				{
					for (size_t i = 0; i < 5; i++)
					{
						flow_measure[i] = ((analogRead(V1)*0.8056) * 11) / 25;//连续采集5次，每次间隔10ms
						delay(10);
					}
					Flow_Measure = (flow_measure[0] + flow_measure[1] + flow_measure[2] + flow_measure[3] + flow_measure[4]) / 5;//取平均值
					long flow_shuchu = Flow_Measure * 1000;
					//flow_measure	Flow_Measure
					if (Flow_Measure >= 0 && Flow_Measure <= 250)
					{
						//Serial.println(Flow_Measure);
						Serial.println(String("RESP_MFC_1_GAS_") + String(flow_shuchu));//回执信息
					}
					else
					{
						Serial.println(String("RESP_MFC_1_GAS_ERROR"));//回执信息
					}
				}
			}
			//进入了Status状态查询
			else if (USBREceive_Data[10] == 'S'	&& USBREceive_Data[11] == 't'	&& USBREceive_Data[12] == 'a' &&
					 USBREceive_Data[13] == 't' && USBREceive_Data[14] == 'u'	&& USBREceive_Data[15] == 's')
			{
				if (USBREceive_Data[8] == '1'	&& USBREceive_Data[9] == '_')
				{
					//Serial.println(String("RESP_MFC_1_Status_") + String("Open"));//回执信息
					Serial.println(String("RESP_MFC_1_Status_ERROR"));//回执信息
				}
				else if (USBREceive_Data[8] == '2'	&& USBREceive_Data[9] == '_')
				{
					//Serial.println(String("RESP_MFC_2_Status_") + String("Open"));//回执信息
					Serial.println(String("RESP_MFC_2_Status_ERROR"));//回执信息
				}

			}
		}
	}
}