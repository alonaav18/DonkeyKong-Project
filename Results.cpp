#include <limits>
#include <fstream>

#include "Results.h"

Results Results::loadResults(const std::string& filename) {
	std::string filename_prefix = filename.substr(0, filename.find_last_of('.'));
	std::string resultsFilename = filename_prefix + ".result";
	std::ifstream results_file(resultsFilename);
	Results results;
	size_t size;
	results_file >> size;
	while (!results_file.eof() && size-- != 0) {
		size_t iteration;
		int result;
		results_file >> iteration >> result;
		results.addResult(iteration, static_cast<ResultValue>(result));
	}
	return results;
}


void Results::saveResults(const std::string& filename) const {
	std::string filename_prefix = filename.substr(0, filename.find_last_of('.'));
	std::string resultsFilename = filename_prefix + ".result";
	std::ofstream results_file(resultsFilename);
	results_file << results.size();
	for (const auto& result : results) {
		results_file << '\n' << result.first << ' ' << result.second;
	}
	results_file.close();
}

//size_t Results::getNextBombIteration() const {
//	if (!results.empty() && results.front().second == hitBomb) {
//		return results.front().first;
//	}
//	else return std::numeric_limits<size_t>::max(); // a big number we will never reach
//}
