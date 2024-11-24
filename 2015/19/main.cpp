#include <iostream>
#include <array>
#include <fstream>
#include <set>
#include <map>

#include "util.h"

using solutionType = size_t;

std::set<std::string>
expandMolecules(std::set<std::string> const &molecules, std::map<std::string, std::set<std::string>> replacements, std::string const &target = "")
{
	std::set<std::string> creations;
	for (auto const &molecule : molecules) {
		for (auto const &[in, repl] : replacements) {
			for (auto const &r : repl) {
				for (size_t pos = molecule.find(in); pos < molecule.size(); pos = molecule.find(in, pos + 1)) {
					if (not target.empty()
						and pos > std::distance(target.begin(), std::get<0>(std::mismatch(target.begin(), target.end(), molecule.begin())))) {
						break;
					}
					std::string out;
					out.reserve(molecule.size() - in.size() + r.size());
					std::copy(molecule.begin(), molecule.begin() + pos, std::back_inserter(out));
					std::copy(r.begin(), r.end(), std::back_inserter(out));
					std::copy(molecule.begin() + pos + in.size(), molecule.end(), std::back_inserter(out));
					creations.insert(out);
				}
			}
		}
	}
	return creations;
}

std::set<std::string>
expandMolecules(std::string const &molecule, std::map<std::string, std::set<std::string>> replacements)
{
	std::set<std::string> molecules;
	molecules.insert(molecule);
	return expandMolecules(molecules, replacements);
}

std::array<solutionType, 2>
solve(std::istream &input)
{
	std::array<solutionType, 2> solution{0};
	std::map<std::string, std::set<std::string>> replacements;
	std::string line;
	while (input) {
		getline(input, line);
		if (line.empty()) {
			break;
		}
		auto rule = split(line, " => ");
		replacements[std::string(rule[0])].insert(std::string(rule[1]));
	}
	getline(input, line);
	/* Part 1 */
	auto creations = expandMolecules(line, replacements);
	solution[0] = creations.size();
	/* Part 2 */
	creations.clear();
	creations.insert("e");
	size_t i;
	for (i = 0; not (creations.contains(line) or creations.empty()); ++i) {
		std::erase_if(creations, [&line](auto const &c) { return c.size() >= line.size(); });
		creations = expandMolecules(creations, replacements, line);
		break; // TODO
	}
	solution[1] = i;

	return solution;
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

