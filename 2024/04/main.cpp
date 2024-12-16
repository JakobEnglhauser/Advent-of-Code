#include <iostream>
#include <array>
#include <fstream>
#include <cstdint>

#include "grid.h"

#ifndef SIZE
#define SIZE 140
#endif

using solutionType = unsigned int;

std::array<solutionType, 2>
solve(std::istream &input)
{
	std::array<solutionType, 2> sum{0};
	Grid<char, SIZE> grid;
	input >> grid;
	/* Part 1 */
	for (std::size_t x = 0; x < SIZE; ++x) {
		std::size_t y;
		for (y = 0; y + 3 < SIZE; ++y) {
			if (grid[x, y] == 'X' and grid[x, y + 1] == 'M' and grid[x, y + 2] == 'A' and grid[x, y + 3] == 'S') {
				++sum[0];
			}
			if (grid[x, y] == 'S' and grid[x, y + 1] == 'A' and grid[x, y + 2] == 'M' and grid[x, y + 3] == 'X') {
				++sum[0];
			}
			if (x + 3 < SIZE and grid[x, y] == 'X' and grid[x + 1, y] == 'M' and grid[x + 2, y] == 'A' and grid[x + 3, y] == 'S') {
				++sum[0];
			}
			if (x + 3 < SIZE and grid[x, y] == 'S' and grid[x + 1, y] == 'A' and grid[x + 2, y] == 'M' and grid[x + 3, y] == 'X') {
				++sum[0];
			}
			if (x + 3 < SIZE and grid[x, y] == 'X' and grid[x + 1, y + 1] == 'M' and grid[x + 2, y + 2] == 'A' and grid[x + 3, y + 3] == 'S') {
				++sum[0];
			}
			if (x + 3 < SIZE and grid[x, y] == 'S' and grid[x + 1, y + 1] == 'A' and grid[x + 2, y + 2] == 'M' and grid[x + 3, y + 3] == 'X') {
				++sum[0];
			}
			if (x >= 3 and grid[x, y] == 'X' and grid[x - 1, y + 1] == 'M' and grid[x - 2, y + 2] == 'A' and grid[x - 3, y + 3] == 'S') {
				++sum[0];
			}
			if (x >= 3 and grid[x, y] == 'S' and grid[x - 1, y + 1] == 'A' and grid[x - 2, y + 2] == 'M' and grid[x - 3, y + 3] == 'X') {
				++sum[0];
			}
		}
		for (; y < SIZE; ++y) {
			if (x + 3 < SIZE and grid[x, y] == 'X' and grid[x + 1, y] == 'M' and grid[x + 2, y] == 'A' and grid[x + 3, y] == 'S') {
				++sum[0];
			}
			if (x + 3 < SIZE and grid[x, y] == 'S' and grid[x + 1, y] == 'A' and grid[x + 2, y] == 'M' and grid[x + 3, y] == 'X') {
				++sum[0];
			}
		}
	}
	/* Part 2 */
	for (std::size_t x = 1; x < SIZE - 1; ++x) {
		for (std::size_t y = 1; y < SIZE - 1; ++y) {
			if (grid[x, y] == 'A'
			    and ((grid[x - 1, y - 1] == 'M' and grid[x + 1, y + 1] == 'S')
			         or (grid[x - 1, y - 1] == 'S' and grid[x + 1, y + 1] == 'M'))
			    and ((grid[x - 1, y + 1] == 'M' and grid[x + 1, y - 1] == 'S')
			         or (grid[x - 1, y + 1] == 'S' and grid[x + 1, y - 1] == 'M'))) {
				++sum[1];
			}
		}
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

