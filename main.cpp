#include<iostream>
#include "LinkList.h"

int main()
{
	using namespace std;
	LinkList<char> test;
	cout << test.empty() << endl;
	test.push_front('a');
	test.push_front('b');
	test.push_back('x');
	test.push_back('z');
	cout << test.size() << endl;
	for (LinkList<char>::iterator i = test.begin(); i != test.end(); ++i)
	{
		cout << *i << " ";
	}
	system("pause");
	return 0;
}