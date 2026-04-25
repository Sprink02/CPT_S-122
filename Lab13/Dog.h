#pragma once
#include "Mammal.h"

class Dog : public Mammal
{
public:
    Dog()
    {
        cout << "Dog constructor..." << endl;
    }

    ~Dog() override
    {
        cout << "Dog destructor..." << endl;
    }

    void Move() const override
    {
        cout << "Dog runs on four legs!" << endl;
    }

    void Speak() const override
    {
        cout << "Dog says: Woof!" << endl;
    }

    // Dog-specific method — not in Mammal.
    // NOTE: not accessible via a Mammal* without casting.
    void WagTail() const
    {
        cout << "Dog wags its tail enthusiastically!" << endl;
    }
};
