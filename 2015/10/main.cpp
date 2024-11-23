#include <iostream>
#include <array>
#include <fstream>
#include <regex>
#include <sstream>

using solutionType = size_t;

inline std::string
lookAndSay(std::string const &in)
{
	static std::regex const regex(R"((.)\1*)");
	std::ostringstream out;
	for (std::sregex_iterator i(in.begin(), in.end(), regex); i != std::sregex_iterator(); ++i) {
		out << (*i)[0].str().size() << (*i)[0].str()[0];
	}
	return out.str();
}

std::array<solutionType, 2>
solve(std::istream &input)
{
	std::string line;
	getline(input, line);
	for (int i = 0; i < 40; ++i) {
		line = lookAndSay(line);
	}
	size_t length40 = line.size();
	for (int i = 0; i < 10; ++i) {
		line = lookAndSay(line);
	}
	return { length40, line.size() };
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

