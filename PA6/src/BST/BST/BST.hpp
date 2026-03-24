#pragma once
#include <iostream>
#include <fstream>
#include <print>
#include "../BSTnode/BSTNode.hpp"


template <typename K, typename V>
class BST {
private:
	BSTNode<K, V>* _pRoot;
	//Recursive Helper functions
	void insertHelper(BSTNode<K, V>*& pNode, const K& key, const V& value)
	{
		if (pNode == nullptr)
		{
			pNode = new BSTNode<K, V>(key, value);
		}
		else if (key < pNode->getKey()) {
			BSTNode<K, V>* left = pNode->getLeft();
			insertHelper(left, key, value);
			pNode->setLeft(left);
		}
		else if (key > pNode->getKey()) {
			BSTNode<K, V>* right = pNode->getRight();
			insertHelper(right, key, value);
			pNode->setRight(right);
		} //dupes are ignored
	}
	V searchHelper(BSTNode<K, V>* pNode, const K& key) const
	{
		if (pNode == nullptr) {
			return V{};  //Not found (error status)
		}
		if (key == pNode->getKey()) {
			return pNode->getValue();
		}
		else if (key < pNode->getKey()) {
			return searchHelper(pNode->getLeft(), key);
		}
		else {
			return searchHelper(pNode->getRight(), key);
		}
	}
	void printInOrder(BSTNode<K, V>* pNode) const
	{
		if (pNode == nullptr) return;
		printInOrder(pNode->getLeft());
		std::cout << pNode->getKey() << "  " << pNode->getValue() << "\n";
		printInOrder(pNode->getRight());
	}
	void destroyTree(BSTNode<K, V>* pNode)
	{
		if (pNode == nullptr) return;
		destroyTree(pNode->getLeft());
		destroyTree(pNode->getRight());
		delete pNode;
	}
public:
	BST(const string& filename) : _pRoot(nullptr)
	{
		std::ifstream inFile(filename);
		if (!inFile.is_open()) {
			std::cerr << "ERROR: Could not open " << filename << "\n";
			return;
		}

		K key;
		V value;
		//EOF is found and this fails naturally
		while (inFile >> key >> value) {
			insert(key, value);
		}
		inFile.close();
	}
	~BST()
	{
		destroyTree(_pRoot);
	}

	void insert(const K& key, const V& value)
	{
		insertHelper(_pRoot, key, value);
	}
	V search(const K& key) const
	{
		return searchHelper(_pRoot, key);
	}
	void print() const
	{
		printInOrder(_pRoot);
		std::cout << "\n";
	}
};