#pragma once

#include <list>

class Results {
public:
	enum ResultValue { died, finished, score, noResult};
private:
	std::list<std::pair<size_t, ResultValue>> results; // pair: iteration, result
public:
	static Results loadResults(const std::string& filename);
	void saveResults(const std::string& filename) const;
	void addResult(size_t iteration, ResultValue result) {
		results.push_back({ iteration, result });
	}

	std::pair<size_t, ResultValue> popResult() {
		if (results.empty()) return { 0, Results::noResult };
		auto result = results.front();
		results.pop_front();
		return result;
	}

	bool cmp(size_t iteration, ResultValue result) {
		if (results.empty()) return false;
		auto result_ = popResult();
		return result_.first == iteration && result_.second == result;
	}

	bool isFinishedBy(size_t iteration) const {
		return results.empty() || results.back().first <= iteration;
	}
	void clrResults() {results.clear();}
	//size_t getNextBombIteration() const;
};
