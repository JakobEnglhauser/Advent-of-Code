#include <iostream>
#include <array>
#include <fstream>
#include <vector>

using solutionType = unsigned long;

solutionType
checksumBlock(size_t pos, unsigned char size, size_t id)
{
	solutionType checksum{0};
	for (size_t i = pos; i < pos + size; ++i) {
		checksum += i;
	}
	return checksum * id;
}


std::array<solutionType, 2>
solve(std::istream &input)
{
	std::array<solutionType, 2> checksum{0};
	std::vector<char> diskMap;
	std::string line;
	getline(input, line);
	diskMap.reserve(line.size());
	for (auto const c : line) {
		diskMap.push_back(c - '0');
	}
	/* Part 1 */
	for (size_t pos = 0, i = 0, j = diskMap.size() - 1; i <= j; ++i) {
		auto &size = diskMap[i];
		if (i % 2 == 0) {          /* used block */
			checksum[0] += checksumBlock(pos, size, i / 2);
			pos += size;
		} else {                   /* free block */
			while (size > 0) {
				checksum[0] += checksumBlock(pos, std::min(size, diskMap[j]), j / 2);
				pos += std::min(size, diskMap[j]);
				size -= diskMap[j];
				diskMap[j] -= (size + diskMap[j]);
				j -= diskMap[j] <= 0 ? 2 : 0;
			}
		}
	}
	/* Reset */
	diskMap.clear();
	for (auto const c : line) {
		diskMap.push_back(c - '0');
	}
	/* Part 2 */
	for (size_t pos = 0, i = 0; i < diskMap.size(); ++i) {
		auto &size = diskMap[i];
		if (size < 0) {            /* moved block */
			pos -= size;
		} else if (i % 2 == 0) {   /* used block */
			checksum[1] += checksumBlock(pos, size, i / 2);
			pos += size;
		} else {                   /* free block */
			while (size > 0) {
				size_t j;
				for (j = diskMap.size() - 1; j > i; j -= 2) {
					if (diskMap[j] > 0 and diskMap[j] <= size) {
						break;
					}
				}
				if (j <= i) {
					/* no block fits inside free space */
					pos += size;
					break;
				}
				checksum[1] += checksumBlock(pos, diskMap[j], j / 2);
				pos += diskMap[j];
				size -= diskMap[j];
				diskMap[j] *= -1; /* mark as moved */
			}
		}
	}
	return checksum;
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

