#include <iostream>
#include <print>
#include <cassert>

using std::string;

class QueueNode
{
public:
	QueueNode();
	QueueNode(string str);
	void setStr(string str);
	string getStr();
	void setPNext(QueueNode* next);
	QueueNode* getPNext();

private:
	string _str;
	QueueNode* _pNext;
};
QueueNode::QueueNode()
{
	_str = "";
}
QueueNode::QueueNode(string str)
{
	_str = str;
}
void QueueNode::setStr(string str)
{
	_str = str;
}
string QueueNode::getStr()
{
	return _str;
}
void QueueNode::setPNext(QueueNode* next)
{
	_pNext = next;
}
QueueNode* QueueNode::getPNext()
{
	return _pNext;
}



class Queue
{
public:
	Queue();
	~Queue();
	bool isempty();
	bool enqueue(string str);
	string dequeue();
	void destroyqueue();
	void printQueueRecursive();
	void printQueueRecursive(QueueNode* pCur,int curSize);


private:
	QueueNode* _pHead;
	QueueNode* _pTail;
	int _size;
};
Queue::Queue()
{
	_pHead = nullptr; _pTail = nullptr; _size=0;
}
Queue::~Queue()
{
	destroyqueue();
}
bool Queue::isempty()
{
	return _size == 0 ? true : false;
}
bool Queue::enqueue(string str)
{
	QueueNode* newNode = new QueueNode(str);
	if (newNode == nullptr) return false;
	_size++;
	if (_pHead == nullptr)
	{
		_pHead = newNode;
		_pTail = newNode;
	}
	else
	{
		_pTail->setPNext(newNode);
		_pTail = newNode;
	}
	return true;
}
string Queue::dequeue()
{
	string str = _pHead->getStr();
	QueueNode* nextNode = _pHead->getPNext();
	delete _pHead;
	_pHead = nextNode;
	if (_pHead == nullptr) _pTail = _pHead; //final node deleted?
	_size--;
	return str;
}
void Queue::destroyqueue()
{
	QueueNode* pCur = this->_pHead;
	if (pCur == nullptr) return;
	while (pCur->getPNext() != nullptr)
	{
		QueueNode* pNext = pCur->getPNext();
		delete pCur;
		pCur = pNext;
	}
	_pHead = _pTail = nullptr; _size = 0;
}
void Queue::printQueueRecursive()
{
	printQueueRecursive(_pHead, _size);
}
void Queue::printQueueRecursive(QueueNode* pCur, int curSize)
{
	std::println("{}", pCur->getStr());
	if (curSize - 1 == 0) return;
	printQueueRecursive(pCur->getPNext(), --curSize);
}



class test
{
public:
	void runApp()
	{
		if (test_enqueue() && test_dequeue() && test_destroyqueue() && test_printQueueRecursive()) std::println("\nYou good");
	}
	bool test_enqueue()
	{
		q.enqueue("new");
		assert(q.isempty() == false && "queue must not be empty");

		q.destroyqueue();
		return true;
	}
	bool test_dequeue()
	{
		q.enqueue("new");
		assert("new" == q.dequeue() && "new doesn't = new");
		assert(q.isempty() == true && "queue must be empty");
		return true;
	}
	bool test_destroyqueue()
	{
		q.enqueue("new");
		q.enqueue("new2");

		q.destroyqueue();
		assert(q.isempty() == true && "queue must be empty");
		return true;
	}
	bool test_printQueueRecursive()
	{
		q.enqueue("hello");
		q.enqueue("world");
		assert(q.isempty() == false && "queue must not be empty");
		q.printQueueRecursive();

		q.destroyqueue();
		return true;
	}
private:
	Queue q;
};


int main()
{
	test t;
	t.runApp();
	return 0;
}