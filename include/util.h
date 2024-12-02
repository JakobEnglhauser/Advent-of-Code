#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <string_view>
#include <string>
#include <cstdlib>

/***
 * split std::string_view string into substrings delimited by delim.
 */
std::vector<std::string_view>
split(std::string_view const &string, std::string const &delim)
{
	std::vector<std::string_view> splits;
	auto s = string.substr(0, string.find(delim));
	if (not s.empty()) {
		splits.push_back(s);
	}
	for (size_t pos = string.find(delim);
		 pos < string.size();
		 pos = string.find(delim, pos + delim.size())) {
		auto s = string.substr(pos + delim.size(), string.find(delim, pos + delim.size()) - pos - delim.size());
		if (not s.empty()) {
			splits.push_back(s);
		}
	}
	return splits;
}

template<typename N>
std::vector<N>
toInts(std::string const &string, int base = 0)
{
	std::vector<N> ints;
	char *end;
	ints.push_back(std::strtol(string.c_str(), &end, base));
	while (*end != '\0') {
		ints.push_back(std::strtol(end, &end, base));
	}
	return ints;
}

#endif

