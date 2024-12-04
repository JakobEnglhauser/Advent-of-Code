#include <iostream>
#include <array>
#include <fstream>

#include "parse.h"

using solutionType = unsigned int;

std::array<solutionType, 2>
solve(std::istream &input)
{
	std::array<solutionType, 2> sum{0};
	std::string fullInput = "";
	std::string line;
	while (input) {
		getline(input, line);
		if (line.empty()) {
			break;
		}
		fullInput += line;
	}

	std::regex regex(R"(mul\(([0-9]+),([0-9]+)\))");
	std::regex dont(R"(don't\(\).*?do\(\))");
	std::array<std::vector<unsigned int>, 2> muls{};
	regexScan(fullInput, regex, muls[0]);
	fullInput = std::regex_replace(fullInput, dont, "");
	regexScan(fullInput, regex, muls[1]);

	for (size_t i = 0; i < muls[0].size(); i += 2) {
		sum[0] += muls[0][i] * muls[0][i + 1];
	}
	for (size_t i = 0; i < muls[1].size(); i += 2) {
		sum[1] += muls[1][i] * muls[1][i + 1];
	}
	return sum;
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

