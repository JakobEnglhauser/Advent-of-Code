#include <iostream>
#include <array>
#include <fstream>
#include <openssl/md5.h>

using solutionType = unsigned long;

template<unsigned int numZeros>
solutionType
md5zeros(std::string const &prefix)
{
	for (solutionType n = 0; ; ++n) {
		std::string const numberString = std::to_string(n);
		unsigned char hash[MD5_DIGEST_LENGTH];
		MD5_CTX md5;
		MD5_Init(&md5);
		MD5_Update(&md5, prefix.c_str(), prefix.size());
		MD5_Update(&md5, numberString.c_str(), numberString.size());
		MD5_Final(hash, &md5);

		bool match = true;
		unsigned int i;
		for (i = 0; i < numZeros / 2; ++i) {
			if (hash[i] != 0) {
				match = false;
				break;
			}
		}
		if (match and ((numZeros % 2) == 0 ? true : ((hash[i] & 0xf0) == 0))) {
			return n;
		}
	}
}

std::array<solutionType, 2>
solve(std::istream &input)
{
	std::string line;
	input >> line;
	return { md5zeros<5>(line), md5zeros<6>(line) };
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

