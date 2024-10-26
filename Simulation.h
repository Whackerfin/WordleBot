#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

class Simulation {
public:
	Simulation();
	void StartSimulation();
	std::vector<std::string> answers;
private:
	std::vector<std::string> GetAnswers();
};