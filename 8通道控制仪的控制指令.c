Serial.println("输入的指令为Y23_OFF");

modbus_CRC = N_CRC16(Y23_OFF, length);//得到modbus_CRC的值
Y23_OFF[6] = modbus_CRC >> 8;
Y23_OFF[7] = modbus_CRC;

Serial2.write(Y23_OFF, 8);//发送Y23_OFF

Upper temperature limit//温度上限
Lower temperature limit//温度下限

SET_MacValve_1_ON//开继电器1					回执：RESP_MacValve_1_ON
SET_MacValve_1_OFF//关继电器1					回执：RESP_MacValve_1_OFF
GET_MacValve_1_Status//得到继电器的状态			回执：RESP_MacValve_1_Value		// Value 為 ON / OFF

SET_MFC_1_Open//开MFC							回执：RESP_MFC_1_Open
SET_MFC_1_Close//关MFC							回执：RESP_MFC_1_Close
SET_MFC_1_GAS_1000// 1000 means 1sccm			回执：RESP_MFC_1_GAS_1000
GET_MFC_1_GAS//得到MFC的流量					回执：RESP_MFC_1_GAS_Value		// Value 為數值
GET_MFC_1_Status//得到MFC的状态					回执：RESP_MFC_1_Status_Value	// Value 為 ON / OFF

SET_HeatingJackets_TempUppLimit_Value//设定温度上限值	Value 為數值，最小为0000，最大为9999
SET_HeatingJackets_TempLowLimit_Value//设定温度下限值	同上，当温度需要设置为49℃，输入应为0490
SET_HeatingJackets_1_TempDesired_Value//设定通道1期望保持的温度，Value是期望得到的温度值，同上
SET_HeatingJackets_1_Heating//将通道1设置为加热模式
SET_HeatingJackets_1_Cooling//将通道1设置为制冷模式
GET_HeatingJackets_1_Temp//得到通道1的测量温度





//这是整个8通道控制仪共用的参数
SET_HeatingJackets_TempUppLimit_Value//设定温度上限值,Value = 溫度數值
RESP_HeatingJackets_TempUPPlimit_OK//上限值的正确回执
RESP_HeatingJackets_TempUPPlimit_ERR_Overflow//上限值异常（溢出）回执
/*可能有预留的回执信息，暂时不考虑*/


SET_HeatingJackets_TempLowLimit_Value//设定温度下限值,Value = 溫度數值
RESP_HeatingJackets_TempLowLimit_OK//下限值的正确回执
RESP_HeatingJackets_TempLowLimit_ERR_Overflow//下限值异常（溢出）回执
/*可能有预留的回执信息，暂时不考虑*/
//---------------------------------------------------------------------------//

//设置通道X的温度，2级私有参数
SET_HeatingJackets_1_TempDesired_Value//设定通道1期望保持的温度，TempDesired是期望得到的温度值
RESP_HeatingJackets_1_TempDesired_OK//通道1温度参数设置成功回执
RESP_HeatingJackets_1_TempDesired_ERR_Overflow//通道1温度参数设置失败（溢出）回执
/*可能有预留的回执信息，暂时不考虑*/


SET_HeatingJackets_2_TempDesired_Value//设定通道2期望保持的温度，Value是期望得到的温度值
RESP_HeatingJackets_2_TempDesired_OK//通道2温度参数设置成功回执
RESP_HeatingJackets_2_TempDesired_ERR_Overflow//通道2温度参数设置失败（溢出）回执
/*可能有预留的回执信息，暂时不考虑*/


SET_HeatingJackets_3_TempDesired_Value//设定通道3期望保持的温度，TempDesired是期望得到的温度值
RESP_HeatingJackets_3_TempDesired_OK//通道3温度参数设置成功回执
RESP_HeatingJackets_3_TempDesired_ERR_Overflow//通道3温度参数设置失败（溢出）回执
/*可能有预留的回执信息，暂时不考虑*/
//---------------------------------------------------------------------------//


//设置通道X的工作方式，2级私有参数
SET_HeatingJackets_1_Heating//将通道1设置为加热模式
RESP_HeatingJackets_1_Heating_OK//通道1设置加热模式成功回执
RESP_HeatingJackets_1_Heating_ERR//通道1设置加热模式失败回执


SET_HeatingJackets_1_Cooling//将通道1设置为制冷模式
RESP_HeatingJackets_1_Cooling_OK//通道1设置制冷模式成功回执
RESP_HeatingJackets_1_Cooling_ERR//通道1设置制冷模式失败回执


SET_HeatingJackets_2_Heating//将通道2设置为加热模式
RESP_HeatingJackets_2_Heating_OK//通道1设置加热模式成功回执
RESP_HeatingJackets_2_Heating_ERR//通道1设置加热模式失败回执


SET_HeatingJackets_2_Cooling//将通道2设置为制冷模式
RESP_HeatingJackets_2_Cooling_OK//通道2设置制冷模式成功回执
RESP_HeatingJackets_2_Cooling_ERR//通道2设置制冷模式失败回执
//---------------------------------------------------------------------------//


//得到通道X的测量温度，2级私有参数，查询
GET_HeatingJackets_1_Temp//得到通道1的测量温度
RESP_HeatingJackets_1_Temp_Value //通道1温度的回执，Value = 溫度數值

GET_HeatingJackets_2_Temp//得到通道2的测量温度
RESP_HeatingJackets_2_Temp_Value //通道2温度的回执，Value = 溫度數值
//---------------------------------------------------------------------------//