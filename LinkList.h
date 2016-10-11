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
	void insert_after(iterator existNode, Type insertData);
	void push_back(Type data);
	void push_front(Type data);
	void pop_back();
	void pop_front();
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
		NodeType<Type> *iter;
		
		friend class LinkList;

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
			if (*this == end())
			{
				throw error;
			}
			iter = iter->next;
			return *this;
		}

		iterator &operator --()
		{
			if (*this == begin())
			{
				throw error;
			}
			iter = iter->prior;
			return *this;
		}

		iterator operator ++(int)
		{
			if (*this == end())
			{
				throw error;
			}
			iterator copy = *this;
			iter = iter->next;
			return copy;
		}

		iterator operator --(int)
		{
			if (*this == begin())
			{
				throw error;
			}
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
void  LinkList<Type>::insert_after(iterator exsitNode, Type date)
{
	if (exsitNode == end())
	{
		throw error;
		return;
	}
	NodeType<Type> *newNode = new NodeType<Type>;
	newNode->data = data;
	newNode->next = exsitNode.iter->next;
	exsitNode.iter->next = newNode;
	newNode->prior = exsitNode.iter;
	newNode->next->prior = newNode;
	++listSize;
}


template<class Type>
void LinkList<Type>::push_back(Type data)
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
void LinkList<Type>::push_front(Type data)
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

