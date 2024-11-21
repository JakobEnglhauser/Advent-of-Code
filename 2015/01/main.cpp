#include <iostream>
#include <array>
#include <fstream>

using solutionType = long;

std::array<solutionType, 2>
solve(std::istream &input)
{
	solutionType floor = 0;
	solutionType basement = -1;
	std::string line;
	getline(input, line);
	for (auto const &c : line) {
		switch (c) {
		case '(':
			++floor;
			break;
		case ')':
			--floor;
			break;
		}
		if (floor < 0 and basement == -1) {
			basement = &c - line.c_str() + 1;
		}
	}
	return { floor, basement };
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

