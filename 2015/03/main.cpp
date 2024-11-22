#include <iostream>
#include <array>
#include <fstream>
#include <cstdint>
#include <set>

using solutionType = size_t;

struct Position {
	long x;
	long y;

	bool
	operator<(Position const &rhs) const {
		return this->y == rhs.y ? this->x < rhs.x : this->y < rhs.y;
	}
};

void
move(Position &pos, char c)
{
	switch (c) {
		case '^':
			++pos.x;
			break;
		case 'v':
			--pos.x;
			break;
		case '>':
			++pos.y;
			break;
		case '<':
			--pos.y;
			break;
	}
}


std::array<solutionType, 2>
solve(std::istream &input)
{
	std::string line;
	getline(input, line);
	std::array<solutionType, 2> visitCount = {0};
	/* Part 1 */
	{
		std::set<Position> visited;
		Position pos{0, 0};
		visited.insert(pos);
		for (char c : line) {
			move(pos, c);
			visited.insert(pos);
		}
		visitCount[0] = visited.size();
	}
	/* Part 2 */
	{
		std::set<Position> visited;
		std::array<Position, 2> pos{{{0, 0}, {0, 0}}};
		visited.insert(pos[0]);
		char toggle = 0;
		for (char c : line) {
			move(pos[toggle], c);
			visited.insert(pos[toggle]);
			toggle = 1 - toggle;
		}
		visitCount[1] = visited.size();
	}
	return visitCount;
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

