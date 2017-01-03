/********************************************************************
���ߣ�Songyimiao
��������: 20160411
�汾��V1.0
����ʵ���Ұ�Ȩ����
/********************************************************************/
#include "includes.h"
 
/***************************************************************
** ����  ��: Songyibiao
** ��    ����http://www.miaowlabs.com
** ��    ����http://miaowlabs.taobao.com
** �ա�  ��: 2015��11��29��
** ��������: main()
** ��������: ������            
** �䡡  ��:   
** �䡡  ��:   
** ��    ע: �ο�STC��Դ���� ��л��ͬѧ
    //ʧ�أ�TxBuf[0] 
	//���ţ�TxBuf[1]
    //Yaw��	TxBuf[4]
    //������TxBuf[2]
    //�����TxBuf[3]
********************����ʵ���Ұ�Ȩ����**************************
***************************************************************/
void main()
{
	DisableInterrupts();//��ֹ���ж�
	DriversInit();//�ײ�������ʼ��		
	MPU6050Init();//MPU6050��ʼ��
	LEDRUN();//���������� 

	GetGyroRevise();//У��������	
//	LED_GREEN = 1; //�̵���
	ParametersInit();//ϵͳ������ʼ��
	SimpleKalman(0.3,1.0); //һά�������˲���ʼ��
	Delaynms(50);//��ʱ50ms	
	
	IAPRead(); //������⵽���¹����ݾͶ���������ȡIAP����

	while(NRF24L01_Check())//��ⲻ��24L01
	{
		Delaynms(500);
		LED_RED=~LED_RED;  
		Delaynms(500);
		LED_RED=~LED_RED; 
	} 
	init_NRF24L01();
	SetRX_Mode();	 //����ģʽ

	Delaynms(10);	 
	RxBuf[1]=255; //����ͨ��
	RxBuf[2]=128; //����
	RxBuf[3]=128; //���
	RxBuf[4]=128;//yaw
	
	LED2=0;	//β��
	LED1=0;	//β��
	TickSound();  //�������� �õ�T2
				
	EnableInterrupts();//�������ж�	 
									  
	while(1)
	{
	TxBuf[1]=(int)roll;
	TxBuf[2]=(int)pitch;	
	TxBuf[0]=(int)(g_fPower*10);	 //-128-127 
	  STC_ISP();	//ISP ���ز��������� 				   
	if(!SoftTimer){
		SoftTimer = 10;
		SetTX_Mode();
	  	nRF24L01_TxPacket(TxBuf);	//����ģʽ	
		Delaynms(1);
	  	SetRX_Mode();
	}
	  nRF24L01_RxPacket(RxBuf);
	  BatteryChecker();
	 
	if(RxBuf[5]==1)	   //�����Ҳఴť-->У�����ٶȼ�
	  {
	    DisableInterrupts();//�ر��жϣ���ֹ���ŵ�IAPд��
		IAP_Angle();
		RxBuf[5]=0;
		TickSound();
		EnableInterrupts(); 
	  }
	  if(RxBuf[6]==1)  //������ఴť-->У��������
	  {
	  	DisableInterrupts();//�ر��жϣ���ֹ���ŵ�IAPд��
		IAP_Gyro();
		RxBuf[6]=0;
		TickSound();
	    EnableInterrupts();
	  }
	  
	  if(i>=10){
	   i=0;
	   if(RxBuf[8]==1)	  //y  ΢����ť
	   {
		  RxBuf[8]=0;
		  g_fOffsety-=1;
		//TickSound();
	   }	
	   if(RxBuf[9]==1)
	   {
		  RxBuf[9]=0;
		  g_fOffsety+=1;
		//TickSound();
		  }	
		  if(RxBuf[10]==1)	  //x
		  {
		  	RxBuf[10]=0;
		  	g_fOffsetx-=1;
		//	TickSound();
		  }	
		  if(RxBuf[7]==1)
		  {
		  	RxBuf[7]=0;
		  	g_fOffsetx+=1;
		//	TickSound();
		  }				
		}

	  
#if 0//DEBUG_UART  //�������� Ԥ��������

	OutData[0] = 45;
  	OutData[1] = 90;  
   	OutData[2] = g_fPower ;
   	OutData[3] = yaw;  

   	OutPut_Data();		
	 	  
#endif	 		
					
	}
}
