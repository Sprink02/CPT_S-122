#include "sim.hpp"

int SIM::randRange(int low, int high)
{
    return low + (rand() % (high - low + 1));
}
string SIM::randomItem()
{
    static const string items[] = {"milk", "cereal", "steak", "bread", "eggs", "butter", "cheese", "apples", "chicken", "rice"};
    return items[rand() % 10];
}
SIM::SIM()
{
    srand((unsigned)time(nullptr));
    _CustomerCount = 0;
    _expressServiceCountdown = 0;
    _normalServiceCountdown = 0;
    _expressNextArrival = randRange(1, 5);
    _normalNextArrival = randRange(3, 8);
}

/*
Kinda cheats for total time, you know total time because of time left for everyone infront of you + your service
*/
void SIM::arriveExpress(int elapsed)
{
    _CustomerCount++;
    if (_CustomerCount > 24 * 60) _CustomerCount = 1;

    int waitTime = _expressServiceCountdown; //use countdown instead of 1st customer
    QUEUENODE* cur = _expressLane.getPHead();
    if (cur != nullptr) cur = cur->getPNext(); //skip first customer
    while (cur != nullptr)
    {
        waitTime += cur->getData().getServiceTime();
        cur = cur->getPNext();
    }
    
    ITEMLIST* items = new ITEMLIST();
    int itemCount = randRange(1, 5);
    int serviceTime = itemCount;
    for (int i = 0; i < itemCount; i++)
    {
        string item = randomItem();
        items->insertFromHead(item);
        items->itemCount++;
    }

    int totalTime = serviceTime + waitTime;
    _expressLane.enqueue(_CustomerCount, serviceTime, totalTime, items);
    std::println("{}[t={}] Express lane: Customer #{} arrived | serviceTime={} | totalTime={}{}", BRED, elapsed, _CustomerCount, serviceTime, totalTime, RESET);
    _expressNextArrival = randRange(1, 5);
}
void SIM::arriveNormal(int elapsed)
{
    _CustomerCount++;
    if (_CustomerCount > 24 * 60) _CustomerCount = 1;

    int waitTime = _normalServiceCountdown; //use countdown instead of 1st customer
    QUEUENODE* cur = _normalLane.getPHead();
    if (cur != nullptr) cur = cur->getPNext(); //skip first customer
    while (cur != nullptr)
    {
        waitTime += cur->getData().getServiceTime();
        cur = cur->getPNext();
    }

    ITEMLIST* items = new ITEMLIST();
    int itemCount = randRange(3, 8);
    int serviceTime = itemCount;
    for (int i = 0; i < itemCount; i++)
    {
        string item = randomItem();
        items->insertFromHead(item);
        items->itemCount++;
    }
    
    int totalTime = serviceTime + waitTime;
    _normalLane.enqueue(_CustomerCount, serviceTime, totalTime, items);
    std::println("{}[t={}] Normal lane:  Customer #{} arrived | serviceTime={} | totalTime={}{}", CYAN, elapsed, _CustomerCount, serviceTime, totalTime, RESET);
    _normalNextArrival = randRange(3, 8);
}
void SIM::processExpress(int elapsed)
{
    if (_expressLane.isEmpty()) return;

    if (_expressServiceCountdown == 0) _expressServiceCountdown = _expressLane.getPHead()->getData().getServiceTime(); //next customer
    _expressServiceCountdown--;

    if (_expressServiceCountdown == 0) //checkout
    {
        DATA d = _expressLane.dequeue();
        std::println("{}[t={}] Express lane: Customer #{} checked out | totalTime={}{}", RED, elapsed, d.getCustomerNum(), d.getTotalTime(), RESET);
    }
}
void SIM::processNormal(int elapsed)
{
    if (_normalLane.isEmpty()) return;

    if (_normalServiceCountdown == 0) _normalServiceCountdown = _normalLane.getPHead()->getData().getServiceTime(); //next customer
    _normalServiceCountdown--;

    if (_normalServiceCountdown == 0) //checkout
    {
        DATA d = _normalLane.dequeue();
        std::println("{}[t={}] Normal lane:  Customer #{} checked out | totalTime={}{}", BBLUE, elapsed, d.getCustomerNum(), d.getTotalTime(), RESET);
    }
}
void SIM::run(int minutes)
{
    std::println("Starting simulation for {} minutes.", minutes);

    minutes++;
    for (int t = 1; t < minutes; t++)
    {
        _expressNextArrival--;
        _normalNextArrival--;

        if (_expressNextArrival == 0) arriveExpress(t);

        if (_normalNextArrival == 0) arriveNormal(t);

        processExpress(t);
        processNormal(t);

        if (t % 10 == 0)
        {
            std::println("\n{}=== Queue snapshot at t={} === - - - - - - - - - -{}",GREEN, t, BRED);
            _expressLane.printQueue("Express");
            std::print("{}",CYAN);
            _normalLane.printQueue("Normal");
            std::println("{} - - - - - - - - - - - - - - - - - - - - - - - - - -{}\n",GREEN, RESET);
        }
    }

    std::println("Simulation complete.");
}
