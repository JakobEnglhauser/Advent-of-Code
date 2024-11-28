#include <iostream>
#include <array>
#include <fstream>
#include <limits>
#include <queue>

using solutionType = unsigned int;

constexpr int startingMp{500};
constexpr char startingHp{50};

struct State
{
	solutionType spentMp;
	int playerMp;
	char playerHp;
	char enemyHp;
	char shield;
	char poison;
	char recharge;
};

struct greaterPriority
{
	bool
	operator()(State const &a, State const &b) const {
		return a.spentMp > b.spentMp;
	}
};

void
enemyTurn(State &s, char enemyDmg)
{
	if (s.poison > 0) {
		s.enemyHp -= 3;
		--s.poison;
	}
	if (s.recharge > 0) {
		s.playerMp += 101;
		--s.recharge;
	}
	if (s.shield > 0) {
		s.playerHp -= std::max(1, enemyDmg - 7);
		--s.shield;
	} else {
		s.playerHp -= enemyDmg;
	}
}

template<bool hardMode = false>
solutionType
minMp(char enemyHp, char enemyDmg)
{
	std::priority_queue<State, std::vector<State>, greaterPriority> frontier;
	frontier.push(State{0, startingMp, startingHp, enemyHp, 0, 0, 0});

	while (not frontier.empty()) {
		State s = frontier.top();
		frontier.pop();
		/* Pre-checks */
		if (s.enemyHp <= 0) {
			/* Victory */
			return s.spentMp;
		}
		if constexpr (hardMode) {
			--s.playerHp;
		}
		if (s.playerHp <= 0) {
			/* Death */
			continue;
		}
		/* Player turn */
		if (s.shield > 0) {
			--s.shield;
		}
		if (s.poison > 0) {
			s.enemyHp -= 3;
			--s.poison;
		}
		if (s.recharge > 0) {
			s.playerMp += 101;
			--s.recharge;
		}
		if (s.playerMp >= 229 and s.recharge == 0) { /* Recharge */
			State n{s.spentMp + 229, s.playerMp - 229, s.playerHp, s.enemyHp, s.shield, s.poison, 5};
			enemyTurn(n, enemyDmg);
			frontier.push(n);
		}
		if (s.playerMp >= 173 and s.poison == 0) { /* Poison */
			State n{s.spentMp + 173, s.playerMp - 173, s.playerHp, s.enemyHp, s.shield, 6, s.recharge};
			enemyTurn(n, enemyDmg);
			frontier.push(n);
		}
		if (s.playerMp >= 113 and s.shield == 0) { /* Shield */
			State n{s.spentMp + 113, s.playerMp - 113, s.playerHp, s.enemyHp, 6, s.poison, s.recharge};
			enemyTurn(n, enemyDmg);
			frontier.push(n);
		}
		if (s.playerMp >= 73) { /* Drain */
			State n{s.spentMp + 73, s.playerMp - 73, static_cast<char>(s.playerHp + 2), static_cast<char>(s.enemyHp - 2), s.shield, s.poison, s.recharge};
			enemyTurn(n, enemyDmg);
			frontier.push(n);
		}
		if (s.playerMp >= 53) { /* Magic Missile */
			State n{s.spentMp + 53, s.playerMp - 53, s.playerHp, static_cast<char>(s.enemyHp - 4), s.shield, s.poison, s.recharge};
			enemyTurn(n, enemyDmg);
			frontier.push(n);
		}
	}
	return 0; /* Only reachable if the fight is impossible to win */
}

std::array<solutionType, 2>
solve(std::istream &input)
{
	std::string line;
	int hp, damage;
	input >> line;
	input >> line;
	input >> hp;
	input >> line;
	input >> damage;

	return { minMp<false>(hp, damage), minMp<true>(hp, damage) };
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

