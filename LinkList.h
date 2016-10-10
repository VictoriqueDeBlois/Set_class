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
	int size;

public:
	LinkList();
	~LinkList();
	inline bool list_empty();
	inline int list_size();
	NodeType<Type> *at(size_t pos);
	void insert_after(NodeType<Type> *existNode, Type insertData);
	void push_back(Type data);
	void push_front(Type data);
	void pop_back();
	void pop_front();
};