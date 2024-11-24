#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <string_view>
#include <string>
#include <iostream>
#include <set>
#include <map>

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

template<typename T>
std::ostream &
operator<<(std::ostream &stream, std::vector<T> const &container)
{
	stream << "[ ";
	for (auto const &i : container) {
		stream << i << " ";
	}
	stream << "]";
	return stream;
}

template<typename T>
std::ostream &
operator<<(std::ostream &stream, std::set<T> const &container)
{
	stream << "{ ";
	for (auto const &i : container) {
		stream << i << " ";
	}
	stream << "}";
	return stream;
}

template<typename K, typename V>
std::ostream &
operator<<(std::ostream &stream, std::map<K, V> const &container)
{
	stream << "{ ";
	for (auto const &[k, v] : container) {
		stream << k << ": " << v << " ";
	}
	stream << "}";
	return stream;
}

#endif

