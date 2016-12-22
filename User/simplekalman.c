#include "simplekalman.h"
#include "math.h"

float k=0;  //Kalman����
float p=0;  //Ԥ�����Э����
float q=0;  //Ԥ�����
float r=0;  //�������������
float x=0;  //����ֵ

void SimpleKalman(float q1,float r1){
	q=q1;
	r=r1;	
	p = sqrt(q1*q1+r1*r1);
}

float UpdateSimpleKalman(float value){
	p+=q;
	k=p/(p+r);
	x+=k*(value-x);
	p*=(1-k);

	return x;
}