/**
Data:2017/9/16
author:zf

感觉应该用vector做容器。。。
**/
#pragma once

const int stack_max_size = 2333;
template<class T>
class MyStack
{
public:
	typedef unsigned size_type;		


public:

	MyStack();
	~MyStack();

	T& top();	//返回栈顶元素
	void push(const T& value);	//入栈
	void pop();		//出栈
	size_type size() { return stack_size; }	//返回栈的大小
	bool empty();		//栈是否为空


private:
	size_type stack_size;
	T stack[stack_max_size];
};

template<class T>
MyStack<T>::MyStack()
{
	stack_size = 0;
}

template<class T>
MyStack<T>::~MyStack()
{

}

template<class T>
 T& MyStack<T>::top()
{
	 if (stack_size !=0)
	 {
		 return stack[stack_size];
	 }
	 else
	 {
		 
	 }
}

 template<class T>
void MyStack<T>::push(const T& value)
 {
	if (stack_size<stack_max_size)
	{
		stack[stack_size + 1] = value;
		stack_size++;
	}
	else
	{

	}
 }

template<class T>
void MyStack<T>::pop()
{
	if (stack_size>0)
	{
		stack_size--;
	}
	else
	{

	}
}

template<class T>
bool MyStack<T>::empty()
{
	if (stack_size==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
