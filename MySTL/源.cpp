/*
ʹ��VS2015ʱ�������֣�
*****************************************************************************
����	C4996	'std::uninitialized_copy::_Unchecked_iterators::_Deprecate':
Call to 'std::uninitialized_copy' with parameters that may be unsafe - this
call relies on the caller to check that the passed values are correct. 
To disable this warning........
****************************************************************************
�����Ԥ������(��Ŀ����----C/C++----Ԥ����----Ԥ����������)��
_SCL_SECURE_NO_WARNINGS
*/

#include<iostream>
#include"RBTree.h"
#include<queue>
#include"MyQueue.h"
#include"MyStack.h"
#include<stack>
#include"MyVector.h"
#include<list>
#include<algorithm>
#include"MyList.h"

//#include"test.h"
using namespace std;


int main()
{
	RBTree<int>tree;
	for (int  i = 0; i < 9; i++)
	{
		int temp = rand() % 100;
		cout << temp << endl;

		Node<int>* t1 = new Node<int>;
		t1->key = temp;
		tree.insert(t1);
	}

	Node<int>* ttt = tree.find(69);
	tree.remove(ttt);


	int rrr;
	cin >> rrr;
	
	
	
}