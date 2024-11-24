#include <iostream>
#include <array>
#include <fstream>
#include <numeric>
#include <limits>
#include <cmath>

using solutionType = int;

constexpr double playerHP = 100.0;

std::array<solutionType, 2>
solve(std::istream &input)
{
	std::array<int, 5> const weapons{{ 8, 10, 25, 40, 74 }};
	std::array<int, 6> const armors{{ 0, 13, 31, 53, 75, 102 }};
	std::array<int, 8> const rings{{ 0, 25, 50, 100, 0, 20, 40, 80 }};

	std::string line;
	int hp, damage, defence;
	input >> line;
	input >> line;
	input >> hp;
	input >> line;
	input >> damage;
	input >> line;
	input >> defence;

	solutionType min{std::numeric_limits<solutionType>::max()};
	solutionType max{0};
	for (unsigned int w = 0; w < weapons.size(); ++w) {
		for (unsigned int a = 0; a < armors.size(); ++a) {
			for (unsigned int r1 = 0; r1 < rings.size(); ++r1) {
				for (unsigned int r2 = r1 + 1; r2 < rings.size(); ++r2) {
					auto const dmgOut = std::max(1l, static_cast<long>(w) + 4 + (r1 < 4 ? r1 : 0) + (r2 < 4 ? r2 : 0) - defence);
					auto const dmgIn = std::max(1l, damage - static_cast<long>(a) - (r1 < 4 ? 0 : (r1 - 4)) - (r2 < 4 ? 0 : (r2 - 4)));
					auto const kill = std::ceil(static_cast<double>(hp) / dmgOut);
					auto const death = std::ceil(playerHP / dmgIn);
					auto const cost = weapons[w] + armors[a] + rings[r1] + rings[r2];
					if (kill <= death) {
						min = std::min(min, cost);
					} else {
						max = std::max(max, cost);
					}
				}
			}
		}
	}
	return { min, max };
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

