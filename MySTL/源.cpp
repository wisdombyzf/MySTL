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
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include"RBTree.h"
#include<queue>
#include"MyQueue.h"
#include"MyStack.h"
#include<stack>
#include"MyVector.h"
#include<list>
#include<algorithm>
#include"MyList.h"
#include<map>
#include"MyMap.h"
#include"MyString.h"

//#include"test.h"
using namespace std;


int main()
{
	MyString t;
	cout<<t.test(66666);
	system("pause");
}