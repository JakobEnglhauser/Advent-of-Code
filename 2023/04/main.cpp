#include <iostream>
#include <array>
#include <fstream>
#include <algorithm>
#include <set>
#include <numeric>
#include <cmath>
#include <deque>

#include "util.h"

using solutionType = unsigned int;

std::array<solutionType, 2>
solve(std::istream &input)
{
	std::array<solutionType, 2> sum{0};
	std::string line;
	std::deque<unsigned int> wonCards;
	while (input) {
		getline(input, line);
		if (line.empty()) {
			break;
		}
		auto splits = split(split(std::string_view(line), ": ")[1], " | ");
		auto winStr = split(splits[0], " ");
		std::set<unsigned int> win;
		std::transform(winStr.begin(), winStr.end(), std::inserter(win, win.begin()), [](auto &str) { return std::atol(str.data()); });
		auto haveStr = split(splits[1], " ");
		std::set<unsigned int> have;
		std::transform(haveStr.begin(), haveStr.end(), std::inserter(have, have.begin()), [](auto &str) { return std::atol(str.data()); });

		std::set<unsigned int> haveWins;
		std::set_intersection(win.begin(), win.end(), have.begin(), have.end(),
							  std::inserter(haveWins, haveWins.begin()));

		/* Part 1 */
		sum[0] += haveWins.size() > 0 ? std::pow(2, haveWins.size() - 1) : 0;
		/* Part 2 */
		size_t const copies = wonCards.empty() ? 1 : wonCards.front() + 1;
		if (not wonCards.empty()) {
			wonCards.pop_front();
		}
		sum[1] += copies;
		for (size_t i = 0; i < haveWins.size() and i < wonCards.size(); ++i) {
			wonCards[i] += copies;
		}
		for (size_t i = wonCards.size(); i < haveWins.size(); ++i) {
			wonCards.push_back(copies);
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

