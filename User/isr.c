/********************************************************************
���ߣ�Songyimiao
��������: 20151129
�汾��V2.0
����ʵ���Ұ�Ȩ����
/********************************************************************/
#include "includes.h"



/***************************************************************
** ����  ��: Songyibiao
** ��    ����http://www.miaowlabs.com
** ��    ����http://miaowlabs.taobao.com
** �ա�  ��: 2015��11��29��
** ��������: Timer1_Update
** ��������: 100hz�жϷ�����            
** �䡡  ��:   
** �䡡  ��:   
** ��    ע: 
********************����ʵ���Ұ�Ȩ����**************************
***************************************************************/
void Timer1_Update(void) interrupt  3		//100hz
{  
//	short tst16 = g_iAccel_X_Axis;
	i++;

	g_Throttle=(float)(255 - RxBuf[1]);	//����	RxBuf[1]:0-255

	if(g_Throttle>20)//������Ŵ���80 �������
	{
		if(RxBuf[0]==g_LastCountRunAway)//���RxBuf[0]������û���յ� ��ʸ��
		{
			g_CountRunAway++;  //״̬��ʶ+1
			if(g_CountRunAway>128){g_CountRunAway=128;}  //״̬��ʶ����128��1��û���յ����ݣ�ʧ�ر���
		}
		else{g_CountRunAway=0;}
	}
	else{g_CountRunAway=0;} //�յ��ź��˳�ʧ�ر���
	if(g_CountRunAway==128){g_Throttle=30;RxBuf[1]=128;RxBuf[2]=128;} //����ʧ�ر��� ����Ϊ1����һ�㣬�����½������������������

	
	g_LastCountRunAway=RxBuf[0];
	SampleInputVoltage();

	Angle_ax=(float)g_iAccel_X_Axis/8192;  //���ٶȴ���
	Angle_ay=(float)g_iAccel_Y_Axis/8192;  //ת����ϵ8192LSB/g
	Angle_az=(float)g_iAccel_Z_Axis/8192;  //���ٶ����� +-4g/S
	Angle_gx -= g_fGyroXOffset;
	Angle_gy -= g_fGyroYOffset;
	Angle_gz -= g_fGyroZOffset;
	Angle_gx=(float)g_iGyro_X_Axis/65.5;   //�����Ǵ���
	Angle_gy=(float)g_iGyro_Y_Axis/65.5;   //���������� 
	Angle_gz=(float)g_iGyro_Z_Axis/65.5;   //ת����ϵ65.5LSB/��
	
//***********************************��Ԫ��***********************************
	IMUupdate(Angle_gx*0.0174533,Angle_gy*0.0174533,Angle_gz*0.0174533,Angle_ax*0.0174533,Angle_ay*0.0174533,Angle_az*0.0174533);
	//*0.0174533ΪPI/180 Ŀ���ǽ��Ƕ�ת����

	if(123<TxBuf[2]<133)
	{
	TxBuf[2]=128;
	}
	if(123<TxBuf[3]<133)
	{
	TxBuf[3]=128;
	}
	if(113<TxBuf[4]<143)
	{
	TxBuf[4]=128;
	}

	AttitudeControl();
							  
	if(g_Throttle>=20)
	{PWM(PWM3,PWM2,PWM1,PWM4);}	 //���2345-   PWM3/PWM2/PWM1/PWM4
	else 
	{PWM(1000,1000,1000,1000);}	  
	
/*	
 	UART1SendByte(0x9c);
 	UART1SendByte(0x00);
 	UART1SendByte(tst16&0xf);
 	UART1SendByte(tst16>>8);*/							  
#if 0//DEBUG_UART  //�������� Ԥ��������

   	OutData[0] = Angle_gx;
  	OutData[1] = Angle_gy;
   	OutData[2] = pitch;//��ӦAngle_gy
   	OutData[3] = roll; //��ӦAngle_gx ��ӦӲ��Y��  
//	OutData[0] = g_fOffsetx;
 // 	OutData[1] = g_fOffsety;   	
//	OutData[2] = g_fPower;
//  	OutData[3] = yaw; 
   	OutPut_Data();		
		 	  
#endif	 		
	
  		g_ucLEDCount++;
   		if(g_ucLEDCount >=125) //LED1��1�뽻����˸
   		{
			g_ucLEDCount=0;
	 		LED_GREEN = ~LED_GREEN;
   		}
			 
}


				 