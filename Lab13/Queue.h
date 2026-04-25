#pragma once
#include "../task1/List.h"

// Queue privately inherits List — users cannot see List's interface.
// enqueue / dequeue are defined in terms of inherited list operations.
template<class NODETYPE>
class Queue : private List<NODETYPE>
{
public:
    // Add an element to the back of the queue
    void enqueue(const NODETYPE& data)
    {
        this->insertAtBack(data);
    }

    // Remove an element from the front of the queue
    // Returns true on success, false if empty
    bool dequeue(NODETYPE& data)
    {
        return this->removeFromFront(data);
    }

    // Expose isEmpty and print from the private base
    using List<NODETYPE>::isEmpty;
    using List<NODETYPE>::print;
};
