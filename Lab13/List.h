#pragma once
#include <iostream>
using std::cout;
using std::endl;

// Forward declaration
template<class NODETYPE> class List;

// ─────────────────────────────────────────────
// ListNode
// ─────────────────────────────────────────────
template<class NODETYPE>
class ListNode
{
    friend class List<NODETYPE>;   // List can touch private members
public:
    explicit ListNode(const NODETYPE& newData)
        : data(newData), nextPtr(nullptr) {}

    NODETYPE getData() const { return data; }

private:
    NODETYPE              data;
    ListNode<NODETYPE>*   nextPtr;
};

// ─────────────────────────────────────────────
// List
// ─────────────────────────────────────────────
template<class NODETYPE>
class List
{
public:
    List()  : firstPtr(nullptr), lastPtr(nullptr) {}

    ~List()
    {
        if (!isEmpty())
        {
            ListNode<NODETYPE>* currentPtr = firstPtr;
            while (currentPtr != nullptr)
            {
                ListNode<NODETYPE>* tempPtr = currentPtr;
                currentPtr = currentPtr->nextPtr;
                delete tempPtr;
            }
        }
    }

    // Insert a new node at the front of the list
    void insertAtFront(const NODETYPE& newData)
    {
        ListNode<NODETYPE>* newPtr = getNewNode(newData);
        if (isEmpty())
            firstPtr = lastPtr = newPtr;
        else
        {
            newPtr->nextPtr = firstPtr;
            firstPtr = newPtr;
        }
    }

    // Insert a new node at the back of the list
    void insertAtBack(const NODETYPE& newData)
    {
        ListNode<NODETYPE>* newPtr = getNewNode(newData);
        if (isEmpty())
            firstPtr = lastPtr = newPtr;
        else
        {
            lastPtr->nextPtr = newPtr;
            lastPtr = newPtr;
        }
    }

    // Remove a node from the front; store its data in removedData
    bool removeFromFront(NODETYPE& removedData)
    {
        if (isEmpty()) return false;

        ListNode<NODETYPE>* tempPtr = firstPtr;
        removedData = firstPtr->data;

        if (firstPtr == lastPtr)
            firstPtr = lastPtr = nullptr;
        else
            firstPtr = firstPtr->nextPtr;

        delete tempPtr;
        return true;
    }

    // Remove a node from the back; store its data in removedData
    bool removeFromBack(NODETYPE& removedData)
    {
        if (isEmpty()) return false;

        ListNode<NODETYPE>* tempPtr = lastPtr;
        removedData = lastPtr->data;

        if (firstPtr == lastPtr)
        {
            firstPtr = lastPtr = nullptr;
        }
        else
        {
            // Walk to the second-to-last node
            ListNode<NODETYPE>* currentPtr = firstPtr;
            while (currentPtr->nextPtr != lastPtr)
                currentPtr = currentPtr->nextPtr;
            lastPtr = currentPtr;
            lastPtr->nextPtr = nullptr;
        }

        delete tempPtr;
        return true;
    }

    bool isEmpty() const { return firstPtr == nullptr; }

    void print() const
    {
        if (isEmpty()) { cout << "List is empty.\n"; return; }
        ListNode<NODETYPE>* currentPtr = firstPtr;
        cout << "List: ";
        while (currentPtr != nullptr)
        {
            cout << currentPtr->data << " ";
            currentPtr = currentPtr->nextPtr;
        }
        cout << "\n";
    }

protected:
    ListNode<NODETYPE>* firstPtr;
    ListNode<NODETYPE>* lastPtr;

    // Utility: allocate and return a new node
    ListNode<NODETYPE>* getNewNode(const NODETYPE& newData)
    {
        return new ListNode<NODETYPE>(newData);
    }
};
