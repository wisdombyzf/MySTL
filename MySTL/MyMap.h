#pragma once
#include"RBTree.h"
#include<string>
#include<iostream>

template<class T1,class T2>
class MyMap
{
public:
	//内嵌类型表
	typedef T1 key_value;
	typedef T2 data_value;
	typedef RBTNode<T1, T2>* iterator;

public:
	MyMap();
	~MyMap();
	void insert(std::pair<key_value, data_value>my_data);		//插入元素
	iterator find(key_value a);			//返回一个迭代器指向键值为key的元素，如果没找到就返回指向map尾部的迭代器
	size_t size() { return cont_size; }		//返回map大小
	bool empty();						//如果map为空则返回true
	void erase(iterator a);				//参数：指向某元素的迭代器。  删除一个元素

private:
	RBTNode<T1, T2>* _create_node_(T1 key,T2 data);		//构造结点

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



