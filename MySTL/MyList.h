/***********************
Data:2017/9/12
author:zf
д���ˡ��������Ժ���˵
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

public:
	MyList();	//�޲���������
	MyList( size_type n);	//����һ����Ϊn������
	~MyList();


	/*
	����������
	iterator operator++ () { return tail->next_pointer; }		//����++�����

	
	*/

	iterator create_node() { return new List_Node<T>; }		//����һ�����
	iterator begin() { return head->next_pointer; }	//����ͷ����ַ
	iterator end() { return tail; }		//����β����ַ
	T front() { return begin()->data; }	//����ͷ���ֵ
	T back() { return end()->data; }	//����β���ֵ

	void insert(iterator position, const T& value);	//��poistionǰ����value
	void erase(iterator position);		//ɾ��position����Ԫ��
	void push_back(const T& value);	//����β�����value
	void pop_back();		//��������β�����һ����
	void push_front(const T& value);	//����ͷ���value
	void pop_front();		//��������ͷ
	size_type size() { return length; }		//����������
	bool empty();		//�Ƿ�Ϊ��

	void test();
	

private:
	iterator head;
	iterator tail;	
	size_type length;	//������

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



