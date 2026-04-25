#include "List.h"
#include <iostream>
using std::cout;

//Task 1 main

int main()
{
    cout << "=== Task 1: List<int> ===\n";
    List<int> intList;

    intList.insertAtBack(10);
    intList.insertAtBack(20);
    intList.insertAtBack(30);
    intList.insertAtFront(5);
    intList.print();           // 5 10 20 30

    int val;
    intList.removeFromFront(val);
    cout << "Removed from front: " << val << "\n";
    intList.print();           // 10 20 30

    intList.removeFromBack(val);
    cout << "Removed from back: " << val << "\n";
    intList.print();           // 10 20

    cout << "\n=== Task 1: List<double> ===\n";
    List<double> dblList;
    dblList.insertAtBack(1.1);
    dblList.insertAtBack(2.2);
    dblList.insertAtFront(0.5);
    dblList.print();

    cout << "\n=== Task 1: List<std::string> ===\n";
    List<std::string> strList;
    strList.insertAtBack("hello");
    strList.insertAtBack("world");
    strList.insertAtFront("start");
    strList.print();

    return 0;
}
