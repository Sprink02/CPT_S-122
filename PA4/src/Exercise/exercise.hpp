#pragma once
#include <iostream>
#include <string>
#include <print>
#include <fstream>
#include <limits>

using std::string;

class EXERCISE
{
private:
	string _planName;
	int _planGoal;
	string _planDate;

public:

	//Class operators
	EXERCISE()
	{
		_planName = "";
		_planGoal = 0;
		_planDate = "";
	}
	EXERCISE(string Name, int Goal, string Date)
	{
		_planName = Name;
		_planGoal = Goal;
		_planDate = Date;
	}
    ~EXERCISE()
    {
		std::println("In Plan Destructor, Destructed object");
    }
	EXERCISE(const EXERCISE& oldPlan)
	{
		_planName = oldPlan._planName;
		_planGoal = oldPlan._planGoal;
		_planDate = oldPlan._planDate;
	}
	friend std::ostream& operator<<(std::ostream& out, const EXERCISE& d) //screen overload
	{
		out << "Plan Name: " << d._planName << "\nPlan Goal: " << d._planGoal << "\nPlan Date: " << d._planDate << "\n";
		return out;
	}
	friend std::fstream& operator<<(std::fstream& out, const EXERCISE& d) //file overload
	{
		out << d._planName << "\n" << d._planGoal << "\n" << d._planDate << "\n\n";
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

class LISTNODE_E
{
public:
	EXERCISE _data;
	LISTNODE_E* _pNext;
	LISTNODE_E(EXERCISE& newExercise)
	{
		_data = newExercise;
		_pNext = NULL;
	}
	LISTNODE_E()
	{
		//tbh don't know why a null constructor does not work here but this works
		_data.set_planName("");
		_data.set_planGoal(0);
		_data.set_planDate("");
		_pNext = NULL;
	}
};

class LIST_E
{
public:
	LISTNODE_E* _pHead;
	LISTNODE_E* _pTail;

	LIST_E()
	{
		_pHead = NULL;
		_pTail = NULL;
	}

	void insert_at_tail(EXERCISE& newExercise)
	{
		LISTNODE_E* newNode = new LISTNODE_E(newExercise);

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

	EXERCISE delete_from_head()
	{
		EXERCISE copy;
		if (_pHead == NULL) // Empty list
			return copy;

		LISTNODE_E* temp = _pHead;
		copy = temp->_data;
		_pHead = _pHead->_pNext;

		if (_pHead == NULL) // List is now empty
			_pTail = NULL;

		delete temp;
		return copy;
	}

	EXERCISE* get_at_index(int index)
	{
		if (_pHead == NULL || index < 0)
			return NULL;

		LISTNODE_E* current = _pHead;
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

std::istream& operator>>(std::istream& fileStream, EXERCISE& exercise)
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

    exercise.set_planName(name);
    exercise.set_planGoal(goal);
    exercise.set_planDate(date);

    return fileStream;
}

