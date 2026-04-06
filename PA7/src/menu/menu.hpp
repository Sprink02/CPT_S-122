#pragma once

#include <print>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../list/list.hpp" //should include node.hpp and data.hpp

using std::string;

#define PASS {}

//std clearscreen
inline void clr_scr()
{
	std::cout << "\x1B[2J\x1B[0;0H";
}

//std pause Wait for \n
inline void pause()
{
	std::print("Press ENTER to continue");
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

//choice_limit
inline bool choice_limit(const int& val, const int min, const int& max)
{
	return (val >= min) && (val <= max);
}


class Menu
{
private:
	List<Data> _list;
	string get_current_date() const;
	void display_menu();
	void read_list();
	void load_master();
	void store_master();
	void mark_absences();
	void edit_absences();
	void gen_report();

	void report_all();
	void report_thresh();

public:
	Menu() : _list() {}
	void run();

};
// Derives the current date from the system clock
string Menu::get_current_date() const
{
	/*
	adapted from https://en.cppreference.com/w/c/chrono/localtime
	and https://en.cppreference.com/w/c/chrono/asctime
	*/
	time_t t = time(NULL);
	struct tm now;
	localtime_s(&now, &t);

	char str[26];
	localtime_s(&now, &t);
	asctime_s(str, sizeof str, &now);
	return str;
}

void Menu::display_menu()
{
	std::println("{0}\n{1}\n{2}\n{3}\n{4}\n{5}\n{6}\n\nChoice: ",
		"1. Import Course List",
		"2. Load Master List",
		"3. Store Master List",
		"4. Mark Absences",
		"5. Edit Absences",
		"6. Generate Report",
		"7. Exit");
}
void Menu::read_list()
{
	clr_scr();
	_list.destroy_list();
	std::ifstream inFile("./statics/classList.csv");
	if (!inFile.is_open())
	{
		std::println("Error: Could not open classList.csv");
		pause();
		return;
	}
	string ln;
	std::getline(inFile, ln);

	int count = 0;
	while (std::getline(inFile, ln))
	{
		if (ln.empty()) continue;

		std::stringstream ss(ln);
		string token;

		string recNumStr, idStr, name, email, unitsStr, major, level;

		std::getline(ss, recNumStr, ',');
		std::getline(ss, idStr, ',');
		std::getline(ss, name, ',');
		std::getline(ss, email, ',');
		std::getline(ss, unitsStr, ',');
		std::getline(ss, major, ',');
		std::getline(ss, level, ',');

		int recNum = 0, idNum = 0, units = 0;
		try { recNum = std::stoi(recNumStr); }
		catch (...) {}
		try { idNum = std::stoi(idStr); }
		catch (...) {}
		try { units = (unitsStr == "AU") ? -1 : std::stoi(unitsStr); }
		catch (...) {}

		Data student(recNum, idNum, name, email, units, major, level);

		// Insert at front – O(1)
		_list.insert_at_front(student);
		count++;
	}

	inFile.close();
	std::println("Imported {} records from classList", count);
	pause();	
}
void Menu::load_master()
{
	clr_scr();
	_list.destroy_list();

	std::ifstream inFile("./statics/master.csv");
	if (!inFile.is_open())
	{
		std::println("Error: Could not open master.csv");
		pause();
		return;
	}

	string ln;
	// Skip header
	std::getline(inFile, ln);

	int count = 0;
	while (std::getline(inFile, ln))
	{
		if (ln.empty()) continue;

		std::stringstream ss(ln);
		std::string recNumStr, idStr, name, email, unitsStr, major, level,
			numAbsStr, datesStr;

		std::getline(ss, recNumStr, ',');
		std::getline(ss, idStr, ',');
		std::getline(ss, name, ',');
		std::getline(ss, email, ',');
		std::getline(ss, unitsStr, ',');
		std::getline(ss, major, ',');
		std::getline(ss, level, ',');
		std::getline(ss, numAbsStr, ',');
		std::getline(ss, datesStr);

		int recNum = 0, idNum = 0, units = 0;
		try { recNum = std::stoi(recNumStr); }
		catch (...) {}
		try { idNum = std::stoi(idStr); }
		catch (...) {}
		try { units = (unitsStr == "AU") ? -1 : std::stoi(unitsStr); }
		catch (...) {}

		Data student(recNum, idNum, name, email, units, major, level);

		// Restore absence dates (stored oldest-first so stack top = most recent)
		// Dates saved as: date1|date2|date3 (oldest first)
		if (!datesStr.empty())
		{
			std::stringstream ds(datesStr);
			string date;
			while (std::getline(ds, date, '|'))
			{
				if (!date.empty())
					student.add_absence(date);
			}
		}

		_list.insert_at_front(student);
		count++;
	}

	inFile.close();
	std::cout << "Loaded " << count << " records from master.csv\n";
	pause();
}
void Menu::store_master()
{
	clr_scr();
	std::ofstream outFile("./statics/master.csv");
	if (!outFile.is_open())
	{
		std::println("Error: Could not open master.csv for writing");
		return;
	}

	// Write header
	outFile << "RecNum,ID,Name,Email,Units,Program,Level,NumAbsences,Dates\n";

	Node<Data>* pCur = _list.get_pHead();
	while (pCur != nullptr)
	{
		Data& d = pCur->get_data_ref();

		outFile << d.get_recordNum() << ","
			<< d.get_idNum() << ","
			<< d.get_name() << ","
			<< d.get_email() << ","
			<< d.get_units() << ","
			<< d.get_major() << ","
			<< d.get_level() << ","
			<< d.get_absenceNum() << ",";

		// Write absence dates oldest-first (invert stack copy)
		stack<string> stackCopy = d.get_absenceDates();
		stack<string> reversed;
		while (!stackCopy.empty())
		{
			reversed.push(stackCopy.top());
			stackCopy.pop();
		}
		bool first = true;
		while (!reversed.empty())
		{
			if (!first) outFile << "|";
			outFile << reversed.top();
			reversed.pop();
			first = false;
		}

		outFile << "\n";
		pCur = pCur->get_pNext();
	}

	outFile.close();
	std::println("Master list stored to master.csv");
	pause();
}
void Menu::mark_absences()
{
	clr_scr();
	if (_list.is_empty())
	{
		std::println("Master list is empty. Import or load records first.");
		return;
	}

	string today = get_current_date();
	std::print("Marking absences for: {}\n\n", today);

	Node<Data>* pCur = _list.get_pHead();
	while (pCur != nullptr)
	{
		Data& student = pCur->get_data_ref();
		char answer = ' ';

		std::print("Is {} absent? (y/n): ", student.get_name());
		std::cin >> answer;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //weird ignore stuff

		if (answer == 'y' || answer == 'Y')
		{
			student.add_absence(today);
			std::println("  Absence recorded.");
		}

		pCur = pCur->get_pNext();
	}

	std::println("Absences marked for today.");
	pause();
}
void Menu::edit_absences() //utter pain
{
	clr_scr();
	if (_list.is_empty())
	{
		std::println("Master list is empty.");
		return;
	}

	std::print("Search by (1) ID or (2) Name? ");
	int choice = 0;
	std::cin >> choice;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	string searchTerm;
	if (choice == 1)
	{
		std::print("Enter student ID: ");
	}
	else
	{
		std::print("Enter student name: ");
	}
	std::getline(std::cin, searchTerm);

	// Linear search through master list
	Node<Data>* pCur = _list.get_pHead();
	Node<Data>* pFound = nullptr;

	while (pCur != nullptr)
	{
		Data& d = pCur->get_data_ref();
		bool match = (choice == 1)
			? (std::to_string(d.get_idNum()) == searchTerm)
			: (d.get_name() == searchTerm);
		if (match)
		{
			pFound = pCur;
			break;
		}
		pCur = pCur->get_pNext();
	}

	if (pFound == nullptr)
	{
		std::println("Student not found.");
		pause();
		return;
	}

	Data& student = pFound->get_data_ref();
	std::println("Found: {0} | Absences: {1}", student.get_name(), student.get_absenceNum());

	// Show all absence dates (copy the stack, print without destroying)
	stack<string> stackCopy = student.get_absenceDates();
	if (stackCopy.empty())
	{
		std::println("No absences recorded.");
		pause();
		return;
	}

	std::println("Recorded absence dates (most recent first):");
	int idx = 1;
	while (!stackCopy.empty())
	{
		std::println("  {}. {}", idx++, stackCopy.top());
		stackCopy.pop();
	}

	std::print("Enter the date to remove (YYYY-MM-DD) or 'cancel': ");
	string dateToRemove;
	std::getline(std::cin, dateToRemove);

	if (dateToRemove == "cancel") return;

	student.remove_absence(dateToRemove);
	std::print("Absence for {} removed (if it existed).\nUpdated absence count: {}\n", dateToRemove, student.get_absenceNum());
	pause();
}
void Menu::gen_report()
{
	clr_scr();
	int choice = 0;
	do
	{
		std::print("1. All Students\n2. Threshold\nChoice: ");
		std::cin >> choice;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (!choice_limit(choice, 1, 2))
			std::println("Invalid sub - menu choice.");
	} while (!choice_limit(choice, 1, 2));

	switch (choice)
	{
	case 1: report_all();  break;
	case 2: report_thresh();  break;
	default: break;
	}
	pause();
}

void Menu::report_all()
{
	clr_scr();
	std::ofstream outFile("report_all.txt");
	if (!outFile.is_open())
	{
		std::println("Error: Could not create report_all.txt");
		return;
	}

	outFile << "Attendance Report – All Students\n"
		<< "Generated: " << get_current_date() << "\n"
		<< std::string(50, '-') << "\n"
		<< "Name                         | Absences | Most Recent\n"
		<< std::string(50, '-') << "\n";

	Node<Data>* pCur = _list.get_pHead();
	while (pCur != nullptr)
	{
		Data& d = pCur->get_data_ref();

		outFile << d.get_name() << " | "
			<< d.get_absenceNum() << "       | "
			<< d.get_absence_recent() << "\n";  // peek()

		pCur = pCur->get_pNext();
	}

	outFile.close();
	std::println("Report written to report_all.txt");
}
void Menu::report_thresh()
{
	clr_scr();
	int threshold = 0;
	std::print("Enter absence threshold: ");
	std::cin >> threshold;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::ofstream outFile("report_threshold.txt");
	if (!outFile.is_open())
	{
		std::println("Error: Could not create report_threshold.txt");
		return;
	}

	outFile << "Attendance Report – Absences >= " << threshold << "\n"
		<< "Generated: " << get_current_date() << "\n"
		<< std::string(40, '-') << "\n";

	Node<Data>* pCur = _list.get_pHead();
	while (pCur != nullptr)
	{
		Data& d = pCur->get_data_ref();

		if (d.get_absenceNum() >= threshold)
		{
			outFile << d.get_name() << "\n";
		}

		pCur = pCur->get_pNext();
	}

	outFile.close();
	std::println("Report written to report_threshold.txt");
}





void Menu::run()
{
	int choice = 0;
	while (choice != 7)
	{
		do
		{
			clr_scr();
			display_menu();
			std::cin >> choice;
		} while (!choice_limit(choice, 1, 7));
		pause();
		switch (choice)
		{
		case 1: read_list(); break;
		case 2: load_master(); break;
		case 3: store_master(); break;
		case 4: mark_absences(); break;
		case 5: edit_absences(); break;
		case 6: gen_report(); break;
		case 7: return; break; //nte: this does not save anything?
		default: std::print("Error: Menu::run() >> switch (choice) default"); return; break; //should never happen :)
		}
		clr_scr();
	}
}