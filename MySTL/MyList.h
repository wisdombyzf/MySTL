/***********************
Data:2017/9/12
author:zf
迭代器待完成,感觉写错了,先用new代替内存空间分配器。。。。
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

struct header
{


};

template<class T>
class MyList
{
public:
	//内嵌类型表
	typedef List_Node<T>*	iterator;	//迭代器
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

	iterator create_node() { return new List_Node<T>; }		//构造一个结点
	void push_back(const T& value);	//链表尾部添加value
	void pop_back();		//弹出链表尾部最后一个数
	size_type size() { return length; }		//返回链表长度
	bool empty() { return head == tail; }		//是否为空

	iterator operator ++(){return }		//重载++运算符

private:
	iterator head;
	iterator tail;	
	size_type length;	//链表长度

};


template<class T>
MyList<T>::MyList()
{
	head = tail = create_node();
	head->next_pointer = NULL;
	head->pre_pointer = NULL;
	length = 0;
}

template<class T>
MyList<T>::MyList(size_type n)
{
	head = tail = create_node();
	head->next_pointer = NULL;
	head->pre_pointer = NULL;
	length = 0;
	for (size_type i = 1; i < n; i++)
	{
		tail->next_pointer = create_node();
		tail->next_pointer->pre_pointer = tail;		//将新建元素的前指针指向前一个元素的地址
		tail = tail->next_pointer;
		//tail->data = NULL;
		length++;
	}
	tail->next_pointer = NULL;
}

template<class T>
MyList<T>::~MyList()
{


}

template<class T>
void MyList<T>::push_back(const T& value)
{
	tail->next_pointer = create_node();
	tail->next_pointer->pre_pointer = tail;		
	tail = tail->next_pointer;

	tail->data = value;
	length++;
};

template<class T>
void MyList<T>::pop_back()
{
	iterator temp;
	temp = tail;
	tail = tail->pre_pointer;
	delete temp;



};



