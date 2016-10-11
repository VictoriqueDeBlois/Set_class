#pragma once
#include"LinkList.h"

template<class T> class Set
{
private:
	LinkList<T> elemSet;
	bool(*dataDef)(T data);

public:
	Set();
	~Set();
	Set(const T *inputStr, size_t elemSize, bool(*_DefData)(T data));
	void insert(T data);
};
