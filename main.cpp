#include<iostream>
#include "LinkList.h"

int main()
{
	LinkList<char> test;
	std::cout << test.empty() << std::endl;
	test.push_front('a');
	test.push_front('b');
	test.push_back('x');
	test.push_back('z');
	std::cout << test.size() << std::endl;

	return 0;
}