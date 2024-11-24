#include <iostream>
#include <array>
#include <fstream>
#include <map>
#include <string>
#include <string_view>

#include "util.h"

using solutionType = unsigned int;

std::array<solutionType, 2>
solve(std::istream &input)
{
	std::array<solutionType, 2> sue{0};
	std::map<std::string_view, unsigned int> target;
	target.emplace("children", 3);
	target.emplace("cats", 7);
	target.emplace("samoyeds", 2);
	target.emplace("pomeranians", 3);
	target.emplace("akitas", 0);
	target.emplace("vizslas", 0);
	target.emplace("goldfish", 5);
	target.emplace("trees", 3);
	target.emplace("cars", 2);
	target.emplace("perfumes", 1);
	std::string line;
	while (input) {
		getline(input, line);
		if (line.empty()) {
			break;
		}
		char *end;
		unsigned int id = std::strtol(&line[4], &end, 10);
		std::string_view data(end + 2);
		auto fields = split(data, ", ");
		std::array<bool, 2> match{{ true, true }};
		for (auto const &field : fields) {
			auto f = split(field, ": ");
			unsigned int have = std::atol(&f[1][0]);
			unsigned int want = target.at(f[0]);
			/* Part 1 */
			if (have != want) {
				match[0] = false;
			}
			/* Part 2 */
			if (f[0] == "cats" or f[0] == "trees") {
				if (have <= want) {
					match[1] = false;
				}
			} else if (f[0] == "pomeranians" or f[0] == "goldfish") {
				if (have >= want) {
					match[1] = false;
				}
			} else if (have != want) {
				match[1] = false;
			}
		}
		sue[0] = match[0] ? id : sue[0];
		sue[1] = match[1] ? id : sue[1];
	}
	return sue;
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

