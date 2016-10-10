#pragma once
#include"LinkList.h"

template<class T> class Set
{
private:
	LinkList<T> elemSet;

public:
	Set();
	~Set();
	void insert(T data, _Fn1 _Func);
};
