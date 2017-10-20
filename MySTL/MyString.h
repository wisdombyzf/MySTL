/*
data:2017/10/18
author:zf
*/
#pragma once
#include<iostream>
class MyString
{
public:
	MyString();
	MyString(const char* a=nullptr);
	MyString(const MyString &other);	//拷贝构造函数
	~MyString();
	
	size_t size() { return length; }	//返回字符串大小
	
	int test(int a = 9999) { return a; }

	MyString operator+(int a);		//重载+
	MyString & operator =(const MyString& old_string) ;  //重载=
	//重载=
	//重载[]

	size_t length;		//字符串长度
	char * data;		//字符串头指针
private:




};

MyString::MyString()
{
	length = 0;
	data = "";	
}

MyString::MyString(const char * a=nullptr)
{
	//注意a是否为空
	if (a==nullptr)
	{
		length = strlen(a);
		data = new char(length + 1);		//不能直接 data = a;。。。。。是个坑
		strcpy(data, a);
	}
	else
	{
		char* temp = data;
		length = 0;
		data = new char(length + 1);
		data = "\0";
		delete temp;
	}
	
}
inline MyString::MyString(const MyString & other)
{
	length = other.length;
	data = new char[length+1];
	strcpy(data, other.data);
}
MyString::~MyString()
{
	delete data;
}

MyString & MyString::operator=(const MyString & old_string)
{
	//检查old_string与this相同的情况
	if (this==&old_string)
	{
		return *this;
	}
	else
	{
		delete[] data;//释放内存。。。。应该用delete也可以
		length = old_string.length;
		data = new char[length + 1];
		strcpy(data, old_string.data);
		return *this;		
	}
}



