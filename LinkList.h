#pragma once

const int error = 1;

template <class Type> struct NodeType
{
	Type data;
	NodeType *prior;
	NodeType *next;
};

template <class Type> class LinkList
{
private:
	NodeType<Type> *head, *tail;
	int listSize;

public:	
	class iterator;
	
	LinkList();
	~LinkList();
	inline bool empty();
	inline int size();
	void insert(iterator Where, const Type& Val);
	void push_back(const Type &data);
	void push_front(const Type &data);
	void pop_back();
	void pop_front();
	void erase(iterator _Where);
	iterator begin()
	{
		return iterator(head->next);
	}
	iterator end()
	{
		return iterator(tail);
	}	
	Type &at(size_t pos);


	
	class iterator
	{
	private:
		friend class LinkList;
		NodeType<Type> *iter;
		

	public:
		iterator()
		{
		}

		iterator(NodeType<Type> *pointer)
		{
			iter = pointer;
		}

		~iterator()
		{
		}

		iterator &operator ++()
		{
			iter = iter->next;
			return *this;
		}

		iterator &operator --()
		{
			iter = iter->prior;
			return *this;
		}

		iterator operator ++(int)
		{
			iterator copy = *this;
			iter = iter->next;
			return copy;
		}

		iterator operator --(int)
		{
			iterator copy = *this;
			iter = iter->prior;
			return copy;
		}

		iterator& operator =(const iterator& copySource)
		{
			if (this != &copySource)
			{
				iter = copySource.iter;
			}
			return *this;
		}

		bool operator != (const iterator& compare)
		{
			return this->iter != compare.iter;
		}

		bool operator == (const iterator& compare)
		{
			return this->iter == compare.iter;
		}

		Type & operator * () const
		{
			return iter->data;
		}

		Type * operator -> () const
		{
			return &iter->data;
		}
	};
};


template<class Type>
LinkList<Type>::LinkList()
{
	listSize = 0;
	head = new NodeType<Type>;
	tail = new NodeType<Type>;
	head->next = tail;
	head->prior = nullptr;
	tail->prior = head;
	tail->next = nullptr;
}


template<class Type>
LinkList<Type>::~LinkList()
{
	NodeType<Type> *pNode = head->next;
	NodeType<Type> *deleteNode;
	while (pNode != nullptr)
	{
		deleteNode = pNode;
		pNode = pNode->next;
		delete deleteNode;
	}
	delete head;
}


template<class Type>
bool  LinkList<Type>::empty()
{
	return size() == 0;
}


template<class Type>
int  LinkList<Type>::size()
{
	return listSize;
}


template<class Type>
Type & LinkList<Type>::at(size_t pos)
{
	NodeType<Type> *pNode = head->next;

	if (pos > size() - 1)
		throw error;
	while (pos != 0)
	{
		pNode = pNode->next;
		--pos;
	}
	return pNode->data;
}

template<class Type>
void  LinkList<Type>::insert(iterator Where, const Type &Val)
{
	NodeType<Type> *newNode = new NodeType<Type>;
	newNode->data = Val;
	newNode->next = Where.iter;
	newNode->prior = Where.iter->prior;
	newNode->prior->next = newNode;
	Where.iter->prior = newNode;
	++listSize;
}


template<class Type>
void LinkList<Type>::push_back(const Type &data)
{
	NodeType<Type> *newNode = new NodeType<Type>;
	newNode->data = data;
	newNode->next = tail;
	newNode->prior = tail->prior;
	tail->prior->next = newNode;
	tail->prior = newNode;
	++listSize;
}

template<class Type>
void LinkList<Type>::push_front(const Type &data)
{
	NodeType<Type> *newNode = new NodeType<Type>;
	newNode->data = data;
	newNode->next = head->next;
	newNode->prior = head;
	head->next = newNode;
	newNode->next->prior = newNode;
	++listSize;
}

template<class Type>
void LinkList<Type>::pop_back()
{
	NodeType<Type> *deleteNode = tail->prior;
	tail->prior = deleteNode->prior;
	deleteNode->prior->next = tail;
	delete deleteNode;
	--listSize;
}

template<class Type>
void LinkList<Type>::pop_front()
{
	NodeType<Type> *deleteNode = head->next;
	head->next = deleteNode->next;
	deleteNode->next->prior = head;
	delete deleteNode;
	--listSize;
}

template<class Type>
void LinkList<Type>::erase(iterator _Where)
{
	_Where.iter->prior->next = _Where.iter->next;
	_Where.iter->next->prior = _Where.iter->prior;
	delete _Where.iter;
}

