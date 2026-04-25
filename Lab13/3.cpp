#include "Task3.h"
#include <iostream>
using std::cout;

int main()
{
    cout << "=== Task 3: Without virtual keyword ===\n";
    cout << "  (Both calls would print 'Base class' if virtual is removed)\n\n";

    cout << "=== Task 3: WITH virtual keyword ===\n";

    Base* ptr = new Base;
    ptr->testFunction();   // prints "Base class"
    delete ptr;

    // ptr now points to a Derived object; virtual dispatch kicks in
    ptr = new Derived;
    ptr->testFunction();   // prints "Derived class"  <-- polymorphism!
    delete ptr;

    cout << "\nExplanation:\n"
         << "  Without 'virtual': both calls resolve at compile-time to\n"
         << "  Base::testFunction() because ptr is of type Base*.\n"
         << "  With 'virtual':    the second call resolves at runtime to\n"
         << "  Derived::testFunction() via the v-table.\n";

    return 0;
}
