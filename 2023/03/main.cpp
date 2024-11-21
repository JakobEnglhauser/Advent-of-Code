#include <iostream>
#include <array>
#include <fstream>
#include <vector>

using solutionType = size_t;

std::array<solutionType, 2>
solve(std::istream &input)
{
	std::array<solutionType, 2> sum{0};
	std::array<std::string, 3> lines;
	getline(input, lines[1]);
	while (input) {
		getline(input, lines[2]);
		/* Part 1 */
		for (size_t i = 0; i < lines[1].size(); ++i) {
			char *end;
			long const n = std::strtol(&lines[1][i], &end, 10);
			size_t const endPos = static_cast<size_t>(end - lines[1].c_str());
			if (n <= 0) {
				continue;
			}
			bool isPartNumber = (i > 0 and lines[1][i - 1] != '.')
				or (endPos < lines[1].size() and lines[1][endPos] != '.');
			for (size_t j = (i > 0 ? i - 1 : 0); j < std::min(lines[1].size(), endPos + 1); ++j) {
				if ((not lines[0].empty() and lines[0][j] != '.')
					or (not lines[2].empty() and lines[2][j] != '.')) {
					isPartNumber = true;
					break;
				}
			}
			sum[0] += isPartNumber ? n : 0;
			i = endPos;
		}
		/* Part 2 */
		for (size_t i = 0; i < lines[1].size(); ++i) {
			if (lines[1][i] != '*') {
				continue;
			}
			std::vector<unsigned long> numbers;
			for (auto const &line : lines) {
				if (not line.empty()) {
					long const n = std::atol(&line[line.find_last_not_of("0123456789", i - 1) + 1]);
					if (n > 0) {
						numbers.push_back(n);
					}
					if (line[i] < '0' or line[i] > '9') {
						long const n = std::atol(&line[i + 1]);
						if (n > 0) {
							numbers.push_back(n);
						}
					}
				}
			}
			if (numbers.size() == 2) {
				sum[1] += numbers[0] * numbers[1];
			}
		}
		lines[0] = std::move(lines[1]);
		lines[1] = std::move(lines[2]);
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

