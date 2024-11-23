#include <iostream>
#include <array>
#include <fstream>
#include <stack>
#include <string_view>

using solutionType = long;

long sumNumbers(std::string const &in)
{
	long sum(0);
	for (size_t i = in.find_first_of("0123456789-"); i < in.size(); i = in.find_first_of("0123456789-", i)) {
		char *end;
		long n = std::strtol(&in.c_str()[i], &end, 10);
		sum += n;
		i = end - in.c_str();
	}
	return sum;
}

std::array<solutionType, 2>
solve(std::istream &input)
{
	std::array<solutionType, 2> sum{0};
	std::string line;
	getline(input, line);
	sum[0] = sumNumbers(line);

	std::stack<size_t> openings;
	for (size_t i = 0; i < line.size(); ++i) {
		if (line[i] == '[' or line[i] == '{') {
			openings.push(i);
		} else if (line[i] == ']' or line[i] == '}') {
			openings.pop();
		} else if (line[openings.top()] == '{' and line[i] == '"' and line[i + 1] == 'r'
				   and line[i + 2] == 'e' and line[i + 3] == 'd' and line[i + 4] == '"') {
			size_t openCount(0), end;
			for (end = i; end < line.size(); ++end) {
				if (line[end] == '[' or line[end] == '{') {
					++openCount;
				} else if ((line[end] == ']' or line[end] == '}') and openCount > 0) {
					--openCount;
				} else if ((line[end] == ']' or line[end] == '}') and openCount == 0) {
					break;
				}
			}
			line[openings.top()] = '[';
			std::fill(line.begin() + openings.top() + 1, line.begin() + end, ' ');
			line[end] = ']';
			i = end - 1;
		}
	}

	sum[1] = sumNumbers(line);

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

