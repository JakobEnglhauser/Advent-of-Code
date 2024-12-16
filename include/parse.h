#include <regex>
#include <string>
#include <iostream>
#include <vector>

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
void parseMatch(std::ssub_match const &match, long& var)
{
	var = std::stol(match.str());
}

template<>
void parseMatch(std::ssub_match const &match, unsigned int& var)
{
	var = std::stoul(match.str());
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

template<typename T>
size_t
regexScan(std::smatch::const_iterator begin, std::smatch::const_iterator const &end, std::vector<T> &var)
{
	++begin; /* first match is whole match not capture groups */
	for (; begin != end; ++begin) {
		if (begin->matched) {
			T val;
			parseMatch(*begin, val);
			var.push_back(val);
		}
	}
	return 1;
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

template<typename T>
size_t
regexScan(std::string const &str, std::regex const &regex, std::vector<T> &var)
{
	auto const matchBegin = std::sregex_iterator(str.begin(), str.end(), regex);
	auto const matchEnd = std::sregex_iterator();
	size_t matches{0};
	for (auto i = matchBegin; i != matchEnd; ++i) {
		matches += regexScan(i->begin(), i->end(), var);
	}
	return matches;
}
