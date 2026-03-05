#pragma once
#include "./src/Fitness_App/fitness_app.hpp"

//Compiler should be set to c++ 23 or newer

int main()
{
	std::fstream fileDiet;
	fileDiet.open("./static/dietPlans.txt");
	std::fstream fileExercise;
	fileExercise.open("./static/exercisePlans.txt");
	if (!(fileDiet.is_open() && fileExercise.is_open()))
	{
		std::println("A file did not open");
		pause();
		return 0;
	}
	FitnessAppWrapper app;
	app.runApp(fileDiet, fileExercise);

	fileDiet.close();
	fileExercise.close();
	return 0;
}