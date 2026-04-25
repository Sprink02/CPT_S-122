#pragma once
#include <iostream>
using std::cout;
using std::endl;

class Mammal
{
public:
    Mammal() : itsAge(1)
    {
        cout << "Mammal constructor..." << endl;
    }

    // Virtual destructor — required for correct polymorphic cleanup
    virtual ~Mammal()
    {
        cout << "Mammal destructor..." << endl;
    }

    virtual void Move() const
    {
        cout << "Mammal moves a step!" << endl;
    }

    virtual void Speak() const
    {
        cout << "What does a mammal speak? Mammilian!" << endl;
    }

protected:
    int itsAge;
};
