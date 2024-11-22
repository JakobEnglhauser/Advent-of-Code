#include <iostream>
#include <array>
#include <fstream>
#include <unordered_map>
#include <cstdint>
#include <string>
#include <regex>

using solutionType = uint16_t;

struct Part {
	enum Op {
		NOP = 0,
		AND = 'A',
		OR = 'O',
		LSHIFT = 'L',
		RSHIFT = 'R',
		NOT = 'N',
	};

	Op op;
	std::array<std::string, 2> in;
	uint16_t signal;
	bool hasSignal;

	Part() : op(NOP), in({"", ""}), hasSignal(false) { }

	Part(Op op, std::string const &in1, std::string const &in2) : op(op), in({in1, in2}), hasSignal(false) { }
};

uint16_t
getSignal(std::string const &wire, std::unordered_map<std::string, Part> &parts)
{
	if (wire[0] >= '0' and wire[0] <= '9') {
		return std::stoul(wire);
	}
	auto &part = parts.at(wire);
	if (part.hasSignal) {
		return part.signal;
	}
	switch (part.op) {
	case Part::Op::NOP:
		part.signal = getSignal(part.in[0], parts);
		part.hasSignal = true;
		return part.signal;
	case Part::Op::AND:
		part.signal = getSignal(part.in[0], parts) & getSignal(part.in[1], parts);
		part.hasSignal = true;
		return part.signal;
	case Part::Op::OR:
		part.signal = getSignal(part.in[0], parts) | getSignal(part.in[1], parts);
		part.hasSignal = true;
		return part.signal;
	case Part::Op::LSHIFT:
		part.signal = getSignal(part.in[0], parts) << getSignal(part.in[1], parts);
		part.hasSignal = true;
		return part.signal;
	case Part::Op::RSHIFT:
		part.signal = getSignal(part.in[0], parts) >> getSignal(part.in[1], parts);
		part.hasSignal = true;
		return part.signal;
	case Part::Op::NOT:
		part.signal = ~getSignal(part.in[1], parts);
		part.hasSignal = true;
		return part.signal;
	default: /* unreachable */
		return 0;
	}
}

std::array<solutionType, 2>
solve(std::istream &input)
{
	std::array<solutionType, 2> signal{{0, 0}};
	/* Parse input */
	std::unordered_map<std::string, Part> parts;
	std::regex lineParser(R"(([0-9a-z]*) ?([A-Z]*) ?([0-9a-z]*) -> ([a-z]*))");
	std::string line;
	while (input) {
		getline(input, line);
		if (line.empty()) {
			break;
		}
		std::smatch match;
		std::regex_match(line, match, lineParser);
		parts.emplace(match[4].str(), Part(static_cast<Part::Op>(match[2].str()[0]), match[1].str(), match[3].str()));
	}
	/* Part 1 */
	signal[0] = getSignal("a", parts);
	/* Reset */
	auto &b = parts.at("b");
	b.op = Part::Op::NOP;
	b.in[0] = std::to_string(signal[0]);
	for (auto &[_, part] : parts) {
		part.hasSignal = false;
	}
	/* Part 2 */
	signal[1] = getSignal("a", parts);
	return signal;
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

