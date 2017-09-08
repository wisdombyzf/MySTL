#pragma once
#include<iostream>
template<typename T>
class MyVector
{
public:
	void push_back(T a)
	{
		a = a + 1;
		std::cout << a <<std:: endl;
	}
private:
};

