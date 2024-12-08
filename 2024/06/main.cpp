#include <iostream>
#include <array>
#include <fstream>
#include <utility>

#include "grid.h"

#define SIZE 130

using solutionType = unsigned int;

std::pair<size_t, size_t>
next(size_t x, size_t y, int dir)
{
	switch (dir) {
	case 0: /* Up */
		return { x - 1, y };
	case 1: /* Right */
		return { x, y + 1 };
	case 2: /* Down */
		return { x + 1, y };
	case 3: /* Left */
		return { x, y - 1 };
	}
	return { x, y }; /* Unreachable */
}

bool
inBounds(size_t x, size_t y)
{
	return x >= 0 and x < SIZE and y >= 0 and y < SIZE;
}

char
dirBits(int dir)
{
	return '0' | (1 << dir);
}

template<typename T, size_t X, size_t Y>
bool
patrol(Grid<T, X, Y> &map, std::pair<size_t, size_t> start)
{
	size_t x, y;
	x = start.first;
	y = start.second;
	int dir = 0;
	while (inBounds(x, y)) {
		if ((map[x, y] & dirBits(dir)) == dirBits(dir)) {
			return true; /* looped */
		}
		map[x, y] = (map[x, y] & '0') == '0' ? map[x, y] | dirBits(dir) : dirBits(dir);
		auto [nx, ny] = next(x, y, dir);
		while (inBounds(nx, ny) and map[nx, ny] == '#') {
			dir = (dir + 1) % 4;
			std::tie(nx, ny) = next(x, y, dir);
		}
		x = nx;
		y = ny;
	}
	return false;
}

std::array<solutionType, 2>
solve(std::istream &input)
{
	std::array<solutionType, 2> count{0};
	Grid<char, SIZE> map;
	std::pair<size_t, size_t> start;
	for (size_t x = 0; x < SIZE; ++x) {
		for (size_t y = 0; y < SIZE; ++y) {
			input >> map[x, y];
			if (map[x, y] == '^') {
				start = {x, y};
			}
		}
	}
	patrol(map, start);
	std::vector<std::pair<size_t, size_t>> path;
	for (size_t x = 0; x < SIZE; ++x) {
		for (size_t y = 0; y < SIZE; ++y) {
			if ((map[x, y] & '0') == '0') {
				++count[0];
				path.emplace_back(x, y);
			}
		}
	}
	for (auto const &[x, y] : path) {
		for (size_t i = 0; i < SIZE * SIZE; ++i) {
			map[i] = (map[i] & '0') == '0' ? '.' : map[i];
		}
		map[x, y] = '#';
		count[1] += patrol(map, start) ? 1 : 0;
		map[x, y] = '.';
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

