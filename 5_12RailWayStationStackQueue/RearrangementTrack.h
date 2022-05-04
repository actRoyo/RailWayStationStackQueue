#pragma once
#include "ArrayQueue.h"
#include<iostream>
using namespace std;
class Carriage
{
public:
	int CarriageNumber;
};
//����쳵�����뻺���
bool Hold(ArrayQueue<Carriage> QueueHold[], int CarriageQuantity, int HoldQueueQuantity,//��������飬�������������������
	//�������Ӧ�������С�����ţ����������С��������ڵ���С����ţ���ǰ�����ȵĳ�����
	int& MinHold, int& MinQueue, int& current)
{
	int BestCushion = -1;//���Ż�������ţ� Ĭ��ֵ-1��ʾδ�ҵ����Ż����
	int BestLast = -1;//�������Ż�������β�ĳ�����
	Carriage temp;
	for (int i = 0; i < HoldQueueQuantity; i++)
	{//Ѱ����ѻ������current����
		if (!QueueHold[i].Empty())
		{
			temp=QueueHold[i].GetRear();//ȡ�õ�ǰ�����i�Ķ�β������
			if (current > temp.CarriageNumber&& temp.CarriageNumber > BestLast)
			{//ѡȡ�����Ķ�β�б�����ģ���С��current�ĳ���
				BestLast = temp.CarriageNumber;
				BestCushion = i;
			}
		}
		else//����Ҳ�����ѻ���죬��������һ�������
			if (BestCushion == -1) BestCushion = i;
	}
	if (BestCushion == -1)
	{
		cout << "wrong!����첻��,����ʧ��" << endl;
		return false;
	}
	temp.CarriageNumber = current;
	QueueHold[BestCushion].EnQueue(temp);//current����ѡ����BestCushion
	cout << "�����뻺��졿����콫" << current << "�ų����Ƶ����Ż�����" << BestCushion << endl;
	if (current < MinHold)
	{
		MinHold = current;
		MinQueue = BestCushion;
	}
	return true;
}
//������쳵���������
void OutPut(ArrayQueue<Carriage>* QueueHold,
	int CarriageQuantity, int HoldQueueQuantity,
	int& MinHold, int& MinQueue)
{
	int current;
	Carriage temp;
	QueueHold[MinQueue].DeQueue();
	cout << "�����嵽���졿��" << MinQueue << "�Ż�������" << MinHold << "�ų��ᵽ����" << endl;
	MinHold = CarriageQuantity + 1;//���ʼ��СֵΪ�������
	for (int i = 0; i < HoldQueueQuantity; i++)
	{//�Ƚ����л�������еĶ�ͷ������
		temp=QueueHold[i].GetFront();
		current = temp.CarriageNumber;

		if (!QueueHold[i].Empty() && current < MinHold)
		{//��ǰ�����űȻ����������С�ĳ����Ż�С���޸�MinHold��MinQueue
			MinHold = current;
			MinQueue = i;
		}
	}
}

bool RearrangementTrack(int CarriageNumber[],//��쳵��˳��
	int CarriageQuantity,//��������
	int HoldQueueQuantity)//���������
{
	int MaxQueueSize = 20;
	Carriage result;
	ArrayQueue<Carriage>   QueueIn(MaxQueueSize);
	for (int i = 0; i < CarriageQuantity; i++)
	{//��������result��ָ�ڴ�ռ���д�ֵ����
		result.CarriageNumber = CarriageNumber[i];
		QueueIn.EnQueue(result);
	}
	ArrayQueue<Carriage> QueueOut(MaxQueueSize);
	ArrayQueue<Carriage>* QueueHold = new ArrayQueue<Carriage>[HoldQueueQuantity];
	int NowOut = 1;//��ǰӦ����ĳ�����
	int MinHold = CarriageQuantity + 1;//�������Ӧ����ĳ����ţ���ʼֵ��󻯡�
	int MinQueue = 0;//���������С�����Ŷ�Ӧ�Ļ���������
	for (int i = 1; i <= CarriageQuantity; i++)//���δ�������ϵĳ��ᣬ����ֱ���������������������뻺���
	{
		result=QueueIn.GetFront();
		QueueIn.DeQueue();
		if (result.CarriageNumber == NowOut)
		{
			cout << "����쵽���졿��������" << result.CarriageNumber << "�ų��ᵽ����" << endl;
			QueueOut.EnQueue(result);
			if (NowOut != CarriageQuantity)
				NowOut++;
			while (MinHold == NowOut)
			{
				//������������������
				result.CarriageNumber = MinHold;
				QueueOut.EnQueue(result);
				OutPut(QueueHold, CarriageQuantity, HoldQueueQuantity, MinHold, MinQueue);
				if (NowOut != CarriageQuantity)
					NowOut++;
			}
		}
		else//��result.CarriageNumber����ĳ�������
		{//�������false˵������첻�㣬����ʧ��
			if (!Hold(QueueHold, CarriageQuantity, HoldQueueQuantity,//��������飬�������������������
				//�������Ӧ�������С�����ţ����������С��������ڵ���С����ţ���ǰ�����ȵĳ�����
				MinHold, MinQueue, result.CarriageNumber))
				return false;
		}
	}
	return true;
}