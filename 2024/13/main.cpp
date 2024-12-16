#include <iostream>
#include <array>
#include <fstream>
#include <utility>
#include <vector>

#include "parse.h"

using solutionType = long;

long
determinant(std::array<long, 2> const &a, std::array<long, 2> const &b)
{
	return a[0] * b[1] - a[1] * b[0];
}

/**
 * Find the required button presses to reach prize, when
 * button A moves the claw by a and button B moves the claw by b.
 * 
 * Mathematically this means:
 * Solve the equation Ax = P
 * where A = (a b) in N^2x2, P = prize in N^2
 * for x in N^2
 * 
 * Returns (3 1) * x
 */
solutionType
solve(std::array<long, 2> const &a, std::array<long, 2> const &b,
	  std::array<long, 2> const &prize)
{
	auto detAB = determinant(a, b);
	auto detA = determinant(prize, b);
	auto detB = determinant(a, prize);
	auto x = detA / detAB;
	auto y = detB / detAB;
	if (detA % detAB != 0 or detB % detAB != 0 or x < 0 or y < 0) {
		return 0;
	}
	return 3 * x + y;
}

std::array<solutionType, 2>
solve(std::istream &input)
{
	std::array<solutionType, 2> sum{0};
	std::regex regex(R"(([0-9]+)[^0-9]+([0-9]+))");
	std::vector<std::array<long, 2>> equations;
	std::string line;
	while (input) {
		getline(input, line);
		if (line.empty()) {
			continue;
		}
		long x, y;
		regexScan(line, regex, x, y);
		equations.push_back({x, y});
	}
	for (size_t i = 0; i < equations.size(); i += 3) {
		sum[0] += solve(equations[i], equations[i + 1], equations[i + 2]);
		equations[i + 2][0] += 1e13;
		equations[i + 2][1] += 1e13;
		sum[1] += solve(equations[i], equations[i + 1], equations[i + 2]);
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

