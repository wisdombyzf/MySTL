/***********************
Data:2017/9/12
author:zf
写崩了。。。。以后在说
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

public:
	MyList();	//无参数，构造
	MyList( size_type n);	//构造一个长为n的链表
	~MyList();


	/*
	迭代器部分
	iterator operator++ () { return tail->next_pointer; }		//重载++运算符

	
	*/

	iterator create_node() { return new List_Node<T>; }		//构造一个结点
	iterator begin() { return head->next_pointer; }	//返回头结点地址
	iterator end() { return tail; }		//返回尾结点地址
	T front() { return begin()->data; }	//返回头结点值
	T back() { return end()->data; }	//返回尾结点值

	void insert(iterator position, const T& value);	//在poistion前插入value
	void erase(iterator position);		//删除position处的元素
	void push_back(const T& value);	//链表尾部添加value
	void pop_back();		//弹出链表尾部最后一个数
	void push_front(const T& value);	//链表头添加value
	void pop_front();		//弹出链表头
	size_type size() { return length; }		//返回链表长度
	bool empty();		//是否为空

	void test();
	

private:
	iterator head;
	iterator tail;	
	size_type length;	//链表长度

};

template<class T>
void MyList<T>::test()
{
	
}

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
void MyList<T>::insert(iterator position, const T & value)
{
	iterator temp = create_node();
	iterator pre_position = position->pre_pointer;
	iterator next_position = position->next_pointer;
	temp->data = value;
	temp->next_pointer = next_position;
	temp->pre_pointer = pre_position;
	pre_position->next_pointer = temp;
	next_position->pre_pointer = temp;
	length++;
}

template<class T>
void MyList<T>::erase(iterator position)
{
	iterator pre_position = position->pre_pointer;
	iterator next_position = position->next_pointer;
	
	pre_position->next_pointer = next_position;
	next_position->pre_pointer = pre_position;
	delete position;
	length--;
}

template<class T>
void MyList<T>::push_back(const T& value)
{
	tail->next_pointer = create_node();
	tail->next_pointer->pre_pointer = tail;		
	tail = tail->next_pointer;

	tail->data = value;
	length++;
}

template<class T>
void MyList<T>::pop_back()
{
	iterator temp;
	temp = tail;
	tail = tail->pre_pointer;
	delete temp;
}

template<class T>
void MyList<T>::push_front(const T & value)
{
	if (length==0)
	{
		iterator tmp = create_node();
		tail = tmp;
		tmp->data = value;
		head->next_pointer = tmp;
		tmp->pre_pointer = head;
	}
	else
	{
		iterator temp = head->next_pointer;
		iterator temp2 = create_node();
		temp2->data = value;
		head->next_pointer = temp2;
		temp2->pre_pointer = head;
		temp2->next_pointer = temp;
		temp->pre_pointer = temp2;
	}
	length++;
}

template<class T>
void MyList<T>::pop_front()
{
	if (length==0)
	{
		
	}
	else
	{
		iterator temp = head->next_pointer;
		iterator temp2 = temp->next_pointer;
		head->next_pointer = temp2;
		temp2->pre_pointer = head;
		delete temp;
		length--;
	}
	
}

template<class T>
bool MyList<T>::empty()
{
	if (length==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}



