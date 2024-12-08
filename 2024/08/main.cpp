#include <iostream>
#include <array>
#include <fstream>
#include <unordered_map>
#include <set>
#include <vector>
#include <utility>
#include <numeric>

#include "debug.h"

using solutionType = unsigned int;

bool
inBounds(long lower, long n, long upper)
{
	return (lower <= n) and (n < upper);
}

std::array<solutionType, 2>
solve(std::istream &input)
{
	std::array<solutionType, 2> count{0};
	std::unordered_map<char, std::vector<std::pair<long, long>>> antennas;
	long size{0}; /* assumes square input */
	std::string line;
	for (long x = 0; input; ++x) {
		getline(input, line);
		if (line.empty()) {
			break;
		}
		size = line.size();
		for (long y = 0; y < size; ++y) {
			if (line[y] != '.') {
				antennas[line[y]].emplace_back(x, y);
			}
		}
	}
	/* Part 1 */
	std::set<std::pair<long, long>> antinodes;
	for (auto const &[_, antennas] : antennas) {
		for (auto a = antennas.begin(); a != antennas.end(); ++a) {
			for (auto b = a + 1; b != antennas.end(); ++b) {
				auto const diff = std::make_pair(b->first - a->first, b->second - a->second);
				auto anti = std::make_pair(a->first - diff.first, a->second - diff.second);
				if (inBounds(0, anti.first, size) and inBounds(0, anti.second, size)) {
					antinodes.insert(anti);
				}
				anti = std::make_pair(b->first + diff.first, b->second + diff.second);
				if (inBounds(0, anti.first, size) and inBounds(0, anti.second, size)) {
					antinodes.insert(anti);
				}
			}
		}
	}
	count[0] = antinodes.size();
	/* Part 2 */
	antinodes.clear();
	for (auto const &[_, antennas] : antennas) {
		for (auto a = antennas.begin(); a != antennas.end(); ++a) {
			for (auto b = a + 1; b != antennas.end(); ++b) {
				auto diff = std::make_pair(b->first - a->first, b->second - a->second);
				auto gcd = std::gcd(diff.first, diff.second);
				diff = std::make_pair(diff.first / gcd, diff.second / gcd);
				for (auto anti = *a;
					 inBounds(0, anti.first, size) and inBounds(0, anti.second, size);
					 anti = std::make_pair(anti.first - diff.first, anti.second - diff.second)) {
					antinodes.insert(anti);
				}
				for (auto anti = *a;
					 inBounds(0, anti.first, size) and inBounds(0, anti.second, size);
					 anti = std::make_pair(anti.first + diff.first, anti.second + diff.second)) {
					antinodes.insert(anti);
				}
			}
		}
	}
	count[1] = antinodes.size();
	return count;
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

