#include <iostream>
#include <array>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>

#include "util.h"

using solutionType = size_t;

struct Bag {
	size_t red;
	size_t green;
	size_t blue;
};

constexpr Bag limit { .red = 12, .green = 13, .blue = 14 };

std::vector<Bag>
parseLine(std::string const &line)
{
	std::string_view game(line);
	game = game.substr(game.find(": ") + 2);
	std::vector<Bag> bags;
	for (auto const &bag : split(game, "; ")) {
		Bag b{ 0, 0, 0};
		for (auto const &cube : split(bag, ", ")) {
			switch (cube.back()) {
			case 'd':
				b.red += std::atol(cube.data());
				break;
			case 'n':
				b.green += std::atol(cube.data());
				break;
			case 'e':
				b.blue += std::atol(cube.data());
				break;
			}
		}
		bags.push_back(b);
	}
	return bags;
}

std::array<solutionType, 2>
solve(std::istream &input)
{
	std::string line;
	std::array<solutionType, 2> sum{0, 0};
	size_t id = 0;
	while (input) {
		getline(input, line);
		if (line.empty()) {
			break;
		}
		auto const bags = parseLine(line);
		/* part 1 */
		++id;
		bool possible = true;
		for (auto const &bag : bags) {
			if (bag.red > limit.red or bag.green > limit.green or bag.blue > limit.blue) {
				possible = false;
				break;
			}
		}
		if (possible) {
			sum[0] += id;
		}
		/* part 2 */
		Bag max{ 0, 0, 0 };
		for (auto const &bag : bags) {
			if (bag.red > limit.red or bag.green > limit.green or bag.blue > limit.blue) {
				possible = false;
			}
			max.red = std::max(max.red, bag.red);
			max.green = std::max(max.green, bag.green);
			max.blue = std::max(max.blue, bag.blue);
		}
		sum[1] += max.red * max.green * max.blue;
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

