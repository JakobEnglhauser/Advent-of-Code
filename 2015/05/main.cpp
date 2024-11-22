#include <iostream>
#include <array>
#include <fstream>
#include <string>
#include <regex>

using solutionType = unsigned int;

std::string const vowels = "aoeui";

std::array<solutionType, 2>
solve(std::istream &input)
{
	std::array<solutionType, 2> sum{0};
	std::array<std::regex, 5> regex{{
		std::regex(R"([aoeui].*[aoeui].*[aoeui])"),
		std::regex(R"((.)\1)"),
		std::regex(R"(ab|cd|pq|xy)"),
		std::regex(R"((.).\1)"),
		std::regex(R"((..).*\1)")
	}};
	std::string line;
	while (input) {
		getline(input, line);
		if (std::regex_search(line, regex[0])
		    and std::regex_search(line, regex[1])
		    and not std::regex_search(line, regex[2])) {
			++sum[0];
		}
		if (std::regex_search(line, regex[3]) and std::regex_search(line, regex[4])) {
			++sum[1];
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

