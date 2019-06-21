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

static unsigned char Temp3_2[8] = { 0x03,0x06,0x00,0x1D,0x01,0xC3 };
static unsigned char Temp4_2[8] = { 0x04,0x06,0x00,0x1D,0x01,0xC3 };

String str_usb;

static unsigned short length = 6;

static int modbus_CRC = 0x00;
static int RS485_CRC = 0x00;
static unsigned char RS485REceive_Data[50];
static int RS485REceive_Length = 0;
static unsigned char USBREceive_Data[50];
static int USBREceive_Length = 0;
static unsigned char LORAEceive_Data[50];
static int LORAREceive_Length = 0;


//相关函数的定义
int RS485Receive_information();			//RS485接收函数
int LORAReceive_information();			//RS485接收函数
int USB_Serial_reception();					//USB串口的接收函数
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
}

int RS485Receive_information(void)
{
	RS485REceive_Length = 0;
	delay(500);
	while (Serial2.available() > 0)
	{
		RS485REceive_Data[RS485REceive_Length++] = Serial2.read();
		Serial.print(RS485REceive_Data[RS485REceive_Length - 1], HEX);
		Serial.print(" ");
	}
	if (RS485REceive_Length > 0)
	{
		Serial.println("");
		Serial.print("RS485REceive_Length = ");
		Serial.println(RS485REceive_Length);
		for (int i = 0; i < RS485REceive_Length; i++)
		{
			Serial.print(String("RS485REceive_Data") + "[ " + i + " ] =");
			Serial.println(RS485REceive_Data[i], HEX);
		}

		RS485_CRC = N_CRC16(RS485REceive_Data, RS485REceive_Length-2);
		Serial.print("RS485_CRC = ");
		Serial.println(RS485_CRC,HEX);

		RS485REceive_Length = 0;
	}
	return RS485_CRC;
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
		Serial.print(String("USB REceive_Data = "));//输出USB接收数据的长度
		Serial.println(USBREceive_Length);

		Serial.println("USB串口接收到的数据为：");

		for (int i = 0; i < USBREceive_Length; i++)
		{
			//Serial.print(String("USBREceive_Data") + "[ " + i + " ] ");
			Serial.print(USBREceive_Data[i],HEX);
			Serial.print("");
		}
		Serial.println("");

		USB_Judge(USBREceive_Data);//
	}
	return 0;
}
void USB_Judge(unsigned char *USBREceive_Data)
{
	if (USBREceive_Data[0] == '3' && USBREceive_Data[1] == '_' && USBREceive_Data[2] == '2')
	{
		Serial.println("输入的指令为Temp3_2");

		modbus_CRC = N_CRC16(Temp3_2, length);//得到modbus_CRC的值
		Temp3_2[6] = modbus_CRC >> 8;
		Temp3_2[7] = modbus_CRC;

		Serial2.write(Temp3_2, 8);//发送Temp3_2
	}
	else if (USBREceive_Data[0] == '4' && USBREceive_Data[1] == '_' && USBREceive_Data[2] == '2')
	{
		Serial.println("输入的指令为Temp4_2");

		modbus_CRC = N_CRC16(Temp4_2, length);//得到modbus_CRC的值
		Temp4_2[6] = modbus_CRC >> 8;
		Temp4_2[7] = modbus_CRC;

		Serial2.write(Temp4_2, 8);//发送Temp4_2
	}

	//========================================================================================================
	if (USBREceive_Data[0] == 'S' && USBREceive_Data[1] == 'E' && USBREceive_Data[2] == 'T' &&
		USBREceive_Data[3] == '_')
		//在这里判断进入了SET的命令
	{
		if (USBREceive_Data[4]  == 'M' && USBREceive_Data[5]  == 'a' && USBREceive_Data[6]  == 'c' &&
			USBREceive_Data[7]  == 'V' && USBREceive_Data[8]  == 'a' && USBREceive_Data[9]  == 'l' &&
			USBREceive_Data[10] == 'v' && USBREceive_Data[11] == 'e' && USBREceive_Data[12] == '_')
			//在这里判断进入了继电器的设置
		{
			if ((USBREceive_Data[15] == 'O' && USBREceive_Data[16] == 'N')||(USBREceive_Data[16] == 'O' && USBREceive_Data[17] == 'N'))
				//在这里判断进入了ON的指令
			{
				if (USBREceive_Data[13] == '1' && USBREceive_Data[14] == '_' )
				//在这里判断进入了1继电器开
				{
					Serial.println("输入的指令为Y0_ON");

					modbus_CRC = N_CRC16(Y0_ON, length);//得到modbus_CRC的值
					Y0_ON[6] = modbus_CRC >> 8;
					Y0_ON[7] = modbus_CRC;

					Serial2.write(Y0_ON, 8);//发送Y0_ON

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_1_ON");//回执信息
					}
				}
				else if (USBREceive_Data[13] == '2' && USBREceive_Data[14] == '_')
				//在这里判断进入了2继电器开
				{
					Serial.println("输入的指令为Y1_ON");

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
					Serial.println("输入的指令为Y2_ON");

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
					Serial.println("输入的指令为Y3_ON");

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
					Serial.println("输入的指令为Y4_ON");

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
					Serial.println("输入的指令为Y5_ON");

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
					Serial.println("输入的指令为Y6_ON");

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
					Serial.println("输入的指令为Y7_ON");

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
					Serial.println("输入的指令为Y8_ON");

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
					Serial.println("输入的指令为Y9_ON");

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
					Serial.println("输入的指令为Y10_ON");

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
					Serial.println("输入的指令为Y11_ON");

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
					Serial.println("输入的指令为Y12_ON");

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
					Serial.println("输入的指令为Y13_ON");

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
					Serial.println("输入的指令为Y14_ON");

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
					Serial.println("输入的指令为Y15_ON");

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
					Serial.println("输入的指令为Y16_ON");

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
					Serial.println("输入的指令为Y17_ON");

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
					Serial.println("输入的指令为Y18_ON");

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
					Serial.println("输入的指令为Y19_ON");

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
					Serial.println("输入的指令为Y20_ON");

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
					Serial.println("输入的指令为Y21_ON");

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
					Serial.println("输入的指令为Y22_ON");

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
					Serial.println("输入的指令为Y23_ON");

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

			else if((USBREceive_Data[15] == 'O' && USBREceive_Data[16] == 'F' && USBREceive_Data[17] == 'F') || 
					(USBREceive_Data[16] == 'O' && USBREceive_Data[17] == 'F' && USBREceive_Data[18] == 'F'))
				//在这里判断进入了OFF命令
			{ 
				if (USBREceive_Data[13] == '1' && USBREceive_Data[14] == '_')
					//在这里判断进入了1继电器关
				{
					Serial.println("输入的指令为Y0_OFF");

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
					Serial.println("输入的指令为Y1_OFF");

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
					Serial.println("输入的指令为Y2_OFF");

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
					Serial.println("输入的指令为Y3_OFF");

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
					Serial.println("输入的指令为Y4_OFF");

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
					Serial.println("输入的指令为Y5_OFF");

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
					Serial.println("输入的指令为Y6_OFF");

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
					Serial.println("输入的指令为Y7_OFF");

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
					Serial.println("输入的指令为Y8_OFF");

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
					Serial.println("输入的指令为Y9_OFF");

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
					Serial.println("输入的指令为Y10_OFF");

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
					Serial.println("输入的指令为Y11_OFF");

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
					Serial.println("输入的指令为Y12_OFF");

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
					Serial.println("输入的指令为Y13_OFF");

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
					Serial.println("输入的指令为Y14_OFF");

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
					Serial.println("输入的指令为Y15_OFF");

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
					Serial.println("输入的指令为Y16_OFF");

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
					Serial.println("输入的指令为Y17_OFF");

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
					Serial.println("输入的指令为Y18_OFF");

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
					Serial.println("输入的指令为Y19_OFF");

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
					Serial.println("输入的指令为Y20_OFF");

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
					Serial.println("输入的指令为Y21_OFF");

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
					Serial.println("输入的指令为Y22_OFF");

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
					Serial.println("输入的指令为Y23_OFF");

					modbus_CRC = N_CRC16(Y23_OFF, length);//得到modbus_CRC的值
					Y23_OFF[6] = modbus_CRC >> 8;
					Y23_OFF[7] = modbus_CRC;

					Serial2.write(Y23_OFF, 8);//发送Y23_OFF

					if (modbus_CRC == RS485Receive_information())
					{
						Serial.println("RESP_MacValve_24_OFF");//回执信息
					}
				}
			}
		}
	}
}