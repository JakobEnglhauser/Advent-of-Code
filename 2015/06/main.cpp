#include <iostream>
#include <array>
#include <fstream>
#include <regex>

#include "grid.h"

using solutionType = unsigned int;

std::array<solutionType, 2>
solve(std::istream &input)
{
	std::array<solutionType, 2> sum{0};
	std::regex const lineParser(R"((turn on|turn off|toggle) ([0-9]*),([0-9]*) through ([0-9]*),([0-9]*))");
	Grid<bool, 1000, 1000> grid1(false);
	Grid<unsigned long, 1000, 1000> grid2(0);
	std::string line;
	while (input) {
		getline(input, line);
		if (line.empty()) {
			break;
		}
		std::smatch match;
		std::regex_match(line, match, lineParser);
		std::ssub_match const action = match[1];
		std::array<size_t const, 2> const from{{std::stoul(match[2]), std::stoul(match[3])}};
		std::array<size_t const, 2> const to{{std::stoul(match[4]), std::stoul(match[5])}};

		for (size_t x = from[0]; x <= to[0]; ++x) {
			for (size_t y = from[1]; y <= to[1]; ++y) {
				if (action == "turn on") {
					grid1[x, y] = true;
					++grid2[x, y];
				} else if (action == "turn off") {
					grid1[x, y] = false;
					grid2[x, y] -= (grid2[x, y] > 0 ? 1 : 0);
				} else if (action == "toggle") {
					grid1[x, y] = not grid1[x, y];
					grid2[x, y] += 2;
				}
			}
		}
	}
	for (size_t i = 0; i < grid1.size(); ++i) {
		sum[0] += grid1[i] ? 1 : 0;
		sum[1] += grid2[i];
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

