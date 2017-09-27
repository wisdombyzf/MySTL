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

//#include"test.h"
using namespace std;


int main()
{


	MyMap<int, string>ttt;
	MyMap<int, string>::iterator iter;

	ttt.insert(pair<int, string>(221, "dfsfs"));
	ttt.insert(pair<int, string>(222, "a"));
	ttt.insert(pair<int, string>(223, "b"));
	ttt.insert(pair<int, string>(224, "c"));
	iter = ttt.find(222);
	ttt.erase(iter);
	iter = ttt.find(222);
	cout << ttt.size() << endl;	
	if (iter==nullptr)
	{
		cout << "元素不存在" << endl;
	}
	else
	{
		cout << iter->data << endl;
	}
	//tree.remove(tree.get_root(),ttt);
	/*
	Node<int>* ttt = tree.find(69);
	tree.remove(ttt);
	*/

	int rrr;
	cin >> rrr;
}