/*
使用VS2015时，若出现：
*****************************************************************************
错误	C4996	'std::uninitialized_copy::_Unchecked_iterators::_Deprecate':
Call to 'std::uninitialized_copy' with parameters that may be unsafe - this
call relies on the caller to check that the passed values are correct. 
To disable this warning........
****************************************************************************
请加入预处理器(项目属性----C/C++----预处理----预处理器定义)：
_SCL_SECURE_NO_WARNINGS
*/

#include<iostream>
#include"MyVector.h"
#include<list>
#include"MyList.h"
using namespace std;


int main()
{
	MyList<int>test;
	test.push_front(88);
	test.push_front(99);
	test.insert(test.begin(), 76889);
	cout << test.front() << endl;
	test.erase(test.begin());
	cout << test.front() << endl;

	
	int rrr;
	cin >> rrr;
	
	
	
}