#include "Queue.h"
#include <iostream>
using std::cout;

//Task 2 main

int main()
{
    cout << "=== Task 2: Queue<int> (private inheritance from List) ===\n";
    Queue<int> q;

    cout << "Enqueueing 10, 20, 30, 40...\n";
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);
    q.print();   // 10 20 30 40 (FIFO order)

    int val;
    while (!q.isEmpty())
    {
        q.dequeue(val);
        cout << "Dequeued: " << val << "\n";
    }

    // Dequeue on empty queue
    bool result = q.dequeue(val);
    cout << "Dequeue on empty queue returned: " << (result ? "true" : "false") << "\n";

    cout << "\n=== Task 2: Queue<std::string> ===\n";
    Queue<std::string> sq;
    sq.enqueue("first");
    sq.enqueue("second");
    sq.enqueue("third");
    sq.print();

    std::string s;
    sq.dequeue(s);
    cout << "Dequeued: " << s << "\n";
    sq.print();

    return 0;
}
