#include"SenSor.h"

int main()
{
	/*
	初始化点的位置，移动方向和速度
	随机数   移动方向   速度固定
	出界判断
	当前点与其他点的位置
	输入max功率
	输出邻居节点
	*/
	
	Sensor sensor[size];  //声明节点  
	initinal(sensor);     //初始化  位置  移动方向   速度  状态
	moveSensor(sensor);
	while (1);
}


////程序运行时间
//DWORD start, end;
//start = timeGetTime();
//
//end = timeGetTime();
//end = end - start;
//long  as = end;
//setbkcolor(WHITE);
//settextcolor(BLACK);
//settextstyle(30,0,("宋体"));
//char ch[20];
//sprintf_s(ch, "%ld", as);
//strcat_s(ch, "ms");

