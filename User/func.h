/********************************************************************
���ߣ�Songyimiao
��������: 20151129
�汾��V2.0
����ʵ���Ұ�Ȩ����
/********************************************************************/
#ifndef _CARSTAND_H_
#define _CARSTAND_H_
extern int PWM1,PWM2,PWM3,PWM4;
extern int g_LastCountRunAway,g_CountRunAway;		   
extern float g_Throttle; //����
extern double pitch, yaw, roll;
extern double Angle_ax, Angle_ay, Angle_az;
extern double Angle_gx, Angle_gy, Angle_gz;
extern int   g_iAccel_X_Axis,g_iAccel_Y_Axis,g_iAccel_Z_Axis ;	//���ٶ�X������
extern int   g_iGyro_X_Axis,g_iGyro_Y_Axis,g_iGyro_Z_Axis  ;	//������Y������
extern float g_fPower;
extern unsigned char g_ucLEDCount;
extern int g_fGyroXOffset,g_fGyroYOffset,g_fGyroZOffset;
extern char g_fOffsetx,g_fOffsety;
extern int i;
extern unsigned char unlock;
extern unsigned short SoftTimer;

void DriversInit(void);
int DataSynthesis(unsigned char REG_Address);
void SampleInputVoltage(void);	
void GetGyroRevise(void);
void BatteryChecker();
void ParametersInit();
void Kalman_Filter(float data Accel,float data Gyro,float data Angle,float data Gyro_R);
void TickSound();
void LEDRUN();
void AttitudeControl();
#endif