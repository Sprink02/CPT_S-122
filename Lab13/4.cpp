#include "Mammal.h"
#include "Dog.h"
#include <iostream>
using std::cout;

int main()
{
    cout << "=== Task 4: Mammal* pointing to a Dog (polymorphism) ===\n\n";

    // Mammal pointer → Dog object: virtual dispatch calls Dog's overrides
    Mammal* pDog = new Dog;
    pDog->Move();    // Dog runs on four legs!
    pDog->Speak();   // Dog says: Woof!

    // pDog->WagTail();  // COMPILE ERROR: WagTail() is not in Mammal
    // To reach WagTail we must cast:
    Dog* castDog = dynamic_cast<Dog*>(pDog);
    if (castDog)
        castDog->WagTail();

    delete pDog;     // virtual destructor ensures Dog destructor is called

    cout << "\n=== Dog pointer → Dog object ===\n\n";
    Dog* pDog2 = new Dog;
    pDog2->Move();
    pDog2->Speak();
    pDog2->WagTail();   // directly accessible via Dog*
    delete pDog2;

    return 0;
}
