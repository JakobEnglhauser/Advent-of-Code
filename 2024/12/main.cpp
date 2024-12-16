#include <iostream>
#include <array>
#include <fstream>
#include <set>
#include <cctype>
#include <bitset>

#include "grid.h"

#ifndef SIZE
#define SIZE 140
#endif

using solutionType = unsigned int;

template<typename T, size_t X, size_t Y = X>
std::array<solutionType, 3>
explore(Grid<T, X, Y> &map, size_t startX, size_t startY)
{
	solutionType area{0}, perimeter{0}, corners{0};
	std::set<std::pair<size_t, size_t>> q;
	q.emplace(startX, startY);
	while (not q.empty()) {
		auto const [x, y] = q.extract(q.begin()).value();
		std::array<solutionType, 2> visitedNeighbors{0};
		std::bitset<4> diagonals{0};
		auto v = [&](size_t nx, size_t ny) {
			if (map[nx, ny] == map[x, y]) {
				q.emplace(nx, ny);
			} else if (map[nx, ny] == std::tolower(map[x, y])) {
				++visitedNeighbors[nx == x ? 0 : 1];
				return true;
			}
			return false;
		};
		if (x > 0) {
			if (v(x - 1, y)) {
				if (y > 0 and map[x - 1, y - 1] == std::tolower(map[x, y])) {
					diagonals[0] = not diagonals[0];
				}
				if (y < SIZE - 1 and map[x - 1, y + 1] == std::tolower(map[x, y])) {
					diagonals[1] = not diagonals[1];
				}
			}
		}
		if (x < SIZE - 1) {
			if (v(x + 1, y)) {
				if (y > 0 and map[x + 1, y - 1] == std::tolower(map[x, y])) {
					diagonals[2] = not diagonals[2];
				}
				if (y < SIZE - 1 and map[x + 1, y + 1] == std::tolower(map[x, y])) {
					diagonals[3] = not diagonals[3];
				}
			}
		}
		if (y > 0) {
			if (v(x, y - 1)) {
				if (x > 0 and map[x - 1, y - 1] == std::tolower(map[x, y])) {
					diagonals[0] = not diagonals[0];
				}
				if (x < SIZE - 1 and map[x + 1, y - 1] == std::tolower(map[x, y])) {
					diagonals[2] = not diagonals[2];
				}
			}
		}
		if (y < SIZE - 1) {
			if (v(x, y + 1)) {
				if (x > 0 and map[x - 1, y + 1] == std::tolower(map[x, y])) {
					diagonals[1] = not diagonals[1];
				}
				if (x < SIZE - 1 and map[x + 1, y + 1] == std::tolower(map[x, y])) {
					diagonals[3] = not diagonals[3];
				}
			}
		}
		++area;
		perimeter += 4 - 2 * (visitedNeighbors[0] + visitedNeighbors[1]);
		switch (visitedNeighbors[0] + visitedNeighbors[1]) {
		case 0:
			corners += 4;
			break;
		case 1:
			corners += 2 * diagonals.count();
			break;
		case 2:
			switch (diagonals.count()) {
			case 0:
				corners -= 2;
				break;
			case 1:
				corners -= (visitedNeighbors[0] == visitedNeighbors[1]) ? 0 : 2;
				break;
			case 2:
				corners += (visitedNeighbors[0] == visitedNeighbors[1]) ? 2 : 0;
				break;
			case 3:
				corners += 2;
				break;
			case 4:
				corners += 4;
				break;
			}
			break;
		case 3:
			corners += 2 * (diagonals.count() - 2);
			break;
		case 4:
			corners -= 4;
			break;
		}
		map[x, y] = std::tolower(map[x, y]);
	}
	return {area, perimeter, corners};
}

std::array<solutionType, 2>
solve(std::istream &input)
{
	std::array<solutionType, 2> sum{0};
	Grid<char, SIZE> map;
	input >> map;
	for (size_t x = 0; x < SIZE; ++x) {
		for (size_t y = 0; y < SIZE; ++y) {
			if (std::isupper(map[x, y])) {
				auto const [area, perimeter, corners] = explore(map, x, y);
				sum[0] += area * perimeter;
				sum[1] += area * corners;
			}
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

