#pragma once

#include <string>
#include <stack>
#include <print>

using std::string;
using std::stack;

class Data
{
private:
	int _recordNum;
	int _idNum;
	string _name;
	string _email;
	int _units;
	string _major;
	string _level;

	int _absenceNum;
	stack<string> _absenceDates;

public:
	Data();
	Data(int newRecordNum, int newIdNum, string& newName, string& newEmail, int newUnits, string& newMajor, string& newLevel);

	int get_recordNum() { return _recordNum; }
	int get_idNum() { return _idNum; }
	string get_name() { return _name; }
	string get_email() { return _email; }
	int get_units() { return _units; }
	string get_major() { return _major; }
	string get_level() { return _level; }
	int get_absenceNum() { return _absenceNum; }
	stack<string> get_absenceDates();

	void set_recordNum(const int& newRecordNum) { _recordNum = newRecordNum; }
	void set_idNum(const int& newIdNum) { _idNum = newIdNum; }
	void set_name(const string& newName) { _name = newName; }
	void set_email(const string& newEmail) { _email = newEmail; }
	void set_units(const int& newUnits) { _units = newUnits; }
	void set_major(const string& newMajor) { _major = newMajor; }
	void set_level(const string& newLevel) { _level = newLevel; }
	void set_absenceNum(const int& newAbsenceNum) { _absenceNum = newAbsenceNum; }

	void add_absence(const string& newDate);
	void remove_absence(const std::string& date);

	string get_absence_recent() const;



};

Data::Data() :
	_recordNum(0), _idNum(0), _name(""), _email(""),
	_units(0), _major(""), _level(""), _absenceNum(0), _absenceDates() {
}
Data::Data(int newRecordNum, int newIdNum, string& newName, string& newEmail, int newUnits, string& newMajor, string& newLevel) :
	_recordNum(newRecordNum), _idNum(newIdNum), _name(newName), _email(newEmail), _units(newUnits), _major(newMajor), _level(newLevel),
	_absenceNum(0), _absenceDates() {}

void Data::add_absence(const string& newDate)
{
	_absenceDates.push(newDate); _absenceNum++;
}
stack<string> Data::get_absenceDates()
{
	return _absenceDates;
}
void Data::remove_absence(const std::string& date)
{
	stack<string> temp;
	bool removed = false;

	while (!_absenceDates.empty())
	{
		string top = _absenceDates.top();
		_absenceDates.pop();
		if (!removed && top == date) { removed = true; }
		else { temp.push(top); }
		_absenceNum--;
	}

	// Re-reverse temp to restore original LIFO order
	stack<string> restored;
	while (!temp.empty()) { restored.push(temp.top()); temp.pop(); }

	_absenceDates = restored;
	if (removed) _absenceNum--;
}
string Data::get_absence_recent() const
{
	return _absenceDates.empty() ? "N/A" : _absenceDates.top();
}