#include <iostream>
#include <array>
#include <vector>
#include <fstream>
#include <algorithm>

using solutionType = unsigned int;

std::array<solutionType, 2>
solve(std::istream &input)
{
	std::array<solutionType, 2> sum{0};
	std::vector<int> left, right;
	std::string line;
	int n;
	while (input >> n) {
		left.push_back(n);
		input >> n;
		right.push_back(n);
	}
	std::sort(left.begin(), left.end());
	std::sort(right.begin(), right.end());
	for (size_t i = 0; i < left.size(); ++i) {
		sum[0] += std::abs(left[i] - right[i]);
		sum[1] += left[i] * std::count(right.begin(), right.end(), left[i]);
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

