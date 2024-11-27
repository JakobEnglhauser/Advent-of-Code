#include <iostream>
#include <array>
#include <fstream>
#include <regex>

#include "parse.h"

using solutionType = unsigned long;

constexpr unsigned long mod = 33554393;
constexpr unsigned long mult = 252533;
constexpr unsigned long base = 20151125;

std::array<solutionType, 2>
solve(std::istream &input)
{
	std::regex regex(R"(([0-9]+)[^0-9]+([0-9]+))");
	std::string line;
	getline(input, line);
	unsigned long row, col;
	regexScan(line, regex, row, col);

	unsigned long codeNum = (row * (row - 1) / 2 + 1);

	for (unsigned long c = 1; c < col; ++c) {
		codeNum += row + c;
	}

	unsigned long code{base};
	for (unsigned long i = 1; i < codeNum; ++i) {
		code = (code * mult) % mod;
	}

	return { code, 0 };
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

