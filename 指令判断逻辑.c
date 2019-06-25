指令判断逻辑.c

//ctrl + x为删除该行


//继电器相关
SET_MacValve_1_ON		//开继电器			01 05 0000 FF00
SET_MacValve_1_OFF		//关继电器			01 05 0000 0000
GET_MacValve_1_Status	//得到继电器的状态	01 01 0000 0001

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