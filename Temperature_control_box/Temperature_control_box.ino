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

#include"user_initialization.h"	//初始化函数
#include"MODBUS_RTU_CRC16.h"	//modbusCRC16校验的函数

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

String str_usb;

static unsigned short length = 6;

static int modbus_CRC = 0x00;
static unsigned char RS485REceive_Data[50];
static int RS485REceive_Length = 0;
static unsigned char USBREceive_Data[50];
static int USBREceive_Length = 0;
static unsigned char LORAEceive_Data[50];
static int LORAREceive_Length = 0;


//相关函数的定义
int16_t RS485Receive_information();			//RS485接收函数
int16_t LORAReceive_information();			//RS485接收函数
int16_t USB_Serial_reception();					//USB串口的接收函数
void USB_Judge(unsigned char *USBREceive_Data);	//USB判断函数



void setup()
{
	Initialization();//初始化函数
}

// Add the main program code into the continuous loop() function
void loop()
{
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
	//	/*for (int i = 0; i < RS485REceive_Length; i++)
	//	{
	//		Serial.print(String("RS485REceive_Data") + "[" + i + "]");
	//		Serial.println(RS485REceive_Data[i], HEX);
	//	}*/
	//	RS485REceive_Length = 0;
	//}
	//Serial.println("");



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
	//	/*for (int i = 0; i < RS485REceive_Length; i++)
	//	{
	//		Serial.print(String("RS485REceive_Data") + "[" + i + "]");
	//		Serial.println(RS485REceive_Data[i], HEX);
	//	}*/
	//	RS485REceive_Length = 0;
	//}
	//Serial.println("");
	//delay(2000);



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
	//	/*for (int i = 0; i < RS485REceive_Length; i++)
	//	{
	//		Serial.print(String("RS485REceive_Data") + "[" + i + "]");
	//		Serial.println(RS485REceive_Data[i], HEX);
	//	}*/
	//	RS485REceive_Length = 0;
	//}
	//Serial.println("");
	//delay(2000);

//==============以下为正常程序===================================

	LORAReceive_information();	//LORA的接收函数
	USB_Serial_reception();		//USB串口接收函数
	RS485Receive_information();	//RS485的接收函数
}

int16_t RS485Receive_information(void)
{
	while (Serial2.available() > 0)//RS485串口接收到数据
	{
		RS485REceive_Data[RS485REceive_Length++] = Serial2.read();
		delay(1);
	}
	if (RS485REceive_Length > 0)
	{
		Serial.print("RS485REceive_Length = ");
		Serial.println(RS485REceive_Length);
		for (int i = 0; i < RS485REceive_Length; i++)
		{
			//Serial.print(String("RS485REceive_Data") + "[" + i + "]");
			Serial.print(RS485REceive_Data[i], HEX);
		}
		RS485REceive_Length = 0;
	}
	return 0;

}

int16_t LORAReceive_information(void)
{
	return 0;
}

int16_t USB_Serial_reception(void)
{
	while (Serial.available() > 0)//USB串口接收到数据
	{
		USBREceive_Data[USBREceive_Length++] = Serial.read();
	}
	//Serial.println(str_usb);
	//delay(5000);
	if (USBREceive_Length > 0)
	{
		//======================================================
		Serial.print("USBREceive_Length = ");//输出数组的长度
		Serial.println(USBREceive_Length);
		//for (int i = 0; i < USBREceive_Length; i++)
		//{
		//	Serial.print(String("USBREceive_Data ") + "[ " + i + " ] = ");//输出接收到的数值
		//	Serial.write(USBREceive_Data[i]);
		//	Serial.println("");
		//}
		/*USBREceive_Length = 0;*/
		//=======================================================

		USB_Judge(USBREceive_Data);//USB判断函数
	}
	return 0;
}
void USB_Judge(unsigned char *USBREceive_Data)
{
	if (USBREceive_Length == 17)
	{
		//开1号继电器，即Y0_ON，SET_MacValve_1_ON
		if (USBREceive_Data[0] == 'S' && USBREceive_Data[6] == 'c' && USBREceive_Data[12] == '_' &&
			USBREceive_Data[1] == 'E' && USBREceive_Data[7] == 'V' && USBREceive_Data[13] == '1' &&
			USBREceive_Data[2] == 'T' && USBREceive_Data[8] == 'a' && USBREceive_Data[14] == '_' &&
			USBREceive_Data[3] == '_' && USBREceive_Data[9] == 'l' && USBREceive_Data[15] == 'O' &&
			USBREceive_Data[4] == 'M' && USBREceive_Data[10] == 'v' && USBREceive_Data[16] == 'N' &&
			USBREceive_Data[5] == 'a' && USBREceive_Data[11] == 'e')
		{
			Serial.println("輸入的指令為Y0_ON");
			modbus_CRC = N_CRC16(Y0_ON, length);//得到modbus_CRC的值
			Serial.print("modbusCRC16 = ");//输出modbus_CRC的值
			Serial.println(modbus_CRC, HEX);

			Y0_ON[6] = modbus_CRC >> 8;
			Y0_ON[7] = modbus_CRC;

			Serial2.write(Y0_ON, 8);//发送YO_ON的指令
			//delay(5);
			USBREceive_Length = 0;//清空长度，为下次的接收做准备
		}
		else
		{
			Serial.println("輸入信息錯誤，輸入的信息如下（請核對）：");
			for (int i = 0; i < USBREceive_Length; i++)
			{
				//Serial.print(String("USBREceive_Data ") + "[ " + i + " ] = ");//输出接收到的数值
				Serial.write(USBREceive_Data[i]);
				//Serial.println("");
			}
			Serial.println("");
			USBREceive_Length = 0;//清空长度，为下次的接收做准备
		}
	}
	else if (USBREceive_Length == 18)
	{
		//关1号继电器，即Y0_OFF,SET_MacValve_1_OFF
		if (USBREceive_Data[0] == 'S' && USBREceive_Data[6]  == 'c' && USBREceive_Data[12] == '_' &&
			USBREceive_Data[1] == 'E' && USBREceive_Data[7]  == 'V' && USBREceive_Data[13] == '1' &&
			USBREceive_Data[2] == 'T' && USBREceive_Data[8]  == 'a' && USBREceive_Data[14] == '_' &&
			USBREceive_Data[3] == '_' && USBREceive_Data[9]  == 'l' && USBREceive_Data[15] == 'O' &&
			USBREceive_Data[4] == 'M' && USBREceive_Data[10] == 'v' && USBREceive_Data[16] == 'F' &&
			USBREceive_Data[5] == 'a' && USBREceive_Data[11] == 'e' && USBREceive_Data[17] == 'F')//SET_MacValve_1_ON
		{
			Serial.println("輸入的指令為Y0_OFF");
			modbus_CRC = N_CRC16(Y0_OFF, length);//得到modbus_CRC的值
			Serial.print("modbusCRC16 = ");//输出modbus_CRC的值
			Serial.println(modbus_CRC, HEX);

			Y0_OFF[6] = modbus_CRC >> 8;
			Y0_OFF[7] = modbus_CRC;

			Serial2.write(Y0_OFF, 8);//发送YO_OFF的指令
			delay(5);
			USBREceive_Length = 0;//清空长度，为下次的接收做准备
		}
		else
		if (USBREceive_Data[0] == 'S' && USBREceive_Data[6] == 'c' && USBREceive_Data[12] == '_' &&
			USBREceive_Data[1] == 'E' && USBREceive_Data[7] == 'V' && USBREceive_Data[13] == '1' &&
			USBREceive_Data[2] == 'T' && USBREceive_Data[8] == 'a' && USBREceive_Data[14] == '_' &&
			USBREceive_Data[3] == '_' && USBREceive_Data[9] == 'l' && USBREceive_Data[15] == 'O' &&
			USBREceive_Data[4] == 'M' && USBREceive_Data[10] == 'v' && USBREceive_Data[16] == 'F' &&
			USBREceive_Data[5] == 'a' && USBREceive_Data[11] == 'e' && USBREceive_Data[17] == 'F')
		{

		}
		else
		{
			Serial.println("輸入信息錯誤，輸入的信息如下（請核對）：");
			for (int i = 0; i < USBREceive_Length; i++)
			{
				//Serial.print(String("USBREceive_Data ") + "[ " + i + " ] = ");//输出接收到的数值
				Serial.write(USBREceive_Data[i]);
				//Serial.println("");
			}
			Serial.println("");
			USBREceive_Length = 0;//清空长度，为下次的接收做准备
		}
	}
	else
	{
		Serial.println("信息長度錯誤，輸入的信息如下（請核對）：");
		for (int i = 0; i < USBREceive_Length; i++)
		{
			//Serial.print(String("USBREceive_Data ") + "[ " + i + " ] = ");//输出接收到的数值
			Serial.write(USBREceive_Data[i]);
			//Serial.println("");
		}
		Serial.println("");
		USBREceive_Length = 0;//清空长度，为下次的接收做准备
	}
}