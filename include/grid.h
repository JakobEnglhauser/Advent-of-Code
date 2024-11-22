#ifndef GRID_H
#define GRID_H

#include <vector>
#include <stdexcept>

template<typename T, size_t X, size_t Y>
class Grid {
public:
	explicit Grid() : data(new T[X * Y]) { }

	explicit Grid(T const &value) : data(new T[X * Y]) {
		std::fill(data, data + X * Y, value);
	}

	~Grid() {
		delete[] data;
	}

	size_t size() const {
		return X * Y;
	}

	T &operator[](size_t i) {
		if (i >= X * Y) {
			throw std::out_of_range("Grid index out of bounds");
		}
		return data[i];
	}

	T const &operator[](size_t i) const {
		if (i >= X * Y) {
			throw std::out_of_range("Grid index out of bounds");
		}
		return data[i];
	}

	T &operator[](size_t x, size_t y) {
		if (x >= X or y >= Y) {
			throw std::out_of_range("Grid index out of bounds");
		}
		return data[x * Y + y];
	}

	T const &operator[](size_t x, size_t y) const {
		if (x >= X or y >= Y) {
			throw std::out_of_range("Grid index out of bounds");
		}
		return data[x * Y + y];
	}

private:
	T *data;

};

#endif

