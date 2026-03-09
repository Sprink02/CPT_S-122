#include <iostream>
#include <string>
#include <print>
#include <fstream>
#include <limits>

using std::string;

class Queue
{
public:
	Queue(int newSize = 0);
	~Queue();

	bool enqueue(string& newItem);
	bool dequeue(string& removedItem);

	bool isEmpty();

private:
	int mSize; // represents the number of items in the queue
	int mMaxSize; // must not exceed the max size of our allocated array
	string* mpFront; // will point to the beginning of contiguous memory on 
	// the heap (an array)
};

// Place your function definition for dequeue() below.

//  Description: Deletes the item at the front of the queue designated by index 0. A successful 
//              removal decreases mSize by 1. To delete the item, all items in the array must be shifted
//				to overwrite the item that was removed.
//				The item removed should be placed in the “removedItem” parameter.
//
// Returns: True if there was an item to remove from the contiguous memory; false otherwise.
//
// Precondition: mpFront must already point to contiguous memory; specifically 
//               item at index 0. The queue may be empty.
//
// Errors: Check that the queue is not empty; if the item cannot be removed because the queue //         is empty, then return false.

bool Queue::dequeue(string& removedIten)
{
	if (isEmpty()) return false;
	removedIten = mpFront[0];

	for (int i = 0; i < mSize - 1; i++)
	{
		mpFront[i] = mpFront[i + 1];
	}
	mSize--;

	return true;
}