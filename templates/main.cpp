#include <iostream>
#include <array>
#include <fstream>

using solutionType = unsigned int;

std::array<solutionType, 2>
solve(std::istream &input)
{
	return {0, 0};
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

