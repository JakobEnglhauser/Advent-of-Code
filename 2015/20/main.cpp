#include <iostream>
#include <array>
#include <fstream>
#include <cmath>
#include <vector>

using solutionType = unsigned int;

size_t
presents(unsigned int house)
{
	unsigned int p(1 + house);
	for (unsigned int i = 2; i < house; ++i) {
		p += (house % i == 0) ? i : 0;
	}
	return p;
}

size_t
presents2(unsigned int house)
{
	unsigned int p(0);
	for (unsigned int i = 1; i <= house; ++i) {
		p += (house % i == 0 and house / i <= 50) ? i : 0;
	}
	return p;
}

std::array<solutionType, 2>
solve(std::istream &input)
{
	std::array<solutionType, 2> sum{0};
	unsigned int target;
	input >> target;
	unsigned int targetTenth = target / 10;

	unsigned int i;
	for (i = 1; presents(i) < targetTenth; ++i) {
	}
	sum[0] = i;
	for (i = 1; presents2(i) * 11 < target; ++i) {
	}
	sum[1] = i;
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

