#pragma once
#include <iostream>
#include <fstream>
#include <print>
#include <string>
#include "./Node.hpp"

using std::string;
using std::print;
using std::println;

class TransactionNode : public Node
{
private:
	int _units;

public:
	TransactionNode();
	TransactionNode(string newData, int newUnits);
	~TransactionNode();

	void set_units(int newUnits);
	int get_units();

	void print_data();
};

TransactionNode::~TransactionNode() {}
TransactionNode::TransactionNode(string data, int units) : Node(data), _units(units) {}

void TransactionNode::set_units(int newUnits)
{
	_units = newUnits;
}
int TransactionNode::get_units()
{
	return _units;
}

void TransactionNode::print_data()
{
	println("{} {}", _data, _units);
}