#include <iostream>
#include <array>
#include <fstream>
#include <vector>

#include "util.h"

using solutionType = unsigned int;

std::array<solutionType, 2>
solve(std::istream &input)
{
	std::array<solutionType, 2> sum{0};
	std::string line;
	while (input) {
		getline(input, line);
		if (line.empty()) {
			break;
		}
		auto dim = split(line, "x");
		int x = std::atoi(dim[0].data());
		int y = std::atoi(dim[1].data());
		int z = std::atoi(dim[2].data());

		sum[0] += 2 * (x * y + y * z + z * x) + std::min(std::min(x * y, y * z), z * x);
		sum[1] += 2 * std::min(std::min(x + y, y + z), z + x) + (x * y * z);
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

