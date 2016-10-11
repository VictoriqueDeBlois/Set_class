#pragma once

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
	bool empty();
	int size();
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
			iter = iter->next;
			return *this;
		}

		iterator &operator --()
		{
			iter = iter->prior;
			if (iter == head)
			{
				iter = nullptr;
			}
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
			if (iter == head)
			{
				iter = nullptr;
			}
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
	head->next = nullptr;
	head->prior = nullptr;
	tail = head;
}


template<class Type>
LinkList<Type>::~LinkList()
{
	NodeType<Type> *pNode = head;
	NodeType<Type> *deleteNode;
	while (pNode != nullptr)
	{
		deleteNode = pNode;
		pNode = pNode->next;
		delete deleteNode;
	}
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

	while (pos != 0 && pNode != nullptr)
	{
		pNode = pNode->next;
		--pos;
	}

	return pNode->data;
}

template<class Type>
void  LinkList<Type>::insert_after(iterator exsitNode, Type date)
{
	NodeType<Type> *newNode = new NodeType;
	newNode->data = data;
	newNode->next = exsitNode.iter->next;
	exsitNode.iter->next = newNode;
	newNode->prior = exsitNode.iter;
	newNode->next->prior = newNode;
	if (exsitNode.iter == tail)
	{
		tail = newNode;
	}
	++listSize;
}


template<class Type>
void LinkList<Type>::push_back(Type data)
{
	NodeType<Type> *newNode = new NodeType<Type>;
	newNode->data = data;
	newNode->next = nullptr;
	newNode->prior = tail;
	tail->next = newNode;
	tail = newNode;
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
	NodeType<Type> *deleteNode = tail;
	tail = tail->prior;
	tail->next = nullptr;
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

