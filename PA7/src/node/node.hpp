#pragma once

template <class T>
class Node
{
private:
	T _data;
	Node* _pNext;

public:
	Node() : _data(), _pNext(nullptr) {}
	Node(Node* pNext) : _data(), _pNext(pNext) {}
	Node(T data) : _data(data), _pNext(nullptr) {}
	Node(T data, Node* pNext) : _data(data), _pNext(pNext) {}

	T get_data() { return _data; }
	T& get_data_ref() { return _data; }
	Node* get_pNext() { return _pNext; }
	void setData(const T& newData) { _data = newData; }
	void set_pNext(Node* newPNext) { _pNext = newPNext; }
};