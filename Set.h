#pragma once
#include"LinkList.h"

template<class T, class _Pr> class Set
{
private:
	LinkList<T> elemSet;
	_Pr _Func;

public:
	typedef typename LinkList<T>::iterator iterator;

	Set();
	Set(const Set& copy);
	Set(Set&& move);
	~Set();
	Set(const T *inputArray, unsigned int elemSize);
	void assign(const T *inputArray, unsigned int elemSize);
	void insert(T& data);
	void print_set();
	int size();
	Set<T, _Pr> operator || (Set<T, _Pr> & rightSet);
	Set<T, _Pr> operator && (Set<T, _Pr> & rightSet);
	Set<T, _Pr> operator - (Set<T, _Pr> & rightSet);
	Set<T, _Pr> operator = (const Set<T, _Pr>& copy);
	Set<T, _Pr> operator = (Set<T, _Pr>&& move);
	iterator begin()
	{
		return elemSet.begin();
	}
	iterator end()
	{
		return elemSet.end();
	}
};

template<class T, class _Pr>
inline Set<T, _Pr>::Set()
{
}

template<class T, class _Pr>
Set<T, _Pr>::Set(const Set & copy)
{
	elemSet = copy.elemSet;
}

template<class T, class _Pr>
Set<T, _Pr>::Set(Set && move)
{
	if (move.size() != 0)
	{
		elemSet.move_copy(move.elemSet);
	}
}


template<class T, class _Pr>
inline Set<T, _Pr>::~Set()
{
	//std::cout << "call ~Set" << std::endl;
}


template<class T, class _Pr>
Set<T, _Pr>::Set(const T *inputArray, unsigned int elemSize)
{
	size_t i = 0;
	for (; i < elemSize; ++i)
	{
		if (_Func(inputArray[i]))
		{
			elemSet.push_front(inputArray[i]);
			++i;
			break;
		}
	}
	for (; i < elemSize; ++i)
	{
		if (_Func(inputArray[i]))
		{
			for (auto iter = elemSet.begin(); ; ++iter)
			{
				if (iter == elemSet.end())
				{
					elemSet.insert(iter, inputArray[i]);
					break;
				}
				if (_Func(inputArray[i], *iter))
				{
					elemSet.insert(iter, inputArray[i]);
					break;
				}
				if (*iter == inputArray[i])
				{
					break;
				}
			}
		}
	}
}

template<class T, class _Pr>
void Set<T, _Pr>::assign(const T * inputArray, unsigned int elemSize)
{
	elemSet.clear();
	size_t i = 0;
	for (; i < elemSize; ++i)
	{
		if (_Func(inputArray[i]))
		{
			elemSet.push_front(inputArray[i]);
			++i;
			break;
		}
	}
	for (; i < elemSize; ++i)
	{
		if (_Func(inputArray[i]))
		{
			for (auto iter = elemSet.begin(); ; ++iter)
			{
				if (iter == elemSet.end())
				{
					elemSet.insert(iter, inputArray[i]);
					break;
				}
				if (_Func(inputArray[i], *iter))
				{
					elemSet.insert(iter, inputArray[i]);
					break;
				}
				if (*iter == inputArray[i])
				{
					break;
				}
			}
		}
	}
}


template<class T, class _Pr>
void Set<T, _Pr>::insert(T& data)
{
	if (!_Func(data))
	{
		return;
	}
	for (auto i = elemSet.begin(); ; ++i)
	{
		if (i == elemSet.end())
		{
			elemSet.insert(i, data);
			break;
		}
		if (_Func(data, *i))
		{
			elemSet.insert(i, data);
			break;
		}
		if (*i == data)
		{
			break;
		}
	}
	return;
}

template<class T, class _Pr>
inline void Set<T, _Pr>::print_set()
{
	for (auto i = elemSet.begin(); i != elemSet.end(); ++i)
	{
		std::cout << *i << ' ';
	}
	std::cout << std::endl;
}


template<class T, class _Pr>
inline int Set<T, _Pr>::size()
{
	return elemSet.size();
}

template<class T, class _Pr>
Set<T, _Pr> Set<T, _Pr>::operator||(Set<T, _Pr> & rightSet)
{
	Set<T, _Pr> unionSet;
	auto leftIter = elemSet.begin();
	auto rightIter = rightSet.elemSet.begin();
	while (leftIter != elemSet.end() && rightIter != rightSet.elemSet.end())
	{
		if (*leftIter < *rightIter)
		{
			unionSet.elemSet.push_back(*leftIter);
			++leftIter;
		}
		else if(*leftIter == *rightIter)
		{
			unionSet.elemSet.push_back(*leftIter);
			++leftIter;
			++rightIter;
		}
		else if (*leftIter > *rightIter)
		{
			unionSet.elemSet.push_back(*rightIter);
			++rightIter;
		}
	}
	if (leftIter == this->elemSet.end())
	{
		while (rightIter != rightSet.end())
		{
			unionSet.elemSet.push_back(*rightIter);
			++rightIter;
		}
	}
	else
	{
		while (leftIter != this->elemSet.end())
		{
			unionSet.elemSet.push_back(*leftIter);
			++leftIter;
		}
	}
	return unionSet;
}

template<class T, class _Pr>
Set<T, _Pr> Set<T, _Pr>::operator&&(Set<T, _Pr>& rightSet)
{
	Set<T, _Pr> intersectionSet;
	auto leftIter = this->elemSet.begin();
	auto rightIter = rightSet.elemSet.begin();
	while (leftIter != this->elemSet.end() && rightIter != rightSet.elemSet.end())
	{
		if (*leftIter < *rightIter)
		{
			++leftIter;
		}
		else if (*leftIter == *rightIter)
		{
			intersectionSet.elemSet.push_back(*leftIter);
			++leftIter;
			++rightIter;
		}
		else if (*leftIter > *rightIter)
		{
			++rightIter;
		}
	}
	return intersectionSet;
}

template<class T, class _Pr>
Set<T, _Pr> Set<T, _Pr>::operator-(Set<T, _Pr>& rightSet)
{
	Set<T, _Pr> differenceSet;
	auto leftIter = this->elemSet.begin();
	auto rightIter = rightSet.elemSet.begin();
	while (leftIter != this->elemSet.end() && rightIter != rightSet.elemSet.end())
	{
		if (*leftIter < *rightIter)
		{
			differenceSet.elemSet.push_back(*leftIter);
			++leftIter;
		}
		else if (*leftIter == *rightIter)
		{
			++leftIter;
			++rightIter;
		}
		else if (*leftIter > *rightIter)
		{
			++rightIter;
		}
	}
	if (leftIter == this->elemSet.end())
	{
		while (rightIter != rightSet.end())
		{
			differenceSet.elemSet.push_back(*rightIter);
			++rightIter;
		}
	}
	else
	{
		while (leftIter != this->elemSet.end())
		{
			differenceSet.elemSet.push_back(*leftIter);
			++leftIter;
		}
	}
	return differenceSet;
}

template<class T, class _Pr>
Set<T, _Pr> Set<T, _Pr>::operator=(const Set<T, _Pr>& copy)
{
	if (this != &copy)
	{
		elemSet = copy.elemSet;
	}
	return *this;
}

template<class T, class _Pr>
Set<T, _Pr> Set<T, _Pr>::operator=(Set<T, _Pr>&& move)
{
	if ((move.size() != 0) && (this != &move))
	{
		elemSet.clear();
		elemSet.move_copy(move.elemSet);
	}
	return *this;
}

