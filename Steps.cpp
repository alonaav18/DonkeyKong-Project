#include <fstream>

#include "Steps.h"

Steps Steps::loadSteps(const std::string& filename) {

	std::string filename_prefix = filename.substr(0, filename.find_last_of('.'));
	std::string stepsFilename = filename_prefix + ".steps";
	Steps steps;
	std::ifstream steps_file(stepsFilename);
	steps_file >> steps.randomSeed;
	size_t size;
	steps_file >> size;
	while (!steps_file.eof() && size-- != 0) {
		size_t iteration;
		char step;
		steps_file >> iteration >> step;
		steps.addStep(iteration, step);
	}
	steps_file.close();
	return steps;
}

void Steps::saveSteps(const std::string& filename) const {
	std::string filename_prefix = filename.substr(0, filename.find_last_of('.'));
	std::string stepsFilename = filename_prefix + ".steps";
	std::ofstream steps_file(stepsFilename);	// FIX CHECK IF GOOD
	steps_file << randomSeed << '\n' << steps.size();
	for (const auto& step : steps) {
		steps_file << '\n' << step.first << ' ' << step.second;
	}
	steps_file.close();
}
