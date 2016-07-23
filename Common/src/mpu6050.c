
#include "MPU6050.H"

/***************************************************************
** ��������: MPU6050Init
** ��������: MPU6050��ʼ������
** �䡡��:   
** �䡡��:   
** ȫ�ֱ���: 
** ������:   ����ʵ����
** ��  ����  Http://miaowlabs.taobao.com
** �ա���:   2014��08��01��
***************************************************************/
void MPU6050Init(void)
{
	Single_WriteI2C(PWR_MGMT_1, 0x00)  ; //�������״̬
	Single_WriteI2C(SMPLRT_DIV, 0x07)  ; //������125hz
	Single_WriteI2C(CONFIG, 0x04)      ; //Accelerometer:21hz 8.5ms ; Gyroscope:20hz 8.3ms
	Single_WriteI2C(GYRO_CONFIG, 0x08) ; // ������500��/S 65.5LSB/g 
	Single_WriteI2C(ACCEL_CONFIG, 0x08); // ���ٶ�+-4g  8192LSB/g
}








