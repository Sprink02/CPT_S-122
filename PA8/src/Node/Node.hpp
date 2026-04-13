#pragma once
#include <iostream>
#include <fstream>
#include <print>
#include <string>

using std::string;

class Node
{
protected:
	string _data;
	Node* _pLeft;
	Node* _pRight;
public:
	Node();
	Node(string newData);
	virtual ~Node();

	void set_data(string newString);
	void set_pLeft(Node* newNode);
	void set_pRight(Node* newNode);

	string get_data();
	Node*& get_pLeft();
	Node*& get_pRight();

	virtual void print_data() = 0;
};

Node::Node() : _data(""), _pLeft(nullptr), _pRight(nullptr) {}
Node::Node(string newData) : _data(newData), _pLeft(nullptr), _pRight(nullptr) {}
Node::~Node() {}

void Node::set_data(string newString)
{
	_data = newString;
}
void Node::set_pLeft(Node* newNode)
{
	_pLeft = newNode;
}
void Node::set_pRight(Node* newNode)
{
	_pRight = newNode;
}

string Node::get_data()
{
	return _data;
}
Node*& Node::get_pLeft()
{
	return _pLeft;
}
Node*& Node::get_pRight()
{
	return _pRight;
}