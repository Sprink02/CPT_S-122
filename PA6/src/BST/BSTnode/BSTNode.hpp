#pragma once
#include <iostream>
#include <print>

using std::string;

//K: char; V: string
template <typename K, typename V>
class BSTNode {
private:
    K _Key;                  //English character
    V _Value;                //Morse code string
    BSTNode<K, V>* _pLeft;   //Left child pointer
    BSTNode<K, V>* _pRight;  //Right child pointer

public:
    BSTNode(const K& key, const V& value) //member init list
        : _Key(key), _Value(value), _pLeft(nullptr), _pRight(nullptr) {}

    K    getKey()   const { return _Key; }
    V    getValue() const { return _Value; }

    BSTNode<K, V>* getLeft()  const { return _pLeft; }
    BSTNode<K, V>* getRight() const { return _pRight; }

    void setLeft(BSTNode<K, V>* pNode) { _pLeft = pNode; }
    void setRight(BSTNode<K, V>* pNode) { _pRight = pNode; }
};