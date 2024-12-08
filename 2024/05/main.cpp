#include <iostream>
#include <array>
#include <fstream>
#include <vector>
#include <utility>
#include <functional>

#include "parse.h"

using solutionType = unsigned int;

bool
pagesOrdered(std::vector<std::pair<unsigned int, unsigned int>> const &rules, unsigned int a, unsigned int b)
{
	for (auto const &[l, r] : rules) {
		if (l == b and r == a) {
			return false;
		}
	}
	return true;
}

std::array<solutionType, 2>
solve(std::istream &input)
{
	std::array<solutionType, 2> sum{0};
	std::regex regexRule(R"(([0-9]+)\|([0-9]+))");
	std::regex regexUpdate(R"(([0-9]+))");
	std::vector<std::pair<unsigned int, unsigned int>> rules;
	std::string line;
	while (input) {
		getline(input, line);
		if (line.empty()) {
			break;
		}
		unsigned int left, right;
		regexScan(line, regexRule, left, right);
		rules.emplace_back(left, right);
	}
	auto ordered = std::bind(pagesOrdered, rules, std::placeholders::_1, std::placeholders::_2);
	while (input) {
		getline(input, line);
		if (line.empty()) {
			break;
		}
		std::vector<unsigned int> update;
		regexScan(line, regexUpdate, update);
		bool correctOrder = std::is_sorted(update.begin(), update.end(), ordered);
		sum[0] += correctOrder ? update[update.size() / 2] : 0;
		std::sort(update.begin(), update.end(), ordered);
		sum[1] += correctOrder ? 0 : update[update.size() / 2];
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

