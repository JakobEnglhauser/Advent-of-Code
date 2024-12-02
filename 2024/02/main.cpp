#include <iostream>
#include <array>
#include <fstream>
#include <algorithm>

#include "util.h"

using solutionType = unsigned int;

bool
isSafe(std::vector<int> const &levels)
{
	int sign = levels[1] - levels[0] < 0 ? -1 : 1;
	for (std::size_t i{0}, j{1}; j < levels.size(); ++i, ++j) {
		auto d = (levels[j] - levels[i]) * sign;
		if (d < 1 or d > 3) {
			return false;
		}
	}
	return true;
}

std::array<solutionType, 2>
solve(std::istream &input)
{
	std::array<solutionType, 2> count{0};
	std::string line;
	while (input) {
		getline(input, line);
		if (line.empty()) {
			break;
		}
		auto levels = toInts<int>(line);

		count[0] += isSafe(levels) ? 1 : 0;

		std::vector<int> reduced(levels.size() - 1);
		for (auto it = levels.begin(); it != levels.end(); ++it) {
			auto tmp = std::copy(levels.begin(), it, reduced.begin());
			std::copy(it + 1, levels.end(), tmp);
			if (isSafe(reduced)) {
				count[1] += 1;
				break;
			}
		}
	}
	return count;
}

int
main(int argc, char **argv)
{
	std::array<solutionType, 2> solution;
	if (argc > 1) {
		std::ifstream file(argv[1]);
		solution = solve(file);
	} else {
		solution = solve(std::cin);
	}
	std::cout << solution[0] << "\n" << solution[1] << std::endl;
	return 0;
}

