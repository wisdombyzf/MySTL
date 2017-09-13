/***********************
Data:2017/9/10
author:zf

��ʱʹ��c++��׼���ڴ�ռ�������
�÷�����STL�е�vector���ƣ�ʵ�������е�СССС���ֹ���
*************************/
#pragma once
#include<memory>
#include<iostream>

template<typename T,class my_allocator=std::allocator<T>>
class MyVector
{
public:
	//��Ƕ���ͱ�
	typedef T	value_type;		//ֵ������
	typedef T*  iterator;		//������
	typedef T&	reference;		//����
	typedef T*  pointer;		//ָ��
	typedef unsigned size_type;		//����һ�����õ�size_t������

public:
	MyVector() :first(0), last(0), length(0) {};		//�޲���ʱ�Ĺ��캯��,��ʼ���б�
	MyVector(size_type n);		//һ������ʱ�Ĺ��캯����n��ʾ��ʼ���鳤��
	MyVector(size_type n,const T& value);		//����һ����nֵΪvalue��vector....������reference����T&������
	~MyVector() { my_destroy(); }		//��������

	void _vector_full();	//�����������������������򿪱��µ��ڴ�ռ�
	void push_back(const T& value);		//vectorβ������ֵvalue
	void pop_back();		//ɾ��β����ֵ
	void insert(iterator position,const T& value);	//��ָ��positionǰ����ֵvalue
	void erase(iterator position);	//ɾ��positionλ�õ�Ԫ��
	void erase(iterator first_position, iterator last_position);	//ɾ����first��last��Ԫ��
	void clear() { last = first; };	//ɾ������Ԫ��

	iterator begin() { return first; }	//������ʼ��ַ
	iterator end() { return last; }		//����vectorβ����ַ�ĺ�һλ
	size_type size() { return size_type(end() - begin()); }		//����vector��С
	size_type max_size() { return size_type(length - first); }	//�������������ɵ����Ԫ������
	reference front() { return *begin(); }		//����vector��һ��ֵ
	reference back() { return *(end() - 1); }		//����vector���һ��ֵ
	reference operator[](size_type n) { return *(begin() + n); }	//���أ���ͨ��[]����Ԫ��
	bool empty() { return begin() == end(); }		//�ж��Ƿ�Ϊ�գ��շ���true

private:
	std::allocator<value_type> alloc;	//�ڴ�ռ������
	iterator first;		//���Ա���׵�ַ
	iterator last;		//���Ա��Ѿ��õ��Ŀռ�
	iterator length;			//���Ա��ܹ�����Ŀռ�
private:
	void my_destroy();		//����vector���ͷſռ�
};



template<typename T, class my_allocator = std::allocator<T>>
void MyVector<T, my_allocator>::erase(iterator position)
{
	iterator temp = position;
	while (temp != last)
	{
		*temp = *(temp + 1);
		temp++;
	}
	last--;
}

template<typename T, class my_allocator = std::allocator<T>>
void MyVector<T, my_allocator>::erase(iterator first_position, iterator last_position)
{
	size_type n = last_position - first_position ;
	iterator temp = first_position;
	while (temp!=last)
	{
		*temp = *(temp + n);
		temp++;
	}
	last -= n;
}

template<typename T, class my_allocator = std::allocator<T>>
void MyVector<T, my_allocator>::insert(iterator position,const T& value)
{
	
	size_type logic_position = position - first;	//ע�⣬�����������ַ,��Ϊ����ʱ�������ַ��ı䣬�˴�Ӧ���߼���ַ�������ε�bug
	if (length==last)	//������������������
	{
		_vector_full();
	}

	iterator temp=last;
	do
	{
		*temp = *(temp - 1);
		temp--;
	} while (temp != (first + logic_position - 1));		//����λ�ú��Ԫ�ض������һλ
	*(first+ logic_position)= value;
	last++;
}

template<typename T, class my_allocator = std::allocator<T>>
void MyVector<T, my_allocator>::_vector_full()
{
	const size_type old_length = size();
	const size_type new_length = old_length * 2 + 1;	//�¿ռ�Ϊԭ���ռ��2����1����˵�ԭ�ռ�Ϊ0ʱ���¿ռ�Ҳ����Ϊ0
	iterator new_first = alloc.allocate(new_length);
	iterator new_last = new_first;

	new_last = std::uninitialized_copy(first, last, new_first);		//����ԭ��������ԭvector�е�ֵ�������µ�vector
	my_destroy();	//�ͷ��ڴ�ռ�

	//����������ָ��
	first = new_first;
	last = new_last;
	length = first+new_length;
}

template<typename T, class my_allocator = std::allocator<T>>
void MyVector<T, my_allocator>::push_back(const T& value)
{
	if (last==length)		//�ռ�����ʱ,���¿����ڴ�ռ�
	{
		_vector_full();
	}
	alloc.construct(last, value);		//������������lastλ����д��value��lastָ�����
	last++;
	
}

template<typename T, class my_allocator = std::allocator<T>>
void MyVector<T, my_allocator>::pop_back()
{
	last--;		//�Ƚ�ָ���Ƶ����һ��Ԫ��,����������������ɾ��
	alloc.destroy(last);
}

template<typename T, class my_allocator = std::allocator<T>>
MyVector<T, my_allocator>::MyVector(size_type n)
{
	first = alloc.allocate(n);
	std::uninitialized_fill(first, first + n, 0);	//�������ú���������n��С�����飬�ҳ�ʼ��Ϊ0
	last = length = first + n;
}

template<typename T, class my_allocator = std::allocator<T>>
MyVector<T, my_allocator>::MyVector(size_type n, const T& value)
{
	first = alloc.allocate(n);
	std::uninitialized_fill(first, first + n, value);	//����n��С�����飬�ҳ�ʼ��Ϊvalue
	last = length = first + n;
}

template<typename T, class my_allocator = std::allocator<T>>
void MyVector<T, my_allocator>::my_destroy()
{
	if (first)	//���������ǿ�
	{
		iterator temp = last;
		do
		{
			temp--;
			alloc.destroy(temp);	//������
		} while (temp!=first);
		alloc.deallocate(first, (last - first));	//���ͷ��ڴ�
		first = last = length = NULL;
	}
}