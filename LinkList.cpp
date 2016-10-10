#include "LinkList.h"


template<class Type>
 LinkList<Type>::LinkList()
{
	size = 0;
	head = new NodeType;
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
bool  LinkList<Type>::list_empty()
{
	return size == 0;
}


template<class Type>
int  LinkList<Type>::list_size()
{
	return size;
}


template<class Type>
NodeType<Type> * LinkList<Type>::at(size_t pos)
{
	NodeType<Type> *pNode = head->next;

	while (pos != 0 && pNode != nullptr)
	{
		pNode = pNode->next;
		pos--;
	}

	return pNode;
}

template<class Type> 
void  LinkList<Type>::insert_after(NodeType<Type> *exsitNode, Type date)
{
	NodeType<Type> *newNode = new NodeType;
	newNode->data = data;
	newNode->next = exsitNode->next;
	exsitNode->next = newNode;
	newNode->prior = exsitNode;
	newNode->next->prior = newNode;
	if (exsitNode == tail)
	{
		tail = newNode;
	}
	size++;
}


template<class Type> 
void LinkList<Type>::push_back(Type data)
{
	NodeType<Type> *newNode = new NodeType;
	newNode->data = data;
	newNode->next = nullptr;
	newNode->prior = tail;
	tail->next = newNode;
	tail = newNode;
	size++;
}

template<class Type>
void LinkList<Type>::push_front(Type data)
{
	NodeType<Type> *newNode = new NodeType;
	newNode->data = data;
	newNode->next = head->next;
	newNode->prior = head;
	head->next = newNode;
	newNode->next->prior = newNode;
	size++;
}

template<class Type> 
void LinkList<Type>::pop_back()
{
	NodeType<Type> *deleteNode = tail;
	tail = tail->prior;
	tail->next = nullptr;
	delete deleteNode;
	size--:
}

template<class Type>
void LinkList<Type>::pop_front()
{
	NodeType<Type> *deleteNode = head->next;
	head->next = deleteNode->next;
	deleteNode->next->prior = head;
	delete deleteNode;
	size--;
}
