#pragma once
#include"RBTree.h"
#include<string>
#include<iostream>

template<class T1,class T2>
class MyMap
{
public:
	//��Ƕ���ͱ�
	typedef T1 key_value;
	typedef T2 data_value;
	typedef RBTNode<T1, T2>* iterator;

public:
	MyMap();
	~MyMap();
	void insert(std::pair<key_value, data_value>my_data);		//����Ԫ��
	iterator find(key_value a);			//����һ��������ָ���ֵΪkey��Ԫ�أ����û�ҵ��ͷ���ָ��mapβ���ĵ�����
	size_t size() { return cont_size; }		//����map��С
	bool empty();						//���mapΪ���򷵻�true
	void erase(iterator a);				//������ָ��ĳԪ�صĵ�������  ɾ��һ��Ԫ��

private:
	RBTNode<T1, T2>* _create_node_(T1 key,T2 data);		//������

private:
	size_t cont_size;
	iterator root;
	RBTree<T1,T2> contain;
};

template<class T1, class T2>
MyMap<T1, T2>::MyMap()
{
	RBTree<T1, T2> contain;
	cont_size = 0;
	//root = contain.root;
}

template<class T1, class T2>
MyMap<T1, T2>::~MyMap()
{
}

template<class T1, class T2>
void MyMap<T1, T2>::insert(std::pair<key_value, data_value> my_data)
{
	iterator node_temp=_create_node_(my_data.first, my_data.second);
	contain.insert(node_temp);
	cont_size++;
}

template<class T1, class T2>
RBTNode<T1, T2>* MyMap<T1, T2>::find(key_value a)
{
	iterator temp = nullptr;
	temp = contain.find(a);
	return temp;
}

template<class T1, class T2>
bool MyMap<T1, T2>::empty()
{
	if (cont_size==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<class T1, class T2>
void MyMap<T1, T2>::erase(iterator a)
{
	contain.remove(a);
	cont_size--;
}

template<class T1, class T2>
RBTNode<T1, T2>* MyMap<T1, T2>::_create_node_(T1 key, T2 data)
{
	iterator node = new RBTNode<T1,T2>();
	node->key = key;
	node->data = data;
	return  node;
}



