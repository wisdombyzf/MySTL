/***********************
Data:2017/9/12
author:zf
�����������,�о�д����
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
	//��Ƕ���ͱ�
	typedef List_Node<T>* iterator;	//������
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

	iterator create_node();		//����һ�����
	void push_back(const T& value);	//����β�����value
	void pop_back();		//��������β�����һ����
	size_type size() { return length; }		//����������
	bool empty() { return head == tail; }		//�Ƿ�Ϊ��

private:
	iterator head;
	iterator tail;

	size_type length;	//������

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



