#pragma once
#include <iostream>
#include <fstream>
#include <print>
#include "../Node/TransactionNode.hpp"

using std::string;

class BST
{
private:
    Node* _pRoot;

    void _destroy_tree(Node* pT);
    void insert(Node*& pT, string data, int units);
    void in_order_traversal(Node* pT, int depth);

public:
    void set_pRoot(Node* newNode);
    Node* get_pRoot();

    BST();
    ~BST();

    void insert(string data, int units);
    void in_order_traversal();
    TransactionNode& find_smallest();
    TransactionNode& find_largest();
};

BST::BST() : _pRoot(nullptr) {}
BST::~BST() { _destroy_tree(_pRoot); }

void BST::set_pRoot(Node* newNode)
{
    _pRoot = newNode;
}
Node* BST::get_pRoot()
{
    return _pRoot;
}

void BST::_destroy_tree(Node* pT)
{
    if (pT == nullptr) return;
    _destroy_tree(pT->get_pLeft());
    _destroy_tree(pT->get_pRight());
    delete pT;
}
void BST::insert(Node*& pT, string data, int units)
{
    if (pT == nullptr)
    {
        pT = new TransactionNode(data, units);
    }
    else if (units < dynamic_cast<TransactionNode*>(pT)->get_units())
    {
        insert(pT->get_pLeft(), data, units);
    }
    else
    {
        insert(pT->get_pRight(), data, units);
    }
}
void BST::in_order_traversal(Node* pT, int depth)
{
    if (pT == nullptr) return;
    in_order_traversal(pT->get_pLeft(), depth + 1);
    for (int i = 0; i < depth; i++) std::cout << "-";
    pT->print_data();
    in_order_traversal(pT->get_pRight(), depth + 1);
}

void BST::insert(string data, int units)
{
    insert(_pRoot, data, units);
}
void BST::in_order_traversal()
{
    in_order_traversal(_pRoot,0);
}
TransactionNode& BST::find_smallest()
{
    Node* pT = _pRoot;
    while (pT->get_pLeft() != nullptr)
    {
        pT = pT->get_pLeft();
    }
    return *dynamic_cast<TransactionNode*>(pT);
}
TransactionNode& BST::find_largest()
{
    Node* pT = _pRoot;
    while (pT->get_pRight() != nullptr)
    {
        pT = pT->get_pRight();
    }
    return *dynamic_cast<TransactionNode*>(pT);
}