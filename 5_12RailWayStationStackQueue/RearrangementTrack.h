#pragma once
#include "ArrayQueue.h"
#include<iostream>
using namespace std;
class Carriage
{
public:
	int CarriageNumber;
};
//将入轨车辆送入缓冲轨
bool Hold(ArrayQueue<Carriage> QueueHold[], int CarriageQuantity, int HoldQueueQuantity,//缓冲轨数组，车厢数量，缓冲轨数量
	//缓冲轨上应输出的最小车厢编号，缓冲轨上最小车厢号所在的最小轨道号，当前待调度的车厢编号
	int& MinHold, int& MinQueue, int& current)
{
	int BestCushion = -1;//最优缓冲轨道编号， 默认值-1表示未找到最优缓冲轨
	int BestLast = -1;//保存最优缓冲轨道队尾的车厢编号
	Carriage temp;
	for (int i = 0; i < HoldQueueQuantity; i++)
	{//寻找最佳缓冲轨存放current车厢
		if (!QueueHold[i].Empty())
		{
			temp=QueueHold[i].GetRear();//取得当前缓冲轨i的队尾车厢编号
			if (current > temp.CarriageNumber&& temp.CarriageNumber > BestLast)
			{//选取缓冲轨的队尾中编号最大的，且小于current的车厢
				BestLast = temp.CarriageNumber;
				BestCushion = i;
			}
		}
		else//如果找不到最佳缓冲轨，则新启用一条缓冲轨
			if (BestCushion == -1) BestCushion = i;
	}
	if (BestCushion == -1)
	{
		cout << "wrong!缓冲轨不足,调度失败" << endl;
		return false;
	}
	temp.CarriageNumber = current;
	QueueHold[BestCushion].EnQueue(temp);//current进入选出的BestCushion
	cout << "【进入缓冲轨】从入轨将" << current << "号车厢移到最优缓冲轨道" << BestCushion << endl;
	if (current < MinHold)
	{
		MinHold = current;
		MinQueue = BestCushion;
	}
	return true;
}
//将缓冲轨车辆放入出轨
void OutPut(ArrayQueue<Carriage>* QueueHold,
	int CarriageQuantity, int HoldQueueQuantity,
	int& MinHold, int& MinQueue)
{
	int current;
	Carriage temp;
	QueueHold[MinQueue].DeQueue();
	cout << "【缓冲到出轨】从" << MinQueue << "号缓冲轨输出" << MinHold << "号车厢到出轨" << endl;
	MinHold = CarriageQuantity + 1;//设初始最小值为最大车厢编号
	for (int i = 0; i < HoldQueueQuantity; i++)
	{//比较所有缓冲队列中的队头车厢编号
		temp=QueueHold[i].GetFront();
		current = temp.CarriageNumber;

		if (!QueueHold[i].Empty() && current < MinHold)
		{//当前车厢编号比缓冲队列中最小的车厢编号还小，修改MinHold和MinQueue
			MinHold = current;
			MinQueue = i;
		}
	}
}

bool RearrangementTrack(int CarriageNumber[],//入轨车厢顺序
	int CarriageQuantity,//车厢数量
	int HoldQueueQuantity)//缓冲轨数量
{
	int MaxQueueSize = 20;
	Carriage result;
	ArrayQueue<Carriage>   QueueIn(MaxQueueSize);
	for (int i = 0; i < CarriageQuantity; i++)
	{//反复利用result所指内存空间进行传值调用
		result.CarriageNumber = CarriageNumber[i];
		QueueIn.EnQueue(result);
	}
	ArrayQueue<Carriage> QueueOut(MaxQueueSize);
	ArrayQueue<Carriage>* QueueHold = new ArrayQueue<Carriage>[HoldQueueQuantity];
	int NowOut = 1;//当前应输出的车厢编号
	int MinHold = CarriageQuantity + 1;//缓冲轨中应输出的车厢编号，初始值最大化。
	int MinQueue = 0;//缓冲轨上最小车厢编号对应的缓冲铁轨编号
	for (int i = 1; i <= CarriageQuantity; i++)//依次处理入轨上的车厢，或者直接送入输出轨道，或者送入缓冲轨
	{
		result=QueueIn.GetFront();
		QueueIn.DeQueue();
		if (result.CarriageNumber == NowOut)
		{
			cout << "【入轨到出轨】从入轨输出" << result.CarriageNumber << "号车厢到出轨" << endl;
			QueueOut.EnQueue(result);
			if (NowOut != CarriageQuantity)
				NowOut++;
			while (MinHold == NowOut)
			{
				//将铁轨输出到出轨队列
				result.CarriageNumber = MinHold;
				QueueOut.EnQueue(result);
				OutPut(QueueHold, CarriageQuantity, HoldQueueQuantity, MinHold, MinQueue);
				if (NowOut != CarriageQuantity)
					NowOut++;
			}
		}
		else//将result.CarriageNumber送入某个缓冲轨
		{//如果返回false说明缓冲轨不足，调度失败
			if (!Hold(QueueHold, CarriageQuantity, HoldQueueQuantity,//缓冲轨数组，车厢数量，缓冲轨数量
				//缓冲轨上应输出的最小车厢编号，缓冲轨上最小车厢号所在的最小轨道号，当前待调度的车厢编号
				MinHold, MinQueue, result.CarriageNumber))
				return false;
		}
	}
	return true;
}