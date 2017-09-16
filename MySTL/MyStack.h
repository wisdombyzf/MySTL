/**
Data:2017/9/16
author:zf

�о�Ӧ����vector������������
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

	T& top();	//����ջ��Ԫ��
	void push(const T& value);	//��ջ
	void pop();		//��ջ
	size_type size() { return stack_size; }	//����ջ�Ĵ�С
	bool empty();		//ջ�Ƿ�Ϊ��


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
