
#include "adc.h"
#include "intrins.h"

void ADCInit(void)
{
    P1ASF |= 0x04;                  //P1.2����Ϊģ�⹦��A/Dʹ��
    ADC_RES = 0;                    //�������Ĵ���
    ADC_CONTR = 0x80;				//20M/540=37kHzת���ٶ�

}

/*----------------------------
��ȡADC���
----------------------------*/
unsigned char GetADCResult(void)
{

     ADC_CONTR = 0x8A;
    _nop_();                        //�ȴ�4��NOP
    _nop_();
    _nop_();
    _nop_();
    while (!(ADC_CONTR & 0x10));//�ȴ�ADCת�����
    ADC_CONTR &= ~0x10;         //Close ADC

    return ADC_RES;                 //����ADC���
	 
}