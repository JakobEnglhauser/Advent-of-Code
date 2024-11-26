#include <iostream>
#include <array>
#include <fstream>

#include "parse.h"

using solutionType = size_t;

struct Instruction {
	char instr;
	char reg;
	int imm;

	Instruction(std::string str, char reg, int imm) : reg(reg - 'a'), imm(imm) {
		if (str == "jie") {
			instr = 'e';
		} else if (str == "jio") {
			instr = 'o';
		} else {
			instr = str[0];
		}
	}
};

solutionType
execute(std::vector<Instruction> const &program, std::array<solutionType, 2>registers = {0, 0})
{
	size_t pc(0);
	while (pc < program.size()) {
		auto const &i = program[pc];
		switch (i.instr) {
		case 'h':
			registers[i.reg] /= 2;
			++pc;
			break;
		case 't':
			registers[i.reg] *= 3;
			++pc;
			break;
		case 'i':
			++registers[i.reg];
			++pc;
			break;
		case 'j':
			pc += i.imm;
			break;
		case 'e':
			pc += (registers[i.reg] % 2) == 0 ? i.imm : 1;
			break;
		case 'o':
			pc += (registers[i.reg] == 1) ? i.imm : 1;
			break;
		}
	}
	return registers[1];
}

std::array<solutionType, 2>
solve(std::istream &input)
{
	std::vector<Instruction> program;
	std::regex regex(R"(^(hlf|tpl|inc|jmp|jie|jio) ([ab])?(?:, )?([+-][0-9]+)?$)");
	std::string line;
	while (input) {
		getline(input, line);
		if (line.empty()) {
			break;
		}
		std::string instr;
		char reg;
		int imm;
		regexScan(line, regex, instr, reg, imm);
		program.emplace_back(instr, reg, imm);
	}
	return { execute(program), execute(program, { 1 , 0}) };
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

