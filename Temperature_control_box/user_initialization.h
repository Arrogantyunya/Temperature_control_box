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
#define LED1        PC3     //LED1
#define LED2        PC2     //LED2
#define LED3        PC1     //LED3
#define LED4        PC0     //LED4
#define K1          PA0     //K1按键
#define K2          PA1     //K1按键
#define KCZJ1       PB12    //继电器1
#define KCZJ2       PB13    //继电器2
#define A01         PA6     //模拟输出1
#define A02         PA7     //模拟输出2     
#define PWR         PA4     //12V升压模块供电
#define DE          PA5     //485模块供电
#define LORA_PWR    PB4     //LORA模块供电
#define LORA_TX     PB11    //LORA TX串口输出
#define LORA_RX     PB10    //LORX RX串口输入
#define AT_CMD      PB3     //高电平时为AT 模式，低电平为透传模式
#define WAKE_UP     PD2     //LORA模块唤醒引脚
#define RESETN      PC12    //LORA模块复位引脚
#define VIN1        PC4     //模拟输入电压1
#define VIN2        PC5     //模拟输入电压2
#define EX_POW		PB0		//
#define BAT_V		PB1		//
#define	BOOT1		PB2		//
#define	SWCLK		PA1		//
#define EEPROM_SDA  PB7     //EEPROM_SDA
#define EEPROM_SCL  PB6     //EEPROM_SCL
#define MCU_RX      PA10    //MCU_RX
#define MCU_TX      PA9     //MCU_TX
#define DE_485      PA5     //485DE
#define RX_485      PA3     //485RX
#define TX_485      PA2     //485TX
#define USBDM		PA11	//usbdm
#define USBDP		PA12	//usbdp
#define SWDIO		PA13	//swdio
#define	RESETn		PC12	//reset_n
#define Wake_Up		PD2		//wake_up
#define	WP			PB5		//wp

//全局函数声明
void Initialization(void);//初始化函数


//全局变量



//类结构声明



#endif