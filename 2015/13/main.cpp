#include <iostream>
#include <array>
#include <fstream>
#include <numeric>
#include <algorithm>
#include <limits>

#include "grid.h"

using solutionType = int;
#ifndef GUEST_COUNT
#define GUEST_COUNT 8
#endif

template<unsigned int count, typename Grid>
int
maxHappiness(Grid const &happiness)
{
	int max(0);
	std::array<unsigned int, count> order;
	std::iota(order.begin(), order.end(), 0);
	do {
		int happy = 0;
		for (unsigned int i = 0; i < count; ++i) {
			happy += happiness[order[i], order[(i + 1) % count]];
			happy += happiness[order[(i + 1) % count], order[i]];
		}
		max = std::max(max, happy);
	} while (std::next_permutation(order.begin(), order.end()));
	return max;
}

std::array<solutionType, 2>
solve(std::istream &input)
{
	Grid<int, GUEST_COUNT + 1, GUEST_COUNT + 1> happiness(0);
	std::string line;
	/* 
	 * Parse input
	 * Assumes input contains *all* pairwise happiness changes between GUEST_COUNT
	 * guests in sorted (in any way) order
	 */
	for (unsigned int i = 0; i < GUEST_COUNT; ++i) {
		for (unsigned int j = 0; j < GUEST_COUNT; ++j) {
			if (i == j) {
				continue;
			}
			getline(input, line);
			happiness[i, j] = std::atoi(line.c_str() + line.find_first_of("0123456789"));
			if (line.contains(" lose ")) {
				happiness[i, j] *= -1;
			}
		}
	}
	return { maxHappiness<GUEST_COUNT>(happiness), maxHappiness<GUEST_COUNT + 1>(happiness) };
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

