#pragma once
#include <iostream>
using std::cout;
using std::endl;

class Base
{
public:
    // Making testFunction virtual enables runtime (dynamic) dispatch.
    // Without 'virtual', the call is resolved at compile time based on
    // the pointer type, so Base::testFunction() would always be called.
    virtual void testFunction()
    {
        cout << "Base class" << endl;
    }

    // Virtual destructor: essential whenever a base class pointer might
    // delete a derived object — ensures the correct destructor chain runs.
    virtual ~Base() = default;
};

class Derived : public Base
{
public:
    // 'override' (C++11) lets the compiler verify we're actually
    // overriding a virtual function — great practice.
    void testFunction() override
    {
        cout << "Derived class" << endl;
    }
};
