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
	MyString(const MyString &other);	//�������캯��
	~MyString();
	
	size_t size() { return length; }	//�����ַ�����С
	
	int test(int a = 9999) { return a; }

	MyString operator+(int a);		//����+
	MyString & operator =(const MyString& old_string) ;  //����=
	//����=
	//����[]

	size_t length;		//�ַ�������
	char * data;		//�ַ���ͷָ��
private:




};

MyString::MyString()
{
	length = 0;
	data = "";	
}

MyString::MyString(const char * a=nullptr)
{
	//ע��a�Ƿ�Ϊ��
	if (a==nullptr)
	{
		length = strlen(a);
		data = new char(length + 1);		//����ֱ�� data = a;�����������Ǹ���
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
	//���old_string��this��ͬ�����
	if (this==&old_string)
	{
		return *this;
	}
	else
	{
		delete[] data;//�ͷ��ڴ档������Ӧ����deleteҲ����
		length = old_string.length;
		data = new char[length + 1];
		strcpy(data, old_string.data);
		return *this;		
	}
}



