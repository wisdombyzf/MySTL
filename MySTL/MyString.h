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
	size_t find(const char* other_string, size_t pos = 0);	//从字符串的pos位置开始，查找子字符串other_string。如果找到，则返回该子字符串首次出现时其首字符的索引；否则，返回-1;
	int test(int a = 9999) { return a; }

	MyString& operator+(const MyString & other_string);		//重载+
	MyString& operator =(const MyString& other_string) ;  //重载=
	bool operator ==(const MyString & other_string)const; ;    //重载=
	char& operator[](int n);    //重载[]

	////////重载<<  >>不对....待定
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
	if (a!=nullptr)
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

inline size_t MyString::find(const char * other_string, size_t pos)
{
	//若子串为空或不存在时
	if (other_string==""||other_string==nullptr)
	{
		return -1;
	}
	int other_string_length = strlen(other_string);
	int* next=new int[other_string_length];
	/*
	构建next数组
	其实用前后缀的方式更容易理解next数组
	1.先找出最长的相等前后缀x
	2.若str[x]==str[当前字符],则next[当前字符]=next[x]
	3.感觉有点像并查集
	*/
	next[0] = -1;
	int j = -1;
	/*
	for (size_t i = 0; i < other_string_length; i++)
	{
		if (j==-1|| other_string[i] == other_string[j+1])
		{
			//当相等前后缀+1时
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
			j = next[j];		//回溯
		}
	}
	/*
	//输出next数组
	for (size_t i = 0; i < other_string_length; i++)
	{
		std::cout << next[i] << std::endl;
	}
	*/

	for (size_t i = 0,k=0; i < length;)
	{
		//当子串匹配到最后一个字符。。。即匹配成功时，返回子串首次出现的首字符的位置
		if (k== other_string_length)
		{
			return i - other_string_length;
		}
		//当比较字符相等时，则比较下一个字符
		if (data[i]==other_string[k])
		{
			k++;
			i++;
		}
		else
		{
			//当k==-1时，被匹配串向右滑动一位
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