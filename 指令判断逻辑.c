指令判断逻辑.c

//ctrl + x为删除该行


//继电器相关
SET_MacValve_1_ON		//开继电器			01 05 0000 FF00
SET_MacValve_1_OFF		//关继电器			01 05 0000 0000
GET_MacValve_1_Status	//得到继电器的状态	01 01 0000 0008

//MFC相关
SET_MFC_1_Open//开MFC
SET_MFC_1_Close//关MFC
SET_MFC_1_GAS_1000// 1000 means 1sccm
GET_MFC_1_GAS//得到MFC的流量
GET_MFC_1_Status//得到MFC的状态

//温度通道相关
SET_HeatingJackets_TempUppLimit_Value//设定温度上限值			03 06 0005 01C3
SET_HeatingJackets_TempLowLimit_Value//设定温度下限值			03 06 0004 01C3
SET_HeatingJackets_1_TempDesired_Value//设定通道1期望保持的温度	03 06 0009 01C3
SET_HeatingJackets_1_Heating//将通道1设置为加热模式				03 06 0011 0000
SET_HeatingJackets_1_Cooling//将通道1设置为制冷模式				03 06 0011 0001
GET_HeatingJackets_1_Temp//得到通道1的测量温度					03 03 1001 0001


//=============================================================
//判断进入了1通道的温度期望设定
if (USBREceive_Data[19] == '1' && USBREceive_Data[20] == '_')
{
	TempDesired = ((USBREceive_Data[33] - 48) * 1000) + ((USBREceive_Data[34] - 48) * 100) + ((USBREceive_Data[35] - 48) * 10) + (USBREceive_Data[36] - 48);
	Serial.print("TempDesired = ");
	Serial.println(TempDesired);

	int x = 4294967295; //4294967295这是最大值
	int hex = 0x1;
	long a;
	char array[33] = {};
	char hexarr[] = { 0x0A,0x0C };
	String str[10];
	String strDemo = "Hi";
	//str[0] = "Hello World";                      // 使用赋值的方法直接定义String对象 
	str[1] = String('a');                        // 将字符转为String对象
	str[2] = String("This is a string");         // 将字符串转为String对象
	str[3] = String(strDemo + " my lover");      // 将String对象和普通字符串通过+连接
	str[4] = String(12);                         // 将普通数字转换为String对象
	str[5] = String(12, HEX);                    // 将十进制转为十六进制表示的String对象
	str[6] = String(255, BIN);                   // 将十进制转为二进制表示的String对象
	str[7] = String(B11111111, DEC);             // 将二进制转为十六进制表示的String对象
	str[8] = String(32769, DEC);                 // 长整型用十进制表示转换为String对象
	str[9] = String(5.6985, 3);                  // 保留3位浮点数表示String对象
	str[0] = "RESP_MacValve_24_OFF" + str[7]+"_";
	for (int i = 0; i < 10; i++) {
		Serial.print(String("str") + i + ": ");
		Serial.println(str[i]);
	}
	char *ptrhex = hexarr;
	char *ptrarr = NULL;
	//ptrarr = inttohex1(x);//char * inttohex1(int aa)
	ptrarr = inttohex2(x);//char * inttohex2(int aa)
	//ptrarr = inttohex3(x);//char * inttohex3(int aa)

	Serial.print("array = ");
	Serial.print(*(ptrarr + 0));
	Serial.print(*(ptrarr + 1));
	Serial.print(*(ptrarr + 2));
	Serial.print(*(ptrarr + 3));
	Serial.print(*(ptrarr + 4));
	Serial.print(*(ptrarr + 5));
	Serial.print(*(ptrarr + 6));
	Serial.println(*(ptrarr + 7));


	Serial.print("inttohex2(x) = ");
	Serial.println(inttohex2(x));

	a = charhex_to_dec(ptrhex);//int charhex_to_dec(char *chr)
	Serial.print("a = ");
	Serial.println(a);

	Serial.print("charhex_to_dec(ptrhex) = ");
	Serial.println(charhex_to_dec(ptrhex));

	//a = hextodec1(hex);//int hextodec1(int aa)
	//Serial.println(a);
	//Serial.print("hextodec1(hex) = ");
	//Serial.println(hextodec1(hex));

	//------------------------------------------------
	//unsigned char TEM[10];
	//TEM = DEC_to_HEX(TempDesired);
	//Serial.print("DEC_to_HEX	TempDesired = ");
	//Serial.println(TempDesired);
	///*String T;
	//T = String(TempDesired);*/
	///*char *T;
	//*T = TempDesired;*/
	///*char *T;
	//*T = 0xff;*/
	//TempDesired = charhex_to_dec(T);
	//Serial.print("charhex_to_dec	TempDesired = ");
	//Serial.println(TempDesired);
	/*for (size_t i = 33; i < 37; i++)
	{
		Serial.print(String("USBREceive_Data") + "[ " + i + " ] ");
		Serial.println(USBREceive_Data[i]);
	}*/
	//------------------------------------------------------------
}


//判断是否进入了SET命令
if (SET_)
{
	//控制继电器
	if(MacValve_)
	{
		//判断进入了ON，需要考虑10位以上的情况
		if(ON)
		{
			//判断进入了1继电器
			if(1_)
			{
				
			}
			//判断进入了2继电器
			else if(2_)
			{
				
			}
			//...
		}
		//判断进入了OFF，需要考虑10位以上的情况
		else if(OFF)
		{
			//判断进入了1继电器
			if(1_)
			{
				
			}	
			//判断进入了2继电器
			else if(2_)
			{
				
			}
			//...
		}
	}
	//控制温度通道
	else if(HeatingJackets_)
	{
		//判断进入设置通道的温度值
		if(TempDesired_)
		{
			//判断是第1通道
			if(1_)
			{
				
			}
			//判断是第2通道
			else if(1_)
			{
				
			}
			//...
		}
		//判断进入设置下限值
		else if(TempUppLimit_)
		{
			
		}
		//判断进入设置上限值
		else if(TempLowLimit_)
		{
			
		}
		//判断进入设置加热模式
		else if(Heating)
		{
			
		}
		//判断进入设置制冷模式
		else if(Cooling)
		{
			
		}
	}
	//进入了MFC
	else if(MFC_)
	{
		//判断进入了Open，需要考虑10位以上的情况
		if(Open)
		{
			//判断进入了1MFC
			if(1_)
			{
				
			}
			//判断进入了2MFC
			else if(2_)
			{
				
			}
			//...
		}
		//判断进入了Close，需要考虑10位以上的情况
		else if(Close)
		{
			//判断进入了1MFC
			if(1_)
			{
				
			}	
			//判断进入了2MFC
			else if(2_)
			{
				
			}
			//...
		}
	}
}
//判断是否是GET命令
else if (GET_)
{
	//查询温度通道
	if(HeatingJackets_)
	{
		//查询温度通道1
		if(1_)
		{
			
		}
		//查询温度通道2
		else if(2_)
		{
			
		}
		//...
	}
	//判断进入了MFC
	else if(MFC_)
	{
		//查询MFC的流量
		if(GAS)
		{
			//查询MFC1的流量
			if(1_)
			{
				
			}
			//查询MFC1的流量
			else if(2_)
			{
				
			}
			//...
		}
		//
		else if(Status)
		{
			//查询MFC1的状态
			if(1_)
			{
				
			}
			//查询MFC2的状态
			else if(2_)
			{
				
			}
			//...
		}
	}
}
//
else if ()
{
	
}