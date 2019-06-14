//user_initialization.h
/*
*版权
*
* 文件名称:user_initialization.h
* 文件标识:配置管理计划书
* 摘要:定义了需要初始化的引脚
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


#ifndef USER_INITIALIZATION_H	//防止头文件user_initialization.h被重复调用
#define USER_INITIALIZATION_H
#include<arduino.h>	//引用标准库的头文件
#include<EEPROM.h>



//引脚定义
#define LED3		PC0		//LED3
#define LED4		PC1		//LED4
#define LED1		PC2		//LED1
#define LED2		PC3		//LED2

#define PWR_EN485	PC7		//485外设电源
#define TX_485		PA2		//485TX
#define RX_485		PA3		//485RX

#define K1			PA4		//按键1
#define K2			PA5		//按键2

#define I3			PA6		//
#define I2			PA7		//
#define I1			PC4		//

#define BAT_V		PB1		//
#define BOOT1		PB2		//

#define GPRS_PWR_EN	PB4		//
#define GPRS_PWRKEY	PC11	//
#define GPRS_RST	PC10	//
#define GPRS_TX		PB10	//		
#define GPRS_RX		PB11	//

#define SWDIO		PA13	//

#define USBEN		PC9		//
#define USBDP		PA12	//
#define USBDM		PA11	//

#define LORA_AUX	PA0		//
#define LORA_PWR	PB8		//
#define LORA_TX		PA10	//LORATX
#define LORA_RX		PA9		//LORARX
#define LORA_M1		PB3		//
#define LORA_M0		PD2		//

#define EX_POW		PC8		//
#define MOSI		PB15	//
#define MISO		PA14	//	
#define SCK			PB13	//
#define CS			PB12	//

#define RTC_SDA		PB7		//
#define RTC_SCL		PB6		//
#define WP			PB5		//
#define ANT_PWR_EN	PC12	//
#define NETLIGHT	PA15	//
#define SWCLK		PA14	//

#define V12_PWR		PC6		//

//全局函数声明
void Initialization(void);//初始化函数


//全局变量



//类结构声明



#endif