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
	MyString(const char* a);
	MyString(const MyString &other);	//拷贝构造函数
	~MyString();
	
	size_t size() const { return length; }	//返回字符串大小
	
	int test(int a = 9999) { return a; }

	MyString& operator+(const MyString & other_string);		//重载+
	MyString& operator =(const MyString& other_string) ;  //重载=
	bool operator ==(const MyString & other_string)const; ;    //重载=
	char& operator[](int n);    //重载[]
	//friend istream& operator>>(istream & is,MyString & str ); //利用友元重载>>
	//friend ostream& operator<<(ostream& os, MyString& str);	//利用友元重载<<

	//之后应放入private
	size_t length;		//字符串长度,
	char * data;		//字符串头指针
private:




};

MyString::MyString()
{
	length = 0;
	data = "";	
}

MyString::MyString(const char * a)
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
	//delete data;
	//length = 0;   
}

inline MyString& MyString::operator+(const MyString & other_string)
{
	MyString new_string;
	new_string.length = length + other_string.length;
	new_string.data = new char[new_string.length + 1];
	strcpy(new_string.data, data);
	strcat(new_string.data, other_string.data);
	delete[] data;
	return new_string;
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
		//delete data;//释放内存。。。。应该用delete也可以
		length = old_string.length;
		data = new char[length + 1];
		strcpy(data, old_string.data);
		return *this;		
	}
}

inline bool MyString::operator==(const MyString & other_string) const
{
	if (length!=other_string.size())
	{
		return false;
	}
	else
	{
		return  strcmp(data, other_string.data) ? false : true;
	}
}

inline char & MyString::operator[](int n)
{
	if (n>=length)
	{
		return data[length - 1];	//当n过大时，返回字符串的最后一个字符
	}
	else
	{
		return data[n];
	}
}


/*
istream& operator >> (istream &is, MyString &str) 
{
	//申请一块足够大的内存。。。。或循环输入？？
	char temp[10086];
	is >> temp;
	str.length = strlen(temp);
	str.data = new char[str.length + 1];
	strcpy(str.data, temp);
	delete temp;
	return is;
}

ostream & operator<<(ostream & os, MyString & str)
{
	os << str.data;
	return os;
}
*/