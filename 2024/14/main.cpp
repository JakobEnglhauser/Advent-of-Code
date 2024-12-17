#include <iostream>
#include <array>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>

#include "parse.h"
#include "debug.h"

using solutionType = unsigned int;

constexpr int width = 101;
constexpr int height = 103;

std::array<int, 2>
move(std::vector<int> const &robot, int time)
{
	auto x = (robot[0] + robot[2] * time) % width;
	x = x < 0 ? x + width : x;
	auto y = (robot[1] + robot[3] * time) % height;
	y = y < 0 ? y + height : y;
	return {x, y};
}

std::array<solutionType, 2>
solve(std::istream &input)
{
	std::array<solutionType, 4> quadrants{0};
	std::regex regex(R"(([-0-9]+))");
	std::vector<std::vector<int>> robots;
	std::string line;
	while (input) {
		getline(input, line);
		if (line.empty()) {
			break;
		}
		robots.emplace_back();
		regexScan(line, regex, robots.back());
		auto const [x, y] = move(robots.back(), 100);
		if (not (x == width / 2 or y == height / 2)) {
			++quadrants[(x < width / 2 ? 0 : 2) + (y < height / 2 ? 0 : 1)];
		}
	}
	solutionType safetyFactor = quadrants[0] * quadrants[1] * quadrants[2] * quadrants[3];
	solutionType time;
	std::array<std::vector<int>, width> columns;
	std::vector<int> straight(30);
	for (time = 0; ; ++time) {
		for (auto const &robot : robots) {
			auto const [c, r] = move(robot, time);
			columns[c].push_back(r);
		}
		for (auto &column : columns) {
			std::sort(column.begin(), column.end());
			for (auto r = column.begin(); std::distance(r, column.end()) >= 30; ++r) {
				std::iota(straight.begin(), straight.end(), *r);
				if (std::equal(straight.begin(), straight.end(), r)) {
					return { safetyFactor, time };
				}
			}
			column.clear();
		}
	}
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

