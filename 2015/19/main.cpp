#include <iostream>
#include <array>
#include <fstream>
#include <set>
#include <map>
#include <list>
#include <iterator>

#include "util.h"
#include "debug.h"

using solutionType = size_t;

//using Atom = std::string;

struct Atom
{
	unsigned char id;

	/**
	 * Assumes str consists of exactly 1 lower case letter or 1 upper case letter
	 * optionally followed by 1 lower case letter.
	 */
	Atom(std::string const &str) {
		id = (str[0] >= 'a' and str[0] <= 'z') ?
			str[0] - 'a' + 1
			: ((str[0] - 'A' + 1) << 4) | (str.size() > 1 ? str[1] - 'a' + 1 : 0);
	}

	bool
	operator==(Atom const &other) const {
		return id == other.id;
	}

	bool
	operator!=(Atom const &other) const {
		return id != other.id;
	}

	bool
	operator<(Atom const &other) const {
		return id < other.id;
	}
};

std::ostream &
operator<<(std::ostream &stream, Atom const &atom)
{
	if ((atom.id & 0xf0) > 0) {
		stream << static_cast<char>((atom.id >> 4) - 1 + 'A');
	}
	if ((atom.id & 0x0f) > 0) {
		stream << static_cast<char>((atom.id & 0x0f) - 1 + 'a');
	}
	return stream;
}

struct Molecule
{
	std::vector<Atom> atoms;

	bool
	operator<(Molecule const &rhs) const {
		if (atoms.size() != rhs.atoms.size()) {
			return atoms.size() < rhs.atoms.size();
		}
		for (auto i = atoms.begin(), j = rhs.atoms.begin(); i != atoms.end(); ++i, ++j ) {
			if (*i != *j) {
				return *i < *j;
			}
		}
		return false; /* lhs == rhs */
	}
};

std::ostream &
operator<<(std::ostream &stream, Molecule const &molecule)
{
	stream << molecule.atoms;
	return stream;
}

std::set<Molecule>
expand(Molecule const &molecule, std::multimap<Atom const &, Molecule> const &rules)
{
	std::set<Molecule> creations;
	for (auto a = molecule.atoms.begin(); a != molecule.atoms.end(); ++a) {
		auto [start, end] = rules.equal_range(*a);
		for (auto r = start; r != end; ++r) {
			Molecule m;
			m.atoms.reserve(molecule.atoms.size() + r->second.atoms.size() - 1);
			std::copy(molecule.atoms.begin(), a, std::back_insert_iterator(m.atoms));
			std::copy(r->second.atoms.begin(), r->second.atoms.end(), std::back_insert_iterator(m.atoms));
			std::copy(a + 1, molecule.atoms.end(), std::back_insert_iterator(m.atoms));
			creations.insert(std::move(m));
		}
	}
	return creations;
}

std::set<Molecule> &
expand(Molecule const &molecule, std::multimap<Atom const &, Molecule> const &rules, std::set<Molecule> &creations, Molecule const &target)
{
	for (auto a = molecule.atoms.begin();
		 a != molecule.atoms.end() and a != std::mismatch(molecule.atoms.begin(), molecule.atoms.end(), target.atoms.begin(), target.atoms.end()).first + 1;
		 ++a) {
		auto [start, end] = rules.equal_range(*a);
		for (auto r = start; r != end; ++r) {
			Molecule m;
			m.atoms.reserve(molecule.atoms.size() + r->second.atoms.size() - 1);
			std::copy(molecule.atoms.begin(), a, std::back_insert_iterator(m.atoms));
			std::copy(r->second.atoms.begin(), r->second.atoms.end(), std::back_insert_iterator(m.atoms));
			std::copy(a + 1, molecule.atoms.end(), std::back_insert_iterator(m.atoms));
			creations.insert(std::move(m));
		}
	}
	return creations;
}

std::set<Molecule>
expand(std::set<Molecule> const &molecules, std::multimap<Atom const &, Molecule> const &rules, Molecule const &target)
{
	std::set<Molecule> creations;
	for (auto const &m : molecules) {
		expand(m, rules, creations, target);
	}
	return creations;
}

std::array<solutionType, 2>
solve(std::istream &input)
{
	std::array<solutionType, 2> solution{0};
	std::set<Atom> symbols;
	std::multimap<Atom const &, Molecule> rules;
	//std::multimap<Molecule, Atom const &> rules;
	std::string line;
	while (input) {
		getline(input, line);
		if (line.empty()) {
			break;
		}
		auto rule = split(line, " => ");
		Atom s{std::string(rule[0])};
		if (not (symbols.contains(s))) {
			symbols.insert(s);
		}
		auto search = symbols.find(s);
		Atom const &lhs = *search;
		Molecule rhs;
		for (char const *start = &rule[1][0], *end = start + 1; *start != '\0' ; ++end) {
			if (*end == '\0' or (*end >= 'A' and *end <= 'Z')) {
				rhs.atoms.emplace_back(std::string(start, end));
				start = end;
			}
		}
		rules.emplace(lhs, rhs);
	}
	getline(input, line);
	Molecule molecule;
	for (char const *start = &line[0], *end = start + 1; *start != '\0' ; ++end) {
		if (*end == '\0' or (*end >= 'A' and *end <= 'Z')) {
			molecule.atoms.emplace_back(std::string(start, end));
			start = end;
		}
	}

	std::cout << symbols << std::endl;
	std::cout << molecule << std::endl;
	std::cout << rules << std::endl;

	solution[0] = expand(molecule, rules).size();

	auto creations = expand(Molecule({Atom("e")}), rules);
	for (unsigned int i = 1; i < 20; ++i) {
		if (creations.contains(molecule)) {
			solution[1] = i;
			break;
		}
		std::cout << i << ": " << creations.size() << "\n";
		creations = expand(creations, rules, molecule);
	}

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

