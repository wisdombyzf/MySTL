/***********************
Data:2017/9/12
author:zf
�����������,�о�д����,����new�����ڴ�ռ��������������
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
	//��Ƕ���ͱ�
	typedef List_Node<T>*	iterator;	//������
	typedef List_Node<T>	value_type;		//ֵ������
	typedef List_Node<T>&	reference;		//����
	//typedef T*  pointer;		//ָ��
	typedef unsigned size_type;		//����һ�����õ�size_t������

	/*
	typedef MyList<T, Ref, Ptr>  self;
	typedef MyList<T, T&, T*>  iterator;
	reference operator*(){ return  }
	*/


public:
	MyList();	//�޲���������
	MyList( size_type n);	//����һ����Ϊn������
	~MyList();

	iterator create_node() { return new List_Node<T>; }		//����һ�����
	void push_back(const T& value);	//����β�����value
	void pop_back();		//��������β�����һ����
	size_type size() { return length; }		//����������
	bool empty() { return head == tail; }		//�Ƿ�Ϊ��

	iterator operator ++(){return }		//����++�����

private:
	iterator head;
	iterator tail;	
	size_type length;	//������

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
		tail->next_pointer->pre_pointer = tail;		//���½�Ԫ�ص�ǰָ��ָ��ǰһ��Ԫ�صĵ�ַ
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



