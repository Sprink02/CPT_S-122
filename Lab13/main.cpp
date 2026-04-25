#include "Mammal.h"
#include "Dog.h"
#include "Animals.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

// ──────────────────────────────────────────────────────────────────────────────
// Answers to the conceptual questions from the lab sheet
// ──────────────────────────────────────────────────────────────────────────────
void printAnswers()
{
    cout << "\n=== Conceptual Q&A ===\n\n"

    // Q1
    << "Q1. What is a v-table?\n"
    << "  A v-table (virtual dispatch table) is a compiler-generated array of\n"
    << "  function pointers, one per virtual function in a class. Every object\n"
    << "  of a class with virtual functions carries a hidden vptr pointing to\n"
    << "  its class's v-table. At runtime, a virtual call follows the vptr to\n"
    << "  the table and calls the correct override — this is dynamic dispatch.\n\n"

    // Q2
    << "Q2. What is a virtual destructor?\n"
    << "  A destructor declared with 'virtual'. When deleting a derived object\n"
    << "  through a base pointer, the virtual destructor ensures the derived\n"
    << "  destructor (and then the base destructor) are both called, preventing\n"
    << "  resource leaks.\n\n"

    // Q3
    << "Q3. How do you declare a virtual constructor?\n"
    << "  You cannot — constructors cannot be virtual in C++. The object's type\n"
    << "  must be known at the point of construction.\n\n"

    // Q4
    << "Q4. How do you create a virtual copy constructor (clone idiom)?\n"
    << "  Use a virtual 'clone()' method:\n"
    << "    class Base { public: virtual Base* clone() const { return new Base(*this); } };\n"
    << "    class Derived : public Base { public: Derived* clone() const override { return new Derived(*this); } };\n\n"

    // Q5
    << "Q5. How do you invoke a base function from a derived class that overrides it?\n"
    << "  Use the scope resolution operator:  Base::functionName();\n\n"

    // Q6
    << "Q6. How do you invoke a base function from a derived class that does NOT override it?\n"
    << "  Simply call it by name — the base version is found via normal lookup.\n\n"

    // Q7
    << "Q7. If Base declares virtual f(), and Derived overrides it without 'virtual',\n"
    << "    is it still virtual for a third-generation class?\n"
    << "  Yes. Virtuality is inherited. Once virtual, always virtual (though\n"
    << "  writing 'virtual' or 'override' in derived classes is good practice).\n\n"

    // Q8
    << "Q8. What is the 'protected' keyword used for?\n"
    << "  A protected member is accessible within the class itself and by any\n"
    << "  derived classes, but not by external code. It's the middle ground\n"
    << "  between private (class-only) and public (everyone).\n\n"

    // ── Exercises ──────────────────────────────────────────────────────────
    << "=== More Exercises ===\n\n"

    << "Ex 1. Virtual function taking int, returning void:\n"
    << "  virtual void someFunc(int x);\n\n"

    << "Ex 2. Square -> Rectangle -> Shape declaration:\n"
    << "  class Shape   { ... };\n"
    << "  class Rectangle : public Shape   { ... };\n"
    << "  class Square    : public Rectangle { ... };\n\n"

    << "Ex 3. Square constructor initialisation (Shape takes 0, Rectangle takes 2):\n"
    << "  Square::Square(int side)\n"
    << "      : Rectangle(side, side) {}\n\n"

    << "Ex 4. Virtual copy constructor (clone) for Square:\n"
    << "  virtual Square* clone() const override { return new Square(*this); }\n\n"

    << "Ex 5. BUG BUSTER:\n"
    << "  void SomeFunction(Shape);        // takes Shape BY VALUE\n"
    << "  Shape* pRect = new Rectangle;\n"
    << "  SomeFunction(*pRect);            // BUG: object slicing!\n"
    << "  Dereferencing pRect copies only the Shape part into the parameter;\n"
    << "  all Rectangle data is sliced off. Fix: pass by reference or pointer.\n\n"

    << "Ex 6. BUG BUSTER:\n"
    << "  class Shape() { ... virtual Shape(const Shape&); };\n"
    << "  BUG: Constructors cannot be virtual in C++. Declaring one as virtual\n"
    << "  is a compile error. Remove 'virtual' from the copy constructor.\n\n";
}

// ──────────────────────────────────────────────────────────────────────────────
// Main: polymorphic animal array (the lab's Task 5 main)
// ──────────────────────────────────────────────────────────────────────────────
int main()
{
    cout << "=== Task 5: Polymorphic Mammal Array ===\n\n";

    const int SIZE = 5;
    Mammal* theArray[SIZE];
    Mammal* ptr = nullptr;
    int choice, i;

    for (i = 0; i < SIZE; i++)
    {
        cout << "(1)dog (2)cat (3)horse (4)guinea pig: ";
        cin >> choice;
        switch (choice)
        {
            case 1:  ptr = new Dog;       break;
            case 2:  ptr = new Cat;       break;
            case 3:  ptr = new Horse;     break;
            case 4:  ptr = new GuineaPig; break;
            default: ptr = new Mammal;    break;
        }
        theArray[i] = ptr;
        cout << "\n";
    }

    cout << "\n--- Each animal speaks ---\n";
    for (i = 0; i < SIZE; i++)
    {
        theArray[i]->Speak();   // runtime dispatch → correct override
        theArray[i]->Move();
        cout << "\n";
    }

    // Clean up — virtual destructor ensures correct chain
    cout << "--- Cleaning up ---\n";
    for (i = 0; i < SIZE; i++)
        delete theArray[i];

    printAnswers();
    return 0;
}
