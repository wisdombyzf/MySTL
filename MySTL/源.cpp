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
using namespace std;


int main()
{
	MyVector<int>ttt;
	for (int  i = 0; i < 16; i++)
	{
		ttt.push_back(i);
	}
	ttt.erase(ttt.begin(),ttt.begin()+4);
	
	for (int  i = 0; i < ttt.size(); i++)
	{
		cout << i << ":" << ttt[i] << endl;
	}
	int rrr;
	cin >> rrr;
	
	
	
}