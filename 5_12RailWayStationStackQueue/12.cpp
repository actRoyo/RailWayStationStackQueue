
#include <iostream>
using namespace std;
#include "RearrangementTrack.h"
int main()
{
	cout << "欢迎来到测试站调度系统" << endl;
	int maxCar = 1;
	cout << "请输入车辆数量" << endl;
	cin >> maxCar;
	cout << " " << endl;
	cout << "请输入车辆编号" << endl;
	int carriageNumber[100];
	for (int i = -1; i < maxCar - 1; i++)
	{
		cin >> carriageNumber[i+1];
	}

	int maxQueue = 1;
	cout << "请输入缓冲轨数量" << endl;
	cin >> maxQueue;

	if (RearrangementTrack(carriageNumber, maxCar, maxQueue))
	{
		cout << "车辆已经出轨完毕";
	}
	else
	{
		cout << "缓冲轨不足，无法重排";
	}

	return 0;
}
/*
#include<iostream>
#include"StackDispatcher.h"
using namespace std;
int main()
{
	int carNumbers = 1;
	cout << "欢迎来到测试站调度系统" << endl;
	cout << "请输入车辆数量" << endl;
	cin >> carNumbers;
	cout << "请依次输入车辆编号" << endl;
	int pCars[100];
	for (int i = -1; i < carNumbers - 1; i++)
	{
		cin >> pCars[i + 1];
	}

	cout << "请输入缓冲轨数量" << endl;
	int holdTrackNumbers = 1;
	cin >> holdTrackNumbers;
	*/