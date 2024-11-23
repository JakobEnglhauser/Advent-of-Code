#include <iostream>
#include <array>
#include <fstream>
#include <regex>
#include <cstdint>

using solutionType = std::string;

inline std::string &
increment(std::string &pass)
{
	for (int i = pass.size() - 1; i >= 0; --i) {
		if (pass[i] == 'z') {
			pass[i] = 'a';
		} else {
			++pass[i];
			break;
		}
	}
	return pass;
}

inline bool
valid(std::string const &pass)
{
	static std::regex const blacklist(R"([iol])");
	static std::regex const pairs(R"((.)\1.*(.)\2)");
	bool straight = false;
	for (size_t i = 0, j = 1, k = 2; k < pass.size(); ++i, ++j, ++k) {
		if (pass[k] - pass[j] == 1 and pass[j] - pass[i] == 1) {
			straight = true;
			break;
		}
	}
	return straight and not std::regex_search(pass, blacklist) and std::regex_search(pass, pairs);
}

std::array<solutionType, 2>
solve(std::istream &input)
{
	std::array<solutionType, 2> nextPass;
	std::string line;
	getline(input, line);
	//uint64_t pass = std::stoul(line);
	do {
		increment(line);
	} while (not valid(line));
	nextPass[0] = line;
	do {
		increment(line);
	} while (not valid(line));
	nextPass[1] = line;
	return nextPass;
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

