#pragma once
#include "Mammal.h"

// ─── Cat ─────────────────────────────────────
class Cat : public Mammal
{
public:
    Cat()  { cout << "Cat constructor..."  << endl; }
    ~Cat() override { cout << "Cat destructor..."  << endl; }

    void Move() const override
    {
        cout << "Cat prowls silently on padded paws!" << endl;
    }

    void Speak() const override
    {
        cout << "Cat says: Meow!" << endl;
    }
};

// ─── Horse ───────────────────────────────────
class Horse : public Mammal
{
public:
    Horse()  { cout << "Horse constructor..."  << endl; }
    ~Horse() override { cout << "Horse destructor..."  << endl; }

    void Move() const override
    {
        cout << "Horse gallops across the field!" << endl;
    }

    void Speak() const override
    {
        cout << "Horse says: Neigh!" << endl;
    }
};

// ─── GuineaPig ───────────────────────────────
class GuineaPig : public Mammal
{
public:
    GuineaPig()  { cout << "GuineaPig constructor..."  << endl; }
    ~GuineaPig() override { cout << "GuineaPig destructor..."  << endl; }

    void Move() const override
    {
        cout << "Guinea pig scurries in little circles!" << endl;
    }

    void Speak() const override
    {
        // As the lab notes: guinea pigs go "weep weep"
        cout << "Guinea pig says: Weep weep!" << endl;
    }
};
