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
#include<queue>
#include"MyQueue.h"
#include"MyStack.h"
#include<stack>
#include"MyVector.h"
#include<list>
#include<algorithm>
#include"MyList.h"
using namespace std;


int main()
{
	MyQueue<int>ttt;
	
	ttt.push(342);
	ttt.push(32);
	ttt.push(344242);
	cout << ttt.size() << endl;

	while (!ttt.empty())
	{
		cout << ttt.front() << endl;
		ttt.pop();
	}
	cout << ttt.size() << endl;
	int rrr;
	cin >> rrr;
	
	
	
}