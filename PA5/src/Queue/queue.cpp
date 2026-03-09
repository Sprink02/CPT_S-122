#include "queue.hpp"

DATA::DATA()
{
	_customerNumber = 0; _serviceTime = 0; _totalTime = 0;
}
DATA::DATA(int customerNum, int serviceTime, int totalTime)
{
	_customerNumber = customerNum;
	_serviceTime = serviceTime;
	_totalTime = totalTime;
}
int DATA::getCustomerNum()
{
	return _customerNumber;
}
int DATA::getServiceTime()
{
	return _serviceTime;
}
int DATA::getTotalTime()
{
	return _totalTime;
}
void DATA::setCustomerNum(int num)
{
	_customerNumber = num;
}
void DATA::setServiceTime(int num)
{
	_serviceTime = num;
}
void DATA::setTotalTime(int num)
{
	_totalTime = num;
}


ITEMNODE::ITEMNODE()
{
	_pNext = nullptr; item = "";
}
ITEMNODE::ITEMNODE(string& newItem)
{
	_pNext = nullptr; item = newItem;
}
ITEMNODE::ITEMNODE(string& newItem, ITEMNODE* nextNode)
{
	_pNext = nextNode, item = newItem;
}
ITEMNODE* ITEMNODE::getPNext()
{
	return _pNext;
}
string ITEMNODE::getItem()
{
	return item;
}
void ITEMNODE::setPNext(ITEMNODE* pNext)
{
	_pNext = pNext;
}
void ITEMNODE::setItem(string newItem)
{
	item = newItem;
}



ITEMLIST::ITEMLIST()
{
	_pHead = nullptr; itemCount = 0;
}
ITEMLIST::~ITEMLIST()
{
	ITEMNODE* pCur = this->_pHead;
	if (pCur == nullptr) return;
	while (pCur->getPNext() != nullptr)
	{
		ITEMNODE* pNext = pCur->getPNext();
		delete pCur;
		pCur = pNext;
	}
}
void ITEMLIST::insertFromHead(string& str)
{
	ITEMNODE* newNode = new ITEMNODE(str, this->_pHead);
	this->_pHead = newNode;
}
ITEMNODE* ITEMLIST::getPHead()
{
	return _pHead;
}
void ITEMLIST::setPHead(ITEMNODE* node)
{
	_pHead = node;
}



QUEUENODE::QUEUENODE()
{
	_pDATA = nullptr; _pNext = nullptr; _pItem = nullptr;
}
QUEUENODE::QUEUENODE(int customerNum, int serviceTime, int totalTime)
{
	_pDATA = new DATA(customerNum, serviceTime, totalTime); _pNext = nullptr; _pItem = nullptr;
}
QUEUENODE::QUEUENODE(int customerNum, int serviceTime, int totalTime, QUEUENODE* nextNode)
{
	_pDATA = new DATA(customerNum, serviceTime, totalTime); _pNext = nextNode; _pItem = nullptr;
}
QUEUENODE::~QUEUENODE()
{
	delete _pDATA;
}
DATA QUEUENODE::getData()
{
	return *_pDATA;
}
QUEUENODE* QUEUENODE::getPNext()
{
	return _pNext;
}
ITEMLIST* QUEUENODE::getPItem()
{
	return _pItem;
}
void QUEUENODE::setData(DATA& newData)
{
	_pDATA->setCustomerNum(newData.getCustomerNum());
	_pDATA->setServiceTime(newData.getServiceTime());
	_pDATA->setTotalTime(newData.getTotalTime());
}
void QUEUENODE::setPNext(QUEUENODE* newNode)
{
	_pNext = newNode;
}
void QUEUENODE::setPItem(ITEMLIST& list)
{
	_pItem = &list;
}



QUEUE::QUEUE()
{
	_pHead = nullptr; _pTail = nullptr;
}
QUEUE::~QUEUE()
{
	QUEUENODE* pCur = this->_pHead;
	if (pCur == nullptr) return;
	while (pCur->getPNext() != nullptr)
	{
		QUEUENODE* pNext = pCur->getPNext();
		delete pCur;
		pCur = pNext;
	}
}
bool QUEUE::enqueue(int customerNum, int serviceTime, int totalTime)
{
	QUEUENODE* newNode = new QUEUENODE(customerNum, serviceTime, totalTime);
	if (newNode == nullptr) return false;
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
bool QUEUE::enqueue(int customerNum, int serviceTime, int totalTime, ITEMLIST* itemList)
{
	QUEUENODE* newNode = new QUEUENODE(customerNum, serviceTime, totalTime);
	if (newNode == nullptr) return false;
	newNode->setPItem(*itemList);
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
DATA QUEUE::getData()
{
	return _pHead->getData();
}
ITEMLIST QUEUE::getItemList()
{
	return *(this->_pHead->getPItem());
}
DATA QUEUE::dequeue()
{
	DATA sData = this->getData();
	QUEUENODE* nextNode = _pHead->getPNext();
	delete _pHead;
	_pHead = nextNode;
	if (_pHead == nullptr) _pTail = _pHead; //final node deleted?
	return sData;
}
QUEUENODE* QUEUE::getPHead()
{
	return _pHead;
}
QUEUENODE* QUEUE::getPTail()
{
	return _pTail;
}
void QUEUE::setPHead(QUEUENODE* node)
{
	_pHead = node;
}
void QUEUE::setPTail(QUEUENODE* node)
{
	_pTail = node;
}bool QUEUE::isEmpty()
{
	return _pHead == nullptr;
}
void QUEUE::printQueue(const string& label)
{
	std::println("--- {} queue ---", label);
	QUEUENODE* cur = _pHead;
	if (cur == nullptr)
	{
		std::println("  (empty)");
		return;
	}
	while (cur != nullptr)
	{
		DATA d = cur->getData();
		std::println("  Customer #{} | serviceTime={} | totalTime={}", d.getCustomerNum(), d.getServiceTime(), d.getTotalTime());
		ITEMLIST* items = cur->getPItem();
		if (items != nullptr && items->itemCount > 0)
		{
			std::print("    Items ({}): ", items->itemCount);
			ITEMNODE* item = items->getPHead();
			while (item != nullptr)
			{
				std::print("{}", item->getItem());
				if (item->getPNext() != nullptr) std::print(", ");
				item = item->getPNext();
			}
			std::println("");
		}
		cur = cur->getPNext();
	}
}
