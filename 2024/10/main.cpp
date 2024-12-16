#include <iostream>
#include <array>
#include <fstream>
#include <utility>
#include <vector>

#include "grid.h"

#ifndef SIZE
#define SIZE 53
#endif

using solutionType = size_t;

template<typename T, size_t X, size_t Y = X>
void
explore(Grid<T, X, Y> const &grid, size_t const x, size_t const y, std::vector<std::pair<size_t, size_t>> &trails)
{
	if (grid[x, y] == '9') {
		trails.emplace_back(x, y);
	}
	if (x > 0 and grid[x - 1, y] == grid[x, y] + 1) {
		explore(grid, x - 1, y, trails);
	}
	if (x < SIZE - 1 and grid[x + 1, y] == grid[x, y] + 1) {
		explore(grid, x + 1, y, trails);
	}
	if (y > 0 and grid[x, y - 1] == grid[x, y] + 1) {
		explore(grid, x, y - 1, trails);
	}
	if (y < SIZE - 1 and grid[x, y + 1] == grid[x, y] + 1) {
		explore(grid, x, y + 1, trails);
	}
}

std::array<solutionType, 2>
solve(std::istream &input)
{
	std::array<solutionType, 2> trailCount{0};
	Grid<unsigned char, SIZE> grid;
	input >> grid;
	for (size_t x = 0; x < SIZE; ++x) {
		for (size_t y = 0; y < SIZE; ++y) {
			if (grid[x, y] == '0') {
				std::vector<std::pair<size_t, size_t>> trails;
				explore(grid, x, y, trails);
				trailCount[1] += trails.size();
				std::sort(trails.begin(), trails.end());
				trailCount[0] += std::unique(trails.begin(), trails.end()) - trails.begin();
			}
		}
	}
	return trailCount;
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

