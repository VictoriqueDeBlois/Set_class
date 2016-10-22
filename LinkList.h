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
	LinkList(const LinkList& copySource);
	~LinkList();
	LinkList<Type>& operator=(const LinkList& copy);
	inline bool empty() const;
	inline int size() const;
	void clear();
	void insert(iterator Where, const Type& Val);
	void push_back(const Type &data);
	void push_front(const Type &data);
	void pop_back();
	void pop_front();
	void erase(iterator _Where);
	void move_copy(LinkList<Type> & move);	//用于移动构造
	iterator begin() const
	{
		return iterator(head->next);
	}
	iterator end() const
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
			return &(iter->data);
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
LinkList<Type>::LinkList(const LinkList<Type> & copySource)
{
	listSize = 0;
	head = new NodeType<Type>;
	tail = new NodeType<Type>;
	head->next = tail;
	head->prior = nullptr;
	tail->prior = head;
	tail->next = nullptr;
	if (copySource.empty())
	{
		return;
	}
	NodeType<Type> *pNode, *pNew;
	pNode = head;
	for (auto i = copySource.begin(); i != copySource.end(); ++i)
	{
		pNew = new NodeType<Type>;
		pNew->data = *i;
		pNew->prior = pNode;
		pNode->next = pNew;
		pNode = pNew;
	}
	pNode->next = tail;
	tail->prior = pNode;
	listSize = copySource.listSize;
}


template<class Type>
LinkList<Type>::~LinkList()
{
	//std::cout << "call ~LinkList" << std::endl;
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
LinkList<Type> & LinkList<Type>::operator=(const LinkList<Type> & copy)
{
	if (this != &copy)
	{
		if (!this->empty())
		{
			this->clear();
		}
		if (copy.empty())
		{
			return *this;
		}
		NodeType<Type> *pNode, *pNew;
		pNode = head;
		for (auto i = copy.begin(); i != copy.end(); ++i)
		{
			pNew = new NodeType<Type>;
			pNew->data = *i;
			pNew->prior = pNode;
			pNode->next = pNew;
			pNode = pNew;
		}
		pNode->next = tail;
		tail->prior = pNode;
		listSize = copy.listSize;
	}
	return *this;
}


template<class Type>
bool  LinkList<Type>::empty() const
{
	return size() == 0;
}


template<class Type>
int  LinkList<Type>::size() const
{
	return listSize;
}

template<class Type>
void LinkList<Type>::clear()
{
	NodeType<Type> *pNode = head->next;
	NodeType<Type> *deleteNode;
	while (pNode != tail)
	{
		deleteNode = pNode;
		pNode = pNode->next;
		delete deleteNode;
	}
	head->next = tail;
	tail->prior = head;
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

template<class Type>
void LinkList<Type>::move_copy(LinkList<Type>& move)
{
	head->next = move.head->next;
	move.head->next->prior = head;
	tail->prior = move.tail->prior;
	move.tail->prior->next = tail;
	move.head->next = move.tail;
	move.tail->prior = move.head;
	listSize = move.listSize;
}

