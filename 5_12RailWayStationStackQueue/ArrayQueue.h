#pragma once

using namespace std;
#include<iostream>
#include<assert.h>
template<typename T>
class ArrayQueue 
{
public:
	ArrayQueue(int initialCapacity = 10);
	~ArrayQueue() { delete[] pItems; }
	bool Empty() const { return frontIndex == backIndex; }
	int Size() const
	{
		return (backIndex - frontIndex + arrayLength) % arrayLength;
	}
	T& GetFront()
	{

		return pItems[(frontIndex + 1) % arrayLength];
	}
	T& GetRear()
	{
		assert(frontIndex != backIndex);
		return pItems[backIndex];
	}
	void DeQueue()
	{
		assert (frontIndex != backIndex);
		frontIndex = (frontIndex + 1) % arrayLength;
		pItems[frontIndex].~T(); 
	}
	void EnQueue(const T& element);
private:
	int frontIndex;      
	int backIndex;       
	int arrayLength;    
	T* pItems;           
};

template<typename T>
ArrayQueue<T>::ArrayQueue(int initialCapacity)
{
	assert(initialCapacity>= 1);
	arrayLength = initialCapacity;
	pItems = new T[arrayLength+1];
	frontIndex = 0;
	backIndex = 0;
}

template<typename T>
void ArrayQueue<T>::EnQueue(const T& element)
{   //如果队满则需要扩充队列空间
	if ((backIndex + 1) % arrayLength == frontIndex)
	{// 先申请一个长度加倍的空间
		T* newQueue = new T[2 * arrayLength];
		// 将元素复制到新的空间中
		int start = (frontIndex + 1) % arrayLength;
		if (start < 2)
			// 没有循环的情况出现
			copy(pItems + start, pItems + start + arrayLength - 1, newQueue);
		else
		{  // 有循环的情况出现
			copy(pItems + start, pItems + arrayLength, newQueue);
			copy(pItems, pItems + backIndex + 1, newQueue + arrayLength - start);
		}

		// 将空间指针指向新的空间
		frontIndex = 2 * arrayLength - 1;
		backIndex = arrayLength - 2;   // 
		arrayLength *= 2;
		pItems = newQueue;
	}

	// 将元素入队
	backIndex = (backIndex + 1) % arrayLength;
	pItems[backIndex] = element;
}