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
#include"MyVector.h"
#include<vector>
#include<list>
using namespace std;


int main()
{
	list<int>test;


	MyVector<int>ttt(8);
	MyVector<int>::iterator
	
	int rrr;
	cin >> rrr;
	
	
	
}