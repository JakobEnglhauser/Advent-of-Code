#include <iostream>
#include <string>
#include <array>
#include <fstream>
#include <regex>

using solutionType = unsigned int;

unsigned int
parseDigit(std::string const &digit)
{
	if (digit.length() == 1) {
		return digit[0] - '0';
	} else if (digit == "on") {
		return 1;
	} else if (digit == "tw") {
		return 2;
	} else if (digit == "thre") {
		return 3;
	} else if (digit == "four") {
		return 4;
	} else if (digit == "fiv") {
		return 5;
	} else if (digit == "six") {
		return 6;
	} else if (digit == "seve") {
		return 7;
	} else if (digit == "eigh") {
		return 8;
	} else if (digit == "nin") {
		return 9;
	} else {
		return 0;
	}
}

std::array<solutionType, 2>
solve(std::istream &input)
{
	std::string line;
	std::array<unsigned int, 2> sum{0};
	std::array<std::regex, 2> regex{
		std::regex("[0-9]"),
		std::regex("[0-9]|on(?=e)|tw(?=o)|thre(?=e)|four|fiv(?=e)|six|seve(?=n)|eigh(?=t)|nin(?=e)") /* lookaheads solve the issue of overlapping words */
	};
	while (input) {
		getline(input, line);
		for (int i = 0; i < 2; ++i) {
			auto match = std::sregex_iterator(line.begin(), line.end(), regex[i]);
			std::string digit = match->str();
			sum[i] += 10 * parseDigit(digit);
			/* find last match */
			for (; match != std::sregex_iterator(); ++match) {
				digit = match->str();
			}
			sum[i] += parseDigit(digit);
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

