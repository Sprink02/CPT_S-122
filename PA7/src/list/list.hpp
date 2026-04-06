#pragma once

#include "../node/node.hpp"
#include "../data/data.hpp"
#include <string>
#include <print>


template<class T>
class List
{
private:
	Node<T>* _pHead;

public:
	List() : _pHead(nullptr) {}
	~List() { destroy_list(); }

	Node<T>* get_pHead() const
	{
		return _pHead;
	}

	void insert_at_front(const T& data)
	{
		Node<T>* pNew = new Node<T>(data);
		pNew->set_pNext(_pHead);
		_pHead = pNew;
	}
	bool is_empty() const 
	{
		return _pHead == nullptr;
	}
	void destroy_list()
	{
		Node<T>* pCur = _pHead;
		while (pCur != nullptr)
		{
			Node<T>* pNext = pCur->get_pNext();
			delete pCur;
			pCur = pNext;
		}
		_pHead = nullptr;
	}
	void print_list() const
	{
		Node<T>* pCur = _pHead;
		int index = 1;
		while (pCur != nullptr)
		{
			std::print("[{}]{}\n", index++, pCur->getData.get_name());
			pCur = pCur->get_pNext();
		}
	}

};