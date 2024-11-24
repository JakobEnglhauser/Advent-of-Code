#include <iostream>
#include <array>
#include <fstream>
#include <functional>
#include <cstdarg>

#include "grid.h"

using solutionType = size_t;

constexpr unsigned int lightsPerDimension = 100;
constexpr unsigned int steps = 100;

void
stencil(bool &target, bool const &value, std::vector<std::reference_wrapper<bool const>> const &neighbors) 
{
	unsigned int on(0);
	for (auto const &n : neighbors) {
		on += n ? 1 : 0;
	}
	if (value) {
		target = (on == 2 or on == 3) ? true : false;
	} else {
		target = (on == 3 ? true : false);
	}
}

std::array<solutionType, 2>
solve(std::istream &input)
{
	Grid<bool, lightsPerDimension> grid;
	std::string line;
	for (size_t i = 0; i < lightsPerDimension; ++i) {
		getline(input, line);
		for (size_t j = 0; j < lightsPerDimension; ++j) {
			grid[i, j] = line[j] == '#';
		}
	}
	/* Copy for Part 2 */
	Grid<bool, lightsPerDimension> grid2;
	grid2 = grid;
	/* Part 1 */
	for (size_t i = 0; i < steps; ++i) {
		grid.apply9(&stencil);
	}
	/* Part 2 */
	grid2[0, 0] = true;
	grid2[0, lightsPerDimension - 1] = true;
	grid2[lightsPerDimension - 1, 0] = true;
	grid2[lightsPerDimension - 1, lightsPerDimension - 1] = true;
	for (size_t i = 0; i < steps; ++i) {
		grid2.apply9(&stencil);
		grid2[0, 0] = true;
		grid2[0, lightsPerDimension - 1] = true;
		grid2[lightsPerDimension - 1, 0] = true;
		grid2[lightsPerDimension - 1, lightsPerDimension - 1] = true;
	}
	return { grid.count(true), grid2.count(true) };
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

