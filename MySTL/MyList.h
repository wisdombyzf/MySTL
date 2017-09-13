/***********************
Data:2017/9/12
author:zf
迭代器待完成,感觉写错了
*************************/
#pragma once
#include<memory>
#include<iostream>

template<class T>
struct List_Node
{
	T data;	
	List_Node* next_pointer;
	List_Node* pre_pointer;
};

template<class T>
class MyList
{
public:
	//内嵌类型表
	typedef List_Node<T>* iterator;	//迭代器
	typedef List_Node<T>	value_type;		//值的类型
	typedef List_Node<T>&	reference;		//引用
	//typedef T*  pointer;		//指针
	typedef unsigned size_type;		//好像一般是用的size_t，待定

	/*
	typedef MyList<T, Ref, Ptr>  self;
	typedef MyList<T, T&, T*>  iterator;
	reference operator*(){ return  }
	*/


public:
	MyList();	//无参数，构造
	MyList( size_type n);	//构造一个长为n的链表
	~MyList();

	iterator create_node();		//构造一个结点
	void push_back(const T& value);	//链表尾部添加value
	void pop_back();		//弹出链表尾部最后一个数
	size_type size() { return length; }		//返回链表长度
	bool empty() { return head == tail; }		//是否为空

private:
	iterator head;
	iterator tail;

	size_type length;	//链表长度

};

template<typename T>
MyList<T>::Mylist(size_type n)
{



};

template<typename T>
MyList<T>::Mylist()
{




};

template<typename T>
void MyList<T>::push_back(const T& value)
{
	




};

template<typename T>
void MyList<T>::pop_back()
{




};



