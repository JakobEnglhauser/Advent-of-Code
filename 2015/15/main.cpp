#include <iostream>
#include <array>
#include <fstream>
#include <vector>
#include <algorithm>

using solutionType = unsigned long;

constexpr unsigned char spoons = 100;
constexpr unsigned int calorieTarget = 500;

struct Ingredient {
	int const capacity;
	int const durability;
	int const flavor;
	int const texture;
	int const calories;
};

solutionType
score(std::vector<Ingredient> const &ingredients, std::vector<unsigned char> const &amounts)
{
	long capacityScore(0);
	long durabilityScore(0);
	long flavorScore(0);
	long textureScore(0);
	for (size_t i = 0; i < ingredients.size() and i < amounts.size(); ++i) {
		capacityScore += ingredients[i].capacity * amounts[i];
		durabilityScore += ingredients[i].durability * amounts[i];
		flavorScore += ingredients[i].flavor * amounts[i];
		textureScore += ingredients[i].texture * amounts[i];
	}
	return std::max(0l, capacityScore) * std::max(0l, durabilityScore) * std::max(0l, flavorScore) * std::max(0l, textureScore);
}

bool
nextCombination(std::vector<unsigned char> &counters, size_t pos = 0)
{
	if (counters[pos] == spoons) {
		if (pos + 1 == counters.size()) {
			return false;
		} else {
			bool ret = nextCombination(counters, pos + 1);
			counters[pos] = counters[pos + 1];
			return ret;
		}
	} else {
		++counters[pos];
		return true;
	}
}

std::vector<unsigned char> &
countersToAmounts(std::vector<unsigned char> const &counters, std::vector<unsigned char> &amounts)
{
	amounts[0] = spoons - counters[0];
	for (size_t i = 1; i < amounts.size(); ++i) {
		amounts[i] = counters[i - 1] - (i < counters.size() ? counters[i] : 0);
	}
	return amounts;
}

std::array<solutionType, 2>
solve(std::istream &input)
{
	std::array<solutionType, 2> maxScore{0};
	std::vector<Ingredient> ingredients;
	std::string line;
	while (input) {
		getline(input, line);
		if (line.empty()) {
			break;
		}
		std::vector<int> values;
		values.reserve(5);
		for (size_t i = line.find_first_of("0123456789-"); i < line.size(); i = line.find_first_of("0123456789-", i)) {
			char *end;
			int n = std::strtol(&line.c_str()[i], &end, 10);
			values.push_back(n);
			i = end - line.c_str();
		}
		ingredients.push_back({values[0], values[1], values[2], values[3], values[4]});
	}
	std::vector<unsigned char> amounts(ingredients.size(), 0);
	std::vector<unsigned char> counters(ingredients.size() - 1, 0);

	do {
		auto s = score(ingredients, countersToAmounts(counters, amounts));
		maxScore[0] = std::max(maxScore[0], s);
		long calories(0);
		for (size_t i = 0; i < ingredients.size() and i < amounts.size(); ++i) {
			calories += ingredients[i].calories * amounts[i];
		}
		if (calories == calorieTarget) {
			maxScore[1] = std::max(maxScore[1], s);
		}
	} while (nextCombination(counters));

	return maxScore;
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

