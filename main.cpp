#include<iostream>
#include<string>
#include<vector>
#include "LinkList.h"
#include "Set.h"

template<typename _Type,
	class _Pr> inline
	void reinput(_Type& _Ch, _Pr _Pred, char* _String = "input again\n")
{
	while (!_Pred(_Ch))
	{
		std::cin.clear();
		char ch;
		while ((ch = getchar()) != '\n')
			continue;
		std::cout << _String << std::flush;
		std::cin >> _Ch;
	}
}

using namespace std;

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

string explain_express(string &exp);

int main()
{
	std::cout << "input set1" << endl;
	string set1Str;
	getline(cin, set1Str);
	Set<char , setdef> set1(set1Str.c_str(), set1Str.length());
	std::cout << "input set2" << endl;
	string set2Str;
	getline(cin, set2Str);
	Set<char, setdef> set2(set2Str.c_str(), set2Str.length());

	Set<char, setdef> ans;

	while (true)
	{
		cout << endl;
		string expression;
		getline(cin, expression);
		string exp = explain_express(expression);

		while (exp.length() == 0)
		{
			cout << "-->  error" << endl;
			cout << endl;
			getline(cin, expression);
			exp = explain_express(expression);
		}

		if (exp.length() == 1)
		{
			switch (exp[0])
			{
			case '1':
				ans = set1;
				break;
			case '2':
				ans = set2;
				break;
			case 'a':
				break;
			}
		}
		else
		{
			vector<Set<char, setdef>*> opnd;
			switch (exp[0])
			{
			case '1':
				opnd.push_back(&set1);
				break;
			case '2':
				opnd.push_back(&set2);
				break;
			case 'a':
				opnd.push_back(&ans);
				break;		
			}
			switch (exp[2])
			{
			case '1':
				opnd.push_back(&set1);
				break;
			case '2':
				opnd.push_back(&set2);
				break;
			case 'a':
				opnd.push_back(&ans);
				break;
			}

			switch (exp[1])
			{
			case '+':
			case '|':
				ans = (*opnd[0]) || (*opnd[1]);
				break;
			case '*':
			case '&':
				ans = (*opnd[0]) && (*opnd[1]);
				break;
			case '-':
				ans = (*opnd[0]) - (*opnd[1]);
				break;
			}
		}
		std::cout << "-->";
		ans.print_set();

	}

	return 0;
}

string explain_express(string &exp)
{
	string returnExp;

	for (auto i = exp.begin(); i != exp.end(); ++i)
	{
		if (isblank(*i))
		{
			exp.erase(i);
		}
	}
	size_t pos = exp.find_first_of("+|*&-");
	if (pos == string::npos)
	{
		if ((pos = exp.find("set")) != string::npos)
		{
			if (exp[pos+3] == '1')
			{
				returnExp.push_back('1');
			}
			else if (exp[pos + 3] == '2')
			{
				returnExp.push_back('2');
			}
		}
		else if (exp.find("ans") != string::npos)
		{
			returnExp.push_back('a');
		}
	}
	else
	{
		if (exp.find("set1", 0, pos) != string::npos)
		{
			returnExp.push_back('1');
		}
		else if (exp.find("set2", 0, pos) != string::npos)
		{
			returnExp.push_back('2');
		}
		else if (exp.find("ans", 0, pos) != string::npos)
		{
			returnExp.push_back('a');
		}

		returnExp.push_back(exp[pos]);

		if (exp.find("set1", pos) != string::npos)
		{
			returnExp.push_back('1');
		}
		else if (exp.find("set2", pos) != string::npos)
		{
			returnExp.push_back('2');
		}
		else if (exp.find("ans", pos) != string::npos)
		{
			returnExp.push_back('a');
		}
	}
	return returnExp;
}