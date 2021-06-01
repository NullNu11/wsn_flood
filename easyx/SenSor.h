#include<graphics.h>
#include<iostream>
#include<stdio.h>
#include<string>
#include<map>
#include <windows.h>
#include<vector>
#include<time.h>
#pragma comment(lib,"winmm.lib")//节点规模
#define size  20
using namespace std;
//节点的位置和移动的方向，速度

class Sensor {
public:
	int sensor_x = 0;
	int sensor_y = 0;
	int	state = 0;
	int driection = 0;
	int speed = 0;
};
int findClick(Sensor(&sensor)[size],int type);
void neighbor(Sensor(&sensor)[size],int a);
void flood(Sensor(&sensor)[size],int a);

//界面初始化
void initinal(Sensor(&sensor)[size]) {
	initgraph(1000, 800);
	srand((unsigned)time(NULL));
	sensor[0].sensor_x = 20;
	sensor[0].sensor_y = 60;
	sensor[0].speed = 10;//10  20   30
	sensor[0].driection = 1;//0-7  八个方向
	setfillcolor(WHITE);
	fillrectangle(0, 0, 1000, 800);
	setfillcolor(RGB(230, 230, 230));
	//边框
	bar(0, 0, 50, 800);
	bar(950, 0, 1000, 800);
	bar(0, 0, 1000, 50);
	bar(0, 700, 1000, 800);
	//初始化
	for (int i = 0; i < size; i++)
	{
		//位置
		sensor[i].sensor_x = (rand() % 880) + 60;
		sensor[i].sensor_y = (rand() % 630) + 60;
		//方向
		sensor[i].driection = (rand() % 8);
		//速度
		int speed = (rand() % 3);
		switch (speed)
		{
		case 1:
			sensor[i].speed = 10;
			break;
		case 2:
			sensor[i].speed = 20;
			break;
		case 0:
			sensor[i].speed = 15;
			break;
		}
	}
}
void moveSensor(Sensor(&sensor)[size]) {

	while (true)
	{	
		Sleep(50);
		for (int i = 0; i < size; i++)
		{
			//出界   换方向
			switch (sensor[i].driection)
			{
			case 1:	
				if (sensor[i].sensor_x > 940)
					sensor[i].driection = 3;
				break;
			case 2:
				
				if (sensor[i].sensor_y > 690)
					sensor[i].driection = 4;
				
				break;
			case 3:
				
				if (sensor[i].sensor_x < 60)
					sensor[i].driection = 1;
				
				break;
			case 4:				
				if (sensor[i].sensor_y < 60)
					sensor[i].driection = 2;
				break;

			case 5:				
				if (sensor[i].sensor_y > 690)
					sensor[i].driection = 0;
				if(sensor[i].sensor_x > 940)
					sensor[i].driection = 6;
				
				break;
			case 6:				
				if (sensor[i].sensor_y > 690)
					sensor[i].driection = 7;
				if(sensor[i].sensor_x < 60)
					sensor[i].driection = 5;
				
				break;
			case 7:
				
				if (sensor[i].sensor_y < 60 )
					sensor[i].driection = 6;
				if(sensor[i].sensor_x < 60)
					sensor[i].driection = 0;
				
				break;
			case 0:
				
				if (sensor[i].sensor_y <60 )
					sensor[i].driection = 5;
				if(sensor[i].sensor_x > 940)
					sensor[i].driection = 7;
				
				break;
			default:
				break;
			}	

			//不出界    移动
			switch (sensor[i].driection)
			{
			case 1:	
				sensor[i].sensor_x += sensor[i].speed;
				break;
			case 2:	
				sensor[i].sensor_y += sensor[i].speed;
				break;
			case 3:
				sensor[i].sensor_x -= sensor[i].speed;
				break;
			case 4:		
				sensor[i].sensor_y -= sensor[i].speed;
				break;
			case 5:		
				sensor[i].sensor_x += sensor[i].speed;
				sensor[i].sensor_y += sensor[i].speed;
				break;
			case 6:
				
				sensor[i].sensor_x -= sensor[i].speed;
				sensor[i].sensor_y += sensor[i].speed;
				break;
			case 7:

				
				sensor[i].sensor_x -= sensor[i].speed;
				sensor[i].sensor_y -= sensor[i].speed;
				break;
			case 0:

				
				sensor[i].sensor_x += sensor[i].speed;
				sensor[i].sensor_y -= sensor[i].speed;
				break;
			default:
				break;
			}
	    }  
		BeginBatchDraw();
		setfillcolor(WHITE);
		fillrectangle(0, 0, 1000, 800);
		setfillcolor(RGB(230, 230, 230));
		bar(0, 0, 50, 800);
		bar(950, 0, 1000, 800);
		bar(0, 0, 1000, 50);
		bar(0, 700, 1000, 800);

		setbkcolor(RGB(230, 230, 230));
		string str;
		settextcolor(BLUE);
		settextstyle(30, 0, ("黑体"));
		char buff0[13] = { "查找邻居节点" };
		str = (string)buff0;
		strcpy_s(buff0, str.c_str());
		outtextxy(150, 740, buff0);
		setlinestyle(PS_SOLID, 3, 0, 0);
		rectangle(140,730,340,780);

		settextcolor(BLUE);
		settextstyle(30, 0, ("黑体"));
	    char buff1[13] = { "模拟洪泛" };
		str = (string)buff1;
		strcpy_s(buff1, str.c_str());
		outtextxy(550, 740, buff1);       
		rectangle(540, 730, 680, 780);
		
		char buff2[5] = { "重置" };
		str = (string)buff2;
		strcpy_s(buff2, str.c_str());
		outtextxy(840, 740, buff2);
		rectangle(830, 730, 910, 780);
		//画点
		for (int i = 0; i < size; i++)
		{	
            setfillcolor(BLUE);
			fillcircle(sensor[i].sensor_x, sensor[i].sensor_y, 10);		
		} 
		EndBatchDraw();
		
		//下框的button
		bool a = MouseHit(); 
		if(a)
		{
		
			MOUSEMSG m = GetMouseMsg();
			//框体变色
			if (m.x >= 140 && m.x <= 340 && m.y >= 730 && m.y <= 780)
			{
				/*	rectangle(140, 730, 340, 780);
					rectangle(540, 730, 680, 780);*/
				//rectangle(830, 730, 910, 780);
				setcolor(GREEN);
				rectangle(140, 730, 340, 780);
				setcolor(WHITE);
			}
			if (m.x >= 540 && m.x <= 680 && m.y >= 730 && m.y <= 780)
			{
				setcolor(GREEN);
				rectangle(540, 730, 680, 780);
				setcolor(WHITE);
			}
			//重置变色
			if (m.x >= 830 && m.x <= 910 && m.y >= 730 && m.y <= 780)
			{
				setcolor(GREEN);
				rectangle(830, 730, 910, 780);
				setcolor(WHITE);
			}
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				/*	rectangle(140, 730, 340, 780);
					rectangle(540, 730, 680, 780);*/
				int sen;
				if (m.x >= 140 && m.x <= 340 && m.y >= 730 && m.y <= 780)
				{
					sen=findClick(sensor,1);
					neighbor(sensor, sen);
					break;
				}
				if (m.x >= 540 && m.x <= 680 && m.y >= 730 && m.y <= 780)
				{
					//fillcircle(m.x, m.y, 10);
					//洪泛
					sen=findClick(sensor,0);
					flood(sensor, sen);
					break;
				}
				
			}
			FlushMouseMsgBuffer();
		}
	}
	
}

int findClick(Sensor(&sensor)[size],int type)
{
	int flag = 0;
	while (1)
	{
		MOUSEMSG m = GetMouseMsg();
	
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			/*if (m.x >= 830 && m.x <= 910 && m.y >= 730 && m.y <= 780)
			{
				goto init;
			}*/
			for (int i = 0; i < size; i++)
			{
				if (m.x >= sensor[i].sensor_x - 10 && m.x <= sensor[i].sensor_x + 10 && m.y >= sensor[i].sensor_y - 10 
					&& m.y <= sensor[i].sensor_y + 10)
				{
					setfillcolor(GREEN);
					/*if (type)
					{
						sensor[i].state = 10;		
					}
					else 
					{
						sensor[i].state = 11;	
					}*/
					fillcircle(sensor[i].sensor_x, sensor[i].sensor_y, 10);
					setfillcolor(BLUE);
					return i;
					//flag = 1;
					//break;
				}
			}
			//执行了点击就算了
			/*if (flag == 1)
				break;*/
		}
	}
}

void neighbor(Sensor(&sensor) [size], int a)
{
	double distance = 0;
	for (int i = 0; i < size; i++)
	{
		distance = sqrt((sensor[a].sensor_x - sensor[i].sensor_x)*(sensor[a].sensor_x - sensor[i].sensor_x)
			+ (sensor[a].sensor_y - sensor[i].sensor_y)*(sensor[a].sensor_y - sensor[i].sensor_y));
		//邻居节点的距离定义
		if (distance <= 150)
		{
			setcolor(WHITE);
			setfillcolor(RED);
			fillcircle(sensor[i].sensor_x, sensor[i].sensor_y, 10);
			setfillcolor(BLUE);
			setcolor(BLACK);
			line(sensor[a].sensor_x, sensor[a].sensor_y, sensor[i].sensor_x, sensor[i].sensor_y);
		}
		
	}
}
struct returnData
{
	int tamp;
	double legth;
};
returnData mindis(Sensor(&sensor)[size], int a)
{
	double min = 99999;
	double current=0;
	int tamp = 0;
	for (int i = 0; i < size; i++)
	{
		if (i != a&&sensor[i].state!=1)
		{
			current = sqrt((sensor[a].sensor_x - sensor[i].sensor_x)*(sensor[a].sensor_x - sensor[i].sensor_x)
				+ (sensor[a].sensor_y - sensor[i].sensor_y)*(sensor[a].sensor_y - sensor[i].sensor_y));
			if (min > current)
			{
				min = current;
				tamp = i;
			}
		}
		
	}
	returnData data;
	data.legth = min;
	data.tamp = tamp;
	return data;
}
void flood(Sensor(&sensor)[size],int a)
{
	int index = 0;
	map<int, int>myMap;
	myMap.emplace(index, a);
	sensor[a].state = 1;
	
	while (1)
	{
		returnData onetime{ 0,99999 };
		//遍历选定块
		for (auto i = myMap.begin(); i != myMap.end(); ++i) {
			returnData d = mindis(sensor, i->second);
			if (d.legth < onetime.legth)
			{
				onetime = d;
			}
		}
		//离团队更近的
		index++;
		myMap.emplace(index, onetime.tamp);
		sensor[onetime.tamp].state = 1;

		//节点变色
		setfillcolor(RED);
		fillcircle(sensor[onetime.tamp].sensor_x, sensor[onetime.tamp].sensor_y, 10);
		setfillcolor(BLUE);

		//退出
		int flag = 0;
		for (int i = 0; i < size; i++)
		{
			if (sensor[i].state == 1)
			{
				flag++;
			}
			if (flag == size)
			{
				break;
			}
		}
		Sleep(1000);
	}
	
	
}