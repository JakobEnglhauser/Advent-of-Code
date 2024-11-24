#include <iostream>
#include <array>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <bitset>

using solutionType = unsigned int;

constexpr unsigned int eggnog = 150;

std::array<solutionType, 2>
solve(std::istream &input)
{
	std::array<solutionType, 2> count{0};
	std::vector<unsigned int> containers;
	std::string line;
	while (input) {
		getline(input, line);
		if (line.empty()) {
			break;
		}
		containers.push_back(std::stoul(line));
	}
	unsigned int min(std::numeric_limits<unsigned int>::max());
	for (size_t i = 0; i < (1ul << containers.size()); ++i) {
		unsigned int volume(0);
		for (size_t j = 0; j < containers.size(); ++j) {
			volume += (i & (1 << j)) ? containers[j] : 0;
		}
		if (volume == eggnog) {
			/* Part 1 */
			++count[0];
			/* Part 2 */
			unsigned int c = std::bitset<64>(i).count();
			if (c < min) {
				min = c;
				count[1] = 1;
			} else if (c == min) {
				++count[1];
			}
		}
	}
	return count;
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

