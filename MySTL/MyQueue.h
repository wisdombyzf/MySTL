/**
Data:2017/9/16
author:zf

感觉应该用vector做容器。。。
**/
#pragma once

const int queue_max_size = 2333;
template<class T>
class MyQueue
{
public:
	typedef unsigned size_type;
public:
	MyQueue();
	~MyQueue();

	T& front();	//返回队列头元素
	void push(const T& value);	//入队列
	void pop();		//出队列
	size_type size() { return queue_tail-queue_head; }	//返回队列的大小
	bool empty();		//队列是否为空


private:
	size_type queue_head;
	size_type queue_tail;
	T queue[queue_max_size];
};

template<class T>
MyQueue<T>::MyQueue()
{
	queue_head = 0;
	queue_tail = 0;
}

template<class T>
MyQueue<T>::~MyQueue()
{

}

template<class T>
T& MyQueue<T>::front()
{
	if (queue_head!=queue_tail)
	{
		return queue[queue_head];
	}
	else
	{

	}
}


template<class T>
void MyQueue<T>::push(const T& value)
{
	if (((queue_tail+1)%queue_max_size)!=queue_head)
	{
		queue[queue_tail] = value;
		queue_tail++;
	}
	else
	{

	}
}

template<class T>
void MyQueue<T>::pop()
{
	if (queue_head!=queue_tail)
	{
		queue_head=(queue_head++)%queue_max_size;
	}
	else
	{

	}
}

template<class T>
bool MyQueue<T>::empty()
{
	if (queue_head==queue_tail)
	{
		return true;
	}
	else
	{
		return false;
	}
}
