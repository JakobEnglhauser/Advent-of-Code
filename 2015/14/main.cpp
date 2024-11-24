#include <iostream>
#include <array>
#include <fstream>
#include <string>
#include <vector>

using solutionType = unsigned int;

constexpr unsigned int endTime = 2503;

struct Reindeer {
	unsigned int const speed;
	unsigned int const airTime;
	unsigned int const restTime;

	unsigned int
	distance(unsigned int time) const {
		auto const cycleTime = airTime + restTime;
		unsigned int cycles = time / cycleTime;
		unsigned int totalAirTime = cycles * airTime + std::min(airTime, time - cycles * cycleTime);
		return totalAirTime * speed;
	}
};

std::array<solutionType, 2>
solve(std::istream &input)
{
	solutionType maxDistance(0);
	std::vector<Reindeer> reindeer;
	std::vector<solutionType> points;
	std::string line;
	while (input) {
		getline(input, line);
		if (line.empty()) {
			break;
		}
		std::vector<unsigned int> values;
		values.reserve(3);
		for (size_t i = line.find_first_of("0123456789"); i < line.size(); i = line.find_first_of("0123456789", i)) {
			char *end;
			unsigned int n = std::strtoul(&line.c_str()[i], &end, 10);
			values.push_back(n);
			i = end - line.c_str();
		}
		reindeer.push_back({ values[0], values[1], values[2] });
		maxDistance = std::max(maxDistance, reindeer.back().distance(endTime));
	}
	points.resize(reindeer.size(), 0);
	for (unsigned int t = 1; t <= endTime; ++t) {
		unsigned int maxDistance(0);
		std::vector<size_t> winners;
		for (size_t i = 0; i < reindeer.size(); ++i) {
			auto const d = reindeer[i].distance(t);
			if (d > maxDistance) {
				maxDistance = d;
				winners.clear();
				winners.push_back(i);
			} else if (d == maxDistance) {
				winners.push_back(i);
			}
		}
		for (auto const i : winners) {
			++points[i];
		}
	}
	solutionType maxPoints(0);
	for (auto const p : points) {
		maxPoints = std::max(maxPoints, p);
	}
	return { maxDistance, maxPoints };
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

