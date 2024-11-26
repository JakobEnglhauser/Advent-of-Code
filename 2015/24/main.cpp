#include <iostream>
#include <array>
#include <vector>
#include <fstream>
#include <numeric>
#include <algorithm>
#include <functional>
#include <limits>

#include "util.h"

using solutionType = unsigned long;

void
findMinConfigurations(std::vector<unsigned int> const &packages, unsigned int const target, std::vector<std::vector<unsigned int>> &minConfigurations, unsigned int const pos = 0, std::vector<unsigned int> chosen = std::vector<unsigned int>())
{
	size_t best = (minConfigurations.size() > 0ul) ?
		minConfigurations.front().size() : std::numeric_limits<size_t>::max();
	if (pos >= packages.size()) {
		/* No more packages available */
	} else if (chosen.size() >= best or packages[pos] * (best - chosen.size()) < target) {
		/* Early exit if this path cannot return better results than the current best.
		 * Requires packages to be sorted from highest to lowest */
	} else if (packages[pos] == target) {
		chosen.push_back(packages[pos]);
		if (chosen.size() < best) {
			/* We found a new optimum, so current results can be discarded. */
			minConfigurations.clear();
		}
		minConfigurations.push_back(chosen);
	} else if (packages[pos] > target) {
		return findMinConfigurations(packages, target, minConfigurations, pos + 1, chosen);
	} else {
		/* Greedy path first reaches the optimum faster, reducing runtime thanks to current best optimization */
		chosen.push_back(packages[pos]);
		findMinConfigurations(packages, target - packages[pos], minConfigurations, pos + 1, chosen);
		chosen.pop_back();
		findMinConfigurations(packages, target, minConfigurations, pos + 1, chosen);
	}
}

solutionType
minQuantumEntanglement(std::vector<unsigned int> packages, unsigned int targetWeight)
{
	std::vector<std::vector<unsigned int>> minConfigurations;
	findMinConfigurations(packages, targetWeight, minConfigurations);

	solutionType min = std::numeric_limits<solutionType>::max();
	for (auto const &conf : minConfigurations) {
		min = std::min(min, std::accumulate(conf.begin(), conf.end(), 1ul, std::multiplies<unsigned long>{}));
	}

	return min;
}

std::array<solutionType, 2>
solve(std::istream &input)
{
	std::vector<unsigned int> packages;
	std::string line;
	unsigned int n;
	while (input >> n) {
		packages.push_back(n);
	}
	std::sort(packages.begin(), packages.end(), std::greater<unsigned int>{});
	unsigned int totalWeight = std::accumulate(packages.begin(), packages.end(), 0);

	return { minQuantumEntanglement(packages, totalWeight / 3),
		minQuantumEntanglement(packages, totalWeight / 4) };
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

