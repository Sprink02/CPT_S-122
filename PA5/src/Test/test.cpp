#include "test.hpp"

bool TEST::test_queue_enqueue_empty()
{
    QUEUE q;
    bool result = q.enqueue(1, 3, 3);
    assert(result == true && "enqueue on empty queue must return true");
    assert(q.getPHead() != nullptr && "head must not be null after enqueue");
    assert(q.getPHead()->getData().getCustomerNum() == 1 && "customer number must be 1");
    assert(q.getPHead()->getData().getServiceTime() == 3 && "service time must be 3");
    assert(q.getPHead()->getData().getTotalTime() == 3 && "total time must be 3");
    assert(q.getPTail() == q.getPHead() && "tail and head must point to same node when queue has one element");
    return true;
}
bool TEST::test_queue_enqueue_one()
{
    QUEUE q;
    q.enqueue(1, 2, 2);
    bool result = q.enqueue(2, 4, 6);
    assert(result == true && "enqueue must return true");
    assert(q.getPHead() != nullptr && "head must not be null");
    assert(q.getPTail() != nullptr && "tail must not be null");
    assert(q.getPHead() != q.getPTail() && "head and tail must differ with two nodes");
    assert(q.getPHead()->getData().getCustomerNum() == 1 && "head must still be customer 1");
    assert(q.getPTail()->getData().getCustomerNum() == 2 && "tail must be customer 2");
    assert(q.getPHead()->getPNext() == q.getPTail() && "head next must point to tail");
    return true;
}
bool TEST::test_queue_dequeue_one()
{
    QUEUE q;
    q.enqueue(1, 5, 5);
    DATA d = q.dequeue();
    assert(d.getCustomerNum() == 1 && "dequeued customer number must be 1");
    assert(d.getServiceTime() == 5 && "dequeued service time must be 5");
    assert(d.getTotalTime() == 5 && "dequeued total time must be 5");
    assert(q.getPHead() == nullptr && "head must be null after dequeuing only node");
    assert(q.getPTail() == nullptr && "tail must be null after dequeuing only node");
    return true;
}
bool TEST::test_queue_dequeue_two()
{
    QUEUE q;
    q.enqueue(1, 2, 2);
    q.enqueue(2, 3, 5);
    DATA d = q.dequeue();
    assert(d.getCustomerNum() == 1 && "first dequeued customer must be customer 1");
    assert(q.getPHead() != nullptr && "head must not be null with one node remaining");
    assert(q.getPHead()->getData().getCustomerNum() == 2 && "remaining head must be customer 2");
    assert(q.getPHead() == q.getPTail() && "head and tail must be equal with one node remaining");
    return true;
}
bool TEST::test_sim_24h()
{
    SIM s;
    s.run(1440);
    return true;
}
void TEST::run()
{
    clr_scr();
    bool allPassed =
        test_queue_enqueue_empty() &&
        test_queue_enqueue_one() &&
        test_queue_dequeue_one() &&
        test_queue_dequeue_two() &&
        test_sim_24h();

    if (!allPassed)
        std::println("1 or more tests FAILED!");
    else
        std::println("All tests PASSED!");
}