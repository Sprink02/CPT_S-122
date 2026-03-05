#pragma once
#include "./src/Diet/diet.hpp"
#include "./src/Exercise/exercise.hpp"

//Compiler should be set to c++ 23 or newer

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

class FitnessAppWrapper
{
public:
	LIST_E exerciseList;
	LIST_D dietList;


	void runApp(std::fstream& fileDiet, std::fstream& fileExercise)
	{
		char u_cin = 0;
		while (u_cin != 9) 
		{
			while (u_cin < '1' || u_cin > '9') //basic error check
			{
				clr_scr();
				this->displayMenu();
				std::cin >> u_cin;
				std::cin.ignore(255, '\n');
			}
			switch (u_cin)
			{
			case '1': loadWeeklyPlan(fileDiet, this->dietList); break;
			case '2': loadWeeklyPlan(fileExercise, this->exerciseList); break;
			case '3': storeWeeklyPlan(fileDiet, this->dietList); break;
			case '4': storeWeeklyPlan(fileExercise, this->exerciseList); break;
			case '5': displayWeeklyPlan(this->dietList); break;
			case '6': displayWeeklyPlan(this->exerciseList); break;
			case '7': editDailyPlan(this->dietList); break;
			case '8': editDailyPlan(this->exerciseList); break;
			case '9': exit(fileDiet, this->dietList, fileExercise, this->exerciseList); return; break;
			default: break;
			}
			u_cin = 0;
			clr_scr();
		}
	}

	void displayMenu()
	{
		std::println("1. Load weekly diet plan from file\n2. Load weekly exercise plan from file\n3. Store weekly diet plan to file\n4. Store weekly exercise plan to file\n5. Display weekly diet plan to screen\n6. Display weekly exercise plan to screen\n7. Edit daily diet plan\n8. Edit daily exercise plan\n9. Exit");
	}

private:
	//Loads
	void loadDailyPlan(std::fstream& fileStream, DIET& plan)
	{
		if (fileStream.eof()) return;
		fileStream >> plan;
		return;
	}
	void loadWeeklyPlan(std::fstream& fileStream, LIST_D& plan)
	{
		for (int i = 0; i < 7; i++)
		{
			DIET newDiet;
			loadDailyPlan(fileStream, newDiet);
			plan.insert_at_tail(newDiet);
		}
		std::println("loaded weekly plan");
		pause();
		return;
	}
	void loadDailyPlan(std::fstream& fileStream, EXERCISE& plan)
	{
		if (fileStream.eof()) return;
		fileStream >> plan;
		return;
	}
	void loadWeeklyPlan(std::fstream& fileStream, LIST_E& plan)
	{
		for (int i = 0; i < 7; i++)
		{
			EXERCISE newExercise;
			loadDailyPlan(fileStream, newExercise);
			plan.insert_at_tail(newExercise);
		}
		std::println("loaded weekly plan");
		pause();
		return;
	}

	//Stores
	//WAL: Fix stores for writing to a file, try to not have to make a new filestream
	void storeDailyPlan(std::fstream& fileStream, DIET& plan)
	{
		fileStream << plan;
		return;
	}
	void storeWeeklyPlan(std::fstream& fileStream, LIST_D& plan)
	{
		fileStream.clear(); //remove EOF flags
		fileStream.seekp(0); //make sure at beggining of file
		for (int i = 0; i < 7; i++)
		{
			DIET* p = plan.get_at_index(i);
			if (p) storeDailyPlan(fileStream, *p); //null guard
		}
		std::println("stored weekly plan");
		pause();
		return;
	}
	void storeDailyPlan(std::fstream& fileStream, EXERCISE& plan)
	{
		fileStream << plan;
		return;
	}
	void storeWeeklyPlan(std::fstream& fileStream, LIST_E& plan)
	{
		fileStream.clear(); //remove EOF flags
		fileStream.seekp(0); //make sure at beggining of file
		for (int i = 0; i < 7; i++)
		{
			EXERCISE* p = plan.get_at_index(i);
			if (p) storeDailyPlan(fileStream, *p); //null guard
		}
		std::println("stored weekly plan");
		pause();
		return;
	}

	//display
	void displayDailyPlan(DIET& plan)
	{
		std::cout << plan;
		return;
	}
	void displayWeeklyPlan(LIST_D& plan)
	{
		clr_scr();
		for (int i = 0; i < 7; i++)
		{
			DIET* p = plan.get_at_index(i);
			if (p) displayDailyPlan(*p); //null guard
		}
		pause();
		return;
	}
	void displayDailyPlan(EXERCISE& plan)
	{
		std::cout << plan;
		return;
	}
	void displayWeeklyPlan(LIST_E& plan)
	{
		clr_scr();
		for (int i = 0; i < 7; i++)
		{
			EXERCISE* p = plan.get_at_index(i);
			if (p) displayDailyPlan(*p); //null guard
		}
		pause();
		return;
	}

	//Edit
	void editDailyPlan(LIST_D& plan)
	{
		char u_cin = 0;
		while (u_cin < '1' || u_cin > '7') //basic error check
		{
			clr_scr();
			std::println("Give # of day to edit 1-7");
			std::cin >> u_cin;
			std::cin.ignore(255, '\n');
		}
		int index = u_cin - '1'; u_cin = 0;
		plan.get_at_index(index)->editGoal();
		return;
	}
	void editDailyPlan(LIST_E& plan)
	{
		char u_cin = 0;
		while (u_cin < '1' || u_cin > '7') //basic error check
		{
			clr_scr();
			std::println("Give # of day to edit 1-7");
			std::cin >> u_cin;
			std::cin.ignore(255, '\n');
		}
		int index = u_cin - '1'; u_cin = 0;
		plan.get_at_index(index)->editGoal();
		return;
	}

	void exit(std::fstream& dietFile, LIST_D& dietPlan, std::fstream& exerciseFile, LIST_E& exercisePlan)
	{
		std::println("exiting program");
		//Reset write cursors to start of file before storing
		dietFile.seekp(0);
		exerciseFile.seekp(0);
		storeWeeklyPlan(dietFile, dietPlan);
		storeWeeklyPlan(exerciseFile, exercisePlan);
		clr_scr();
		std::println("exited program successfully");
		return;
	}
};