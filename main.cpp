#include<iostream>
#include "LinkList.h"
#include "Set.h"

struct setdef
{
	bool operator()(const char& left, const char& right) const
	{
		return (left < right);
	}

	bool operator()(const char& elem) const
	{
		return (elem >= 'a' && elem <= 'z');
	}
};


int main()
{
	using namespace std;
	
	system("pause >nul");
	return 0;
}