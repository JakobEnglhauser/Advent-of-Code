#include <iostream>
#include <array>
#include <fstream>
#include <cmath>

#include "parse.h"

using solutionType = unsigned long;

unsigned long
pow10(unsigned int exp)
{
	unsigned long pow{1};
	for (; exp > 0; --exp) {
		pow *= 10;
	}
	return pow;
}

unsigned int
width(unsigned long number)
{
	return (1 + std::floor(std::log10(number)));
}

template<bool withConcatenation>
bool
equationValid(std::vector<unsigned long> const &values, unsigned long target, size_t index)
{
	if (index == 1) {
		return values[1] == target;
	}
	return (target % values[index] == 0 and equationValid<withConcatenation>(values, target / values[index], index - 1))
		or (target > values[index] and equationValid<withConcatenation>(values, target - values[index], index - 1))
		or (withConcatenation
			and ((target - values[index]) % pow10(width(values[index]))) == 0
			and equationValid<withConcatenation>(values, target / pow10(width(values[index])), index - 1));
}

std::array<solutionType, 2>
solve(std::istream &input)
{
	std::array<solutionType, 2> sum{0};
	std::regex regex(R"(([0-9]+))");
	std::string line;
	while (input) {
		getline(input, line);
		if (line.empty()) {
			break;
		}
		std::vector<unsigned long> values;
		regexScan(line, regex, values);
		sum[0] += equationValid<false>(values, values[0], values.size() - 1) ? values[0] : 0;
		sum[1] += equationValid<true>(values, values[0], values.size() - 1) ? values[0] : 0;
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

