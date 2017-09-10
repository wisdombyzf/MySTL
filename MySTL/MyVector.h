/***********************
Data:2017/9/10
author:zf

暂时使用c++标准的内存空间配置器
用法：和STL中的vector相似，实现了其中的小小小小部分功能
*************************/
#pragma once
#include<memory>
#include<iostream>

template<typename T,class my_allocator=std::allocator<T>>
class MyVector
{
public:
	//内嵌类型表
	typedef T	value_type;		//值的类型
	typedef T*  iterator;		//迭代器
	typedef T&	reference;		//引用
	typedef T*  pointer;		//指针
	typedef unsigned size_type;		//好像一般是用的size_t，待定

public:
	MyVector();		//无参数时的构造函数
	MyVector(size_type n);		//一个参数时的构造函数，n表示初始数组长度
	MyVector(size_type n,const T& value);		//构造一个长n值为value的vector....不能用reference代替T&。。。
	~MyVector() { my_destroy(); }		//析构函数

	void _vector_full();	//辅助函数，若容器已满，则开辟新的内存空间
	void push_back(const T& value);		//vector尾部插入值value
	void pop_back();		//删除尾部的值
	void insert(iterator position,const T& value);	//

	iterator begin() { return first; }	//返回起始值
	iterator end() { return last; }		//返回vector尾部值
	bool empty() { return begin() == end(); }		//判断是否为空，空返回true
	size_type size() { return size_type(end() - begin()); }		//返回vector大小

	reference front() { return *begin(); }		//返回vector第一个值
	reference back() { return *(end() - 1); }		//返回vector最后一个值
	reference operator[](size_type n) { return *(begin() + n); }	//重载，可通过[]访问元素

private:
	std::allocator<value_type> alloc;	//内存空间分配器
	iterator first;		//线性表的首地址
	iterator last;		//线性表已经用掉的空间
	iterator length;			//线性表总共申请的空间
private:
	void my_destroy();		//销毁vector，释放空间
};

template<typename T, class my_allocator = std::allocator<T>>
void MyVector<T, my_allocator>::insert(iterator position,const T& value)
{


}

template<typename T, class my_allocator = std::allocator<T>>
void MyVector<T, my_allocator>::_vector_full()
{
	const size_type old_length = size();
	const size_type new_length = old_length * 2 + 1;	//新空间为原来空间的2倍加1，当原空间为0时，新空间也不会为0
	iterator new_first = alloc.allocate(new_length);
	iterator new_last = new_first;

	new_last = std::uninitialized_copy(first, last, new_first);		//利用原生函数将原vector中的值拷贝到新的vector
	my_destroy();	//释放内存空间

	//调整迭代器指针
	first = new_first;
	last = new_last;
	length = first+new_length;

}

template<typename T, class my_allocator = std::allocator<T>>
void MyVector<T, my_allocator>::push_back(const T& value)
{
	if (last==length)		//空间已满时,重新开辟内存空间
	{
		_vector_full();
	}
	alloc.construct(last, value);		//调用配置器在last位置上写入value，last指针后移
	last++;
	
}

template<typename T, class my_allocator = std::allocator<T>>
void MyVector<T, my_allocator>::pop_back()
{
	last--;		//先将指针移到最后一个元素,再利用配置器函数删除
	alloc.destroy(last);
}


template<typename T, class my_allocator = std::allocator<T>>
MyVector<T, my_allocator>::MyVector()
{
	
}

template<typename T, class my_allocator = std::allocator<T>>
MyVector<T, my_allocator>::MyVector(size_type n)
{
	first = alloc.allocate(n);
	std::uninitialized_fill(first, first + n, 0);	//利用内置函数，申请n大小的数组，且初始化为0
	last = length = first + n;
}

template<typename T, class my_allocator = std::allocator<T>>
MyVector<T, my_allocator>::MyVector(size_type n, const T& value)
{
	first = alloc.allocate(n);
	std::uninitialized_fill(first, first + n, value);	//申请n大小的数组，且初始化为value
	last = length = first + n;
}

template<typename T, class my_allocator = std::allocator<T>>
void MyVector<T, my_allocator>::my_destroy()
{

}