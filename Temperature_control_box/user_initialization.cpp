//user_initialization.cpp
/*
*版权
*
* 文件名称:user_initialization.cpp
* 文件标识:配置管理计划书
* 摘要:对引脚进行初始化
*
* 当前版本:V1.0
* 作者:刘家辉
* 完成日期:
* 修改者:
* 修改日期:
*
* 取代版本:
* 原作者:刘家辉
* 完成日期:
*/


#include"user_initialization.h"	//引用头文件

//函 数 名：Initialization() 
//功能描述：初始化的函数
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
void Initialization()//初始化函数
{
    //初始化引脚
    afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY);//因为引脚复用
	pinMode(USBEN, OUTPUT);//USB使能
	//pinMode(PWR_EN485, OUTPUT);//485模块使能
	pinMode(V12_PWR,OUTPUT);
    //pinMode(RESETN,OUTPUT);//复位电路，给高电平进行复位
    //pinMode(KCZJ1,OUTPUT);//继电器
    //pinMode(KCZJ2,OUTPUT);
    //pinMode(PWR,OUTPUT);//因为取消掉了MOS管，直接跳线，导致PWR无法使用
    pinMode(LED1,OUTPUT);
    pinMode(LED2,OUTPUT);
    pinMode(LED3,OUTPUT);
    pinMode(LED4,OUTPUT);
    //pinMode(A01,OUTPUT);//缺少IC1 TLV2472芯片，该模块无法使用
    //pinMode(A02,OUTPUT);
    pinMode(K1,INPUT);//按键
    pinMode(K2,INPUT);   
    pinMode(LORA_PWR,OUTPUT);//LORA
 //   pinMode(AT_CMD,OUTPUT);
 //   pinMode(WAKE_UP,OUTPUT);
	//pinMode(VIN1,INPUT);//模拟输入
	//pinMode(VIN2,INPUT);
	//pinMode(DE_485, OUTPUT);//485使能引脚，低电平发送，高电平接收
    
    //初始化串口
	digitalWrite(USBEN, LOW);//USB使能引脚
    Serial.begin(9600);		//USB的串口

	//Serial1.begin(9600);	//LORA的串口

	//digitalWrite(PWR_EN485,HIGH);//485使能引脚
	Serial2.begin(9600);	//485的串口

    //Serial3.begin(9600);	//GPRS的串口

    ////继电器初始化//
    //digitalWrite(KCZJ1,HIGH);
    //digitalWrite(KCZJ2,HIGH);

    //LED初始化
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,LOW);
    digitalWrite(LED4,LOW);
    
    //lora相关初始化//
    digitalWrite(LORA_PWR,HIGH);
    //digitalWrite(RESETN,HIGH);
    //digitalWrite(AT_CMD,LOW);

	digitalWrite(V12_PWR,HIGH);//12V电源使能

	delay(1000);
	Serial.println("初始化完成");
}
