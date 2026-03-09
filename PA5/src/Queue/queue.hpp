#pragma once
#include <string>
#include <print>
#include <limits>
#include <time.h>

using std::string;

class DATA
{
private:
	int _customerNumber;
	int _serviceTime;
	int _totalTime;

public:
	DATA();
	DATA(int customerNum, int serviceTime, int totalTime);
	int getCustomerNum();
	int getServiceTime();
	int getTotalTime();
	void setCustomerNum(int num);
	void setServiceTime(int num);
	void setTotalTime(int num);
};



class ITEMNODE
{
private:
	ITEMNODE* _pNext;
	string item;
public:
	ITEMNODE();
	ITEMNODE(string& newItem);
	ITEMNODE(string& newItem, ITEMNODE* nextNode);
	ITEMNODE* getPNext();
	string getItem();
	void setPNext(ITEMNODE* pNext);
	void setItem(string newItem);
};
class ITEMLIST
{
private:
	ITEMNODE* _pHead;
public:
	int itemCount;
	ITEMLIST();
	~ITEMLIST();
	void insertFromHead(string& str);
	ITEMNODE* getPHead();
	void setPHead(ITEMNODE* node);
};




class QUEUENODE
{
private:
	DATA* _pDATA;
	QUEUENODE* _pNext;
	ITEMLIST* _pItem;
public:
	QUEUENODE();
	QUEUENODE(int customerNum, int serviceTime, int totalTime);
	QUEUENODE(int customerNum, int serviceTime, int totalTime, QUEUENODE* nextNode);
	~QUEUENODE();
	DATA getData();
	QUEUENODE* getPNext();
	ITEMLIST* getPItem();
	void setData(DATA& newData);
	void setPNext(QUEUENODE* newNode);
	void setPItem(ITEMLIST& list);
};
class QUEUE
{
private:
	QUEUENODE* _pHead;
	QUEUENODE* _pTail;

public:
	QUEUE();
	~QUEUE();
	bool enqueue(int customerNum, int serviceTime, int totalTime);
	bool enqueue(int customerNum, int serviceTime, int totalTime, ITEMLIST* itemList);
	DATA getData();
	ITEMLIST getItemList();
	DATA dequeue();
	QUEUENODE* getPHead();
	QUEUENODE* getPTail();
	void setPHead(QUEUENODE* node);
	void setPTail(QUEUENODE* node);
	bool isEmpty();
	void printQueue(const string& label);
};