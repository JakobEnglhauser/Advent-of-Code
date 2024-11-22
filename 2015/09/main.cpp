#include <iostream>
#include <array>
#include <fstream>
#include <numeric>
#include <algorithm>
#include <limits>

#include "grid.h"

using solutionType = unsigned int;
#ifndef CITY_COUNT
#define CITY_COUNT 8
#endif

std::array<solutionType, 2>
solve(std::istream &input)
{
	Grid<unsigned int, CITY_COUNT, CITY_COUNT> distances(0);
	std::string line;
	/* 
	 * Parse input
	 * Assumes input contains *all* pairwise distances between CITY_COUNT cities
	 * in sorted (in any way) order
	 */
	for (unsigned int i = 0; i < CITY_COUNT; ++i) {
		for (unsigned int j = i + 1; j < CITY_COUNT; ++j) {
			getline(input, line);
			distances[i, j] = std::atoi(line.c_str() + line.rfind("=") + 1);
			distances[j, i] = distances[i, j];
		}
	}
	solutionType min(std::numeric_limits<solutionType>::max());
	solutionType max(0);
	std::array<unsigned int, CITY_COUNT> order;
	std::iota(order.begin(), order.end(), 0);
	do {
		unsigned int length = 0;
		for (unsigned int i = 0, j = 1; j < CITY_COUNT; ++i, ++j) {
			length += distances[order[i], order[j]];
		}
		min = std::min(min, length);
		max = std::max(max, length);
	} while (std::next_permutation(order.begin(), order.end()));
	return { min, max };
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

