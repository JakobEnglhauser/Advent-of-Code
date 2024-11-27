#include <regex>
#include <string>
#include <iostream>

template<typename T>
void parseMatch(std::ssub_match const &match, T& var)
{
	var = match;
}

template<>
void parseMatch(std::ssub_match const &match, int& var)
{
	var = std::stoi(match.str());
}

template<>
void parseMatch(std::ssub_match const &match, unsigned long& var)
{
	var = std::stoul(match.str());
}

template<>
void parseMatch(std::ssub_match const &match, char& var)
{
	var = match.str()[0];
}

template<typename T>
size_t
regexScan(std::smatch::const_iterator begin, std::smatch::const_iterator const &end, T &var)
{
	if (begin == end) {
		return 0;
	}
	if (begin->matched) {
		parseMatch(*begin, var);
	}
	return 1;
}

template<typename T, typename... Variables>
size_t
regexScan(std::smatch::const_iterator begin, std::smatch::const_iterator const &end, T &var, Variables &... variables)
{
	if (begin == end) {
		return 0;
	}
	if (begin->matched) {
		parseMatch(*begin, var);
	}
	return 1 + regexScan(begin + 1, end, variables...);
}

template<typename ...Variables>
size_t
regexScan(std::string const &str, std::regex const &regex, Variables &... variables)
{
	std::smatch match;
	if (not std::regex_search(str, match, regex)) {
		return 0;
	}
	return regexScan(match.begin() + 1, match.end(), variables...);
}
