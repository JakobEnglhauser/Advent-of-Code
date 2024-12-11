#include <iostream>
#include <array>
#include <fstream>
#include <vector>
#include <cmath>
#include <numeric>
#include <functional>
#include <map>
#include <utility>

using solutionType = unsigned long;

solutionType
countStones(unsigned char const iterations, unsigned long const stone)
{
	static std::map<std::pair<unsigned char, unsigned long>, solutionType> memory;
	auto const remember = memory.find({ iterations, stone });
	if (remember != memory.end()) {
		return remember->second;
	} else if (iterations == 0) {
		return 1;
	} else if (stone == 0) {
		auto count = countStones(iterations - 1, 1);
		memory.emplace(std::make_pair(iterations, stone), count);
		return count;
	} else {
		unsigned int digits = 1 + std::floor(std::log10(stone));
		if (digits % 2 == 1) {
			auto count = countStones(iterations - 1, 2024 * stone);
			memory.emplace(std::make_pair(iterations, stone), count);
			return count;
		} else {
			unsigned int pow = std::pow(10, digits / 2);
			auto count = countStones(iterations - 1, stone % pow) + countStones(iterations - 1, stone / pow);
			memory.emplace(std::make_pair(iterations, stone), count);
			return count;
		}
	}
}

std::array<solutionType, 2>
solve(std::istream &input)
{
	std::array<solutionType, 2> count{0};
	std::vector<unsigned long> stones;
	unsigned long stone;
	while (input >> stone) {
		stones.push_back(stone);
	}
	for (auto stone : stones) {
		count[0] += countStones(25, stone);
	}
	for (auto stone : stones) {
		count[1] += countStones(75, stone);
	}
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

