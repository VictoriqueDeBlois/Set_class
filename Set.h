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



template<class T>
Set<T>::Set()
{

}

template<class T>
Set<T>::~Set()
{

}

template<class T>
Set<T>::Set(const T *input, size_t elemSize, bool(*_DefData)(T data))
{
	dataDef = _DefData;
	for (size_t i = 0; i < elemSize; i++)
	{
		if (_DefData(input[i]))
		{
			LinkList::iterator<T>
		}
	}
}

template<class T>
void Set<T>::insert(T data)
{

}
