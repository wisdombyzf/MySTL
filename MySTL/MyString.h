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
	MyString(const MyString &other);	//�������캯��
	~MyString();
	
	
	size_t size() const { return length; }	//�����ַ�����С
	size_t find(const char* other_string, size_t pos = 0);	//���ַ�����posλ�ÿ�ʼ���������ַ���other_string������ҵ����򷵻ظ����ַ����״γ���ʱ�����ַ������������򣬷���-1;
	int test(int a = 9999) { return a; }

	MyString& operator+(const MyString & other_string);		//����+
	MyString& operator =(const MyString& other_string) ;  //����=
	bool operator ==(const MyString & other_string)const; ;    //����=
	char& operator[](int n);    //����[]

	////////����<<  >>����....����
	//friend istream& operator>>(istream & is,MyString & str ); //������Ԫ����>>
	//friend ostream& operator<<(ostream& os, MyString& str);	//������Ԫ����<<

	//֮��Ӧ����private
	size_t length;		//�ַ�������,
	char * data;		//�ַ���ͷָ��
private:




};

MyString::MyString()
{
	length = 0;
	data = "";	
}

MyString::MyString(const char * a)
{
	//ע��a�Ƿ�Ϊ��
	if (a!=nullptr)
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

inline size_t MyString::find(const char * other_string, size_t pos)
{
	//���Ӵ�Ϊ�ջ򲻴���ʱ
	if (other_string==""||other_string==nullptr)
	{
		return -1;
	}
	int other_string_length = strlen(other_string);
	int* next=new int[other_string_length];
	/*
	����next����
	��ʵ��ǰ��׺�ķ�ʽ���������next����
	1.���ҳ�������ǰ��׺x
	2.��str[x]==str[��ǰ�ַ�],��next[��ǰ�ַ�]=next[x]
	3.�о��е��񲢲鼯
	*/
	next[0] = -1;
	int j = -1;
	/*
	for (size_t i = 0; i < other_string_length; i++)
	{
		if (j==-1|| other_string[i] == other_string[j+1])
		{
			//�����ǰ��׺+1ʱ
			if (other_string[i] == other_string[j + 1])
			{
				j++;
				next[i] = next[j];
			}
			else
			{
				//
				next[i] = j;
			}
		}
		else
		{
			j = next[j];
		}

	}
	*/

	for (int i = 0; i <other_string_length;)
	{
		if (j == -1 || other_string[i] == other_string[j])
		{
			++i;
			++j;
			if (other_string[i] != other_string[j])		
			{
				next[i] = j;
			}
			else
			{
				next[i] = next[j];
			}
		}
		else
		{
			j = next[j];		//����
		}
	}
	/*
	//���next����
	for (size_t i = 0; i < other_string_length; i++)
	{
		std::cout << next[i] << std::endl;
	}
	*/

	for (size_t i = 0,k=0; i < length;)
	{
		//���Ӵ�ƥ�䵽���һ���ַ���������ƥ��ɹ�ʱ�������Ӵ��״γ��ֵ����ַ���λ��
		if (k== other_string_length)
		{
			return i - other_string_length;
		}
		//���Ƚ��ַ����ʱ����Ƚ���һ���ַ�
		if (data[i]==other_string[k])
		{
			k++;
			i++;
		}
		else
		{
			//��k==-1ʱ����ƥ�䴮���һ���һλ
			if (k==-1)
			{
				k++;
				i++;
			}
			k = next[k];
		}
	}
	return -1;
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
	//���old_string��this��ͬ�����
	if (this==&old_string)
	{
		return *this;
	}
	else
	{
		//delete data;//�ͷ��ڴ档������Ӧ����deleteҲ����
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
		return data[length - 1];	//��n����ʱ�������ַ��������һ���ַ�
	}
	else
	{
		return data[n];
	}
}


/*
istream& operator >> (istream &is, MyString &str) 
{
	//����һ���㹻����ڴ档��������ѭ�����룿��
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