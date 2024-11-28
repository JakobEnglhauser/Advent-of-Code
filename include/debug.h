#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <ranges>
#include <type_traits>
#include <tuple>
#include <utility>

template<typename ...T>
std::ostream &
operator<<(std::ostream &stream, std::tuple<T...> const &tuple)
{
	stream << "( ";
	for (std::size_t i = 0; i < std::tuple_size(tuple); ++i) {
		stream << std::get<i>(tuple) << " ";
	}
	stream << ")";
	return stream;
}

template<typename T, typename U>
std::ostream &
operator<<(std::ostream &stream, std::pair<T, U> const &tuple)
{
	stream << "( " << tuple.first << " " << tuple.second << " )";
	return stream;
}

template<typename>
struct is_pair : std::false_type{};

template<typename T, typename U>
struct is_pair<std::pair<T, U>> : std::true_type{};

template<typename>
struct is_char_array : std::false_type{};

template<>
struct is_char_array<char []> : std::true_type{};

template<std::size_t N>
struct is_char_array<char [N]> : std::true_type{};

template<std::ranges::common_range C,
	typename = typename std::enable_if<!is_char_array<C>::value && !std::is_same<C, std::string>::value>::type>
std::ostream &
operator<<(std::ostream &stream, C const &container)
{
	stream << "{ ";
	if constexpr (is_pair<typename C::value_type>::value) {
		for (auto const &[k, v] : container) {
			stream << "[" << k << ": " << v << "] ";
		}
	} else {
		for (auto const &i : container) {
			stream << i << " ";
		}
	}
	stream << "}";
	return stream;
}

#endif

