#pragma once
#include <iostream>
#include <string>
#include <print>
#include <fstream>
#include <limits>

using std::string;

class DIET
{
private:
	string _planName;
	int _planGoal;
	string _planDate;

public:

	//Class operators
	DIET()
	{
		_planName = "";
		_planGoal = 0;
		_planDate = "";
	}
	DIET(string Name, int Goal, string Date)
	{
		_planName = Name;
		_planGoal = Goal;
		_planDate = Date;
	}
    ~DIET()
    {
		std::println("In Plan Destructor, Destructed object");
    }
	DIET(const DIET& oldPlan)
	{
		_planName = oldPlan._planName;
		_planGoal = oldPlan._planGoal;
		_planDate = oldPlan._planDate;
	}
	friend std::ostream& operator<<(std::ostream& out, const DIET& d) //screen overload
	{
		out << "Plan Name: " << d._planName << "\nPlan Goal: " << d._planGoal << "\nPlan Date: " << d._planDate << "\n";
		return out;
	}
	friend std::fstream& operator<<(std::fstream& out, const DIET& d) //file overload
	{
		out << d._planName << '\n' << d._planGoal << '\n' << d._planDate << '\n' << '\n';
		return out;
	}

	//setters and getters
	int set_planName(string newPlanName)
	{
		this->_planName = newPlanName;
		return 1;
	}
	int set_planGoal(int newPlanGoal)
	{
		this->_planGoal = newPlanGoal;
		return 1;
	}
	int set_planDate(string newPlanDate)
	{
		this->_planDate = newPlanDate;
		return 1;
	}

	string get_planName()
	{
		return (string)this->_planName;
	}
	int get_planGoal()
	{
		return (int)this->_planGoal;
	}
	string get_planDate()
	{
		return (string)this->_planDate;
	}
	
};

class LISTNODE_D
{
public:
	DIET _data;
	LISTNODE_D* _pNext;
	LISTNODE_D(DIET& newDiet)
	{
		_data = newDiet;
		_pNext = NULL;
	}
	LISTNODE_D()
	{
		//tbh don't know why a null constructor does not work here but this works
		_data.set_planName("");
		_data.set_planGoal(0);
		_data.set_planDate("");
		_pNext = NULL;
	}
};

class LIST_D
{
public:
	LISTNODE_D* _pHead;
	LISTNODE_D* _pTail;

	LIST_D()
	{
		_pHead = NULL;
		_pTail = NULL;
	}

	void insert_at_tail(DIET& newDiet)
	{
		LISTNODE_D* newNode = new LISTNODE_D(newDiet);

		if (_pHead == NULL) // Empty list
		{
			_pHead = newNode;
			_pTail = newNode;
			return;
		}

		_pTail->_pNext = newNode;
		_pTail = newNode;
		return;
	}

	DIET delete_from_head()
	{
		DIET copy;
		if (_pHead == NULL) // Empty list
			return copy;

		LISTNODE_D* temp = _pHead;
		copy = temp->_data;
		_pHead = _pHead->_pNext;

		if (_pHead == NULL) // List is now empty
			_pTail = NULL;

		delete temp;
		return copy;
	}

	DIET* get_at_index(int index)
	{
		if (_pHead == NULL || index < 0)
			return NULL;

		LISTNODE_D* current = _pHead;
		int i = 0;

		while (current != NULL)
		{
			if (i == index)
				return &current->_data;

			current = current->_pNext;
			i++;
		}

		return NULL; // Index out of bounds
	}


};

std::fstream& operator>>(std::fstream& fileStream, DIET& diet)
{
	string name, date;
	int goal;

    while (std::getline(fileStream, name)) {
        if (!name.empty()) break;
    }
    if (fileStream.eof() && name.empty()) return fileStream;

    if (!(fileStream >> goal)) return fileStream;
    fileStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // consume rest of line

    std::getline(fileStream, date);

    diet.set_planName(name);
    diet.set_planGoal(goal);
    diet.set_planDate(date);

    return fileStream;
}