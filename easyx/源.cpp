#include"SenSor.h"

int main()
{
	/*
	��ʼ�����λ�ã��ƶ�������ٶ�
	�����   �ƶ�����   �ٶȹ̶�
	�����ж�
	��ǰ�����������λ��
	����max����
	����ھӽڵ�
	*/
	
	Sensor sensor[size];  //�����ڵ�  
	initinal(sensor);     //��ʼ��  λ��  �ƶ�����   �ٶ�  ״̬
	moveSensor(sensor);
	while (1);
}


////��������ʱ��
//DWORD start, end;
//start = timeGetTime();
//
//end = timeGetTime();
//end = end - start;
//long  as = end;
//setbkcolor(WHITE);
//settextcolor(BLACK);
//settextstyle(30,0,("����"));
//char ch[20];
//sprintf_s(ch, "%ld", as);
//strcat_s(ch, "ms");

