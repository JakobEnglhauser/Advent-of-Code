#include <iostream>
#include <array>
#include <fstream>
#include <regex>

using solutionType = unsigned int;

std::array<solutionType, 2>
solve(std::istream &input)
{
	std::array<solutionType, 2> sum{0};
	std::regex const regex(R"(\\x[0-9a-f][0-9a-f]|\\\\|\\")");
	std::string line;
	while (input) {
		getline(input, line);
		if (line.empty()) {
			break;
		}
		/* Part 1 */
		std::string const raw = std::regex_replace(line, regex, " ");
		sum[0] += line.size() - raw.size() + 2;
		/* Part 2 */
		for (auto const &c : line) {
			if (c == '"' or c == '\\') {
			}
			sum[1] += (c == '"' or c == '\\') ? 1 : 0;
		}
		sum[1] += 2;
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

