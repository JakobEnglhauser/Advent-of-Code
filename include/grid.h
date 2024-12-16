#ifndef GRID_H
#define GRID_H

#include <stdexcept>
#include <iostream>
#include <functional>
#include <vector>

/**
 * 2-dimensional heap allocated array
 */
template<typename T, size_t X, size_t Y = X>
class Grid {
public:
	explicit Grid() : data(new T[X * Y]) { }

	explicit Grid(T const &value) : data(new T[X * Y]) {
		std::fill(data, data + X * Y, value);
	}

	~Grid() {
		delete[] data;
	}

	size_t
	size() const {
		return X * Y;
	}

	Grid &
	operator=(Grid<T, X, Y> const &other) {
		for (size_t i = 0; i < X * Y; ++i) {
			(*this)[i] = other[i];
		}
		return *this;
	}

	T &
	operator[](size_t i) {
		if (i >= X * Y) {
			throw std::out_of_range("Grid index out of bounds");
		}
		return data[i];
	}

	T const &
	operator[](size_t i) const {
		if (i >= X * Y) {
			throw std::out_of_range("Grid index out of bounds");
		}
		return data[i];
	}

	T &
	operator[](size_t x, size_t y) {
		if (x >= X or y >= Y) {
			throw std::out_of_range("Grid index out of bounds");
		}
		return data[x * Y + y];
	}

	T const &
	operator[](size_t x, size_t y) const {
		if (x >= X or y >= Y) {
			throw std::out_of_range("Grid index out of bounds");
		}
		return data[x * Y + y];
	}

	void
	apply(void (*stencil)(T const &value)) {
		for (size_t i = 0; i < X * Y; ++i) {
			stencil((*this)[i]);
		}
	}

	void
	apply9(void (*stencil)(T &target, T const &value, std::vector<std::reference_wrapper<T const>> const &neighbors)) {
		Grid<T, X, Y> targetGrid;
		size_t x(0);
		size_t y(0);
		stencil(targetGrid[x, y], (*this)[x, y],
				{ (*this)[x, y + 1],
				  (*this)[x + 1, y], (*this)[x + 1, y + 1] });
		for (y = 1; y < Y - 1; ++y) {
			stencil(targetGrid[x, y], (*this)[x, y],
					{ (*this)[x, y - 1], (*this)[x, y + 1],
					  (*this)[x + 1, y - 1], (*this)[x + 1, y], (*this)[x + 1, y + 1] });
		}
		stencil(targetGrid[x, y], (*this)[x, y],
				{ (*this)[x, y - 1],
				  (*this)[x + 1, y - 1], (*this)[x + 1, y] });
		for (x = 1; x < X - 1; ++x) {
			y = 0;
			stencil(targetGrid[x, y], (*this)[x, y],
					{ (*this)[x - 1, y], (*this)[x - 1, y + 1],
					  (*this)[x, y + 1],
					  (*this)[x + 1, y], (*this)[x + 1, y + 1]});
			for (y = 1; y < Y - 1; ++y) {
				stencil(targetGrid[x, y], (*this)[x, y],
						{ (*this)[x - 1, y - 1], (*this)[x - 1, y], (*this)[x - 1, y + 1],
						  (*this)[x, y - 1], (*this)[x, y + 1],
						  (*this)[x + 1, y - 1], (*this)[x + 1, y], (*this)[x + 1, y + 1] });
			}
			stencil(targetGrid[x, y], (*this)[x, y],
					{ (*this)[x - 1, y - 1], (*this)[x - 1, y],
					  (*this)[x, y - 1],
					  (*this)[x + 1, y - 1], (*this)[x + 1, y] });
		}
		y = 0;
		stencil(targetGrid[x, y], (*this)[x, y],
				{ (*this)[x - 1, y], (*this)[x - 1, y + 1],
				  (*this)[x, y + 1] });
		for (y = 1; y < Y - 1; ++y) {
			stencil(targetGrid[x, y], (*this)[x, y],
					{ (*this)[x - 1, y - 1], (*this)[x - 1, y], (*this)[x - 1, y + 1],
					  (*this)[x, y - 1], (*this)[x, y + 1] });
		}
		stencil(targetGrid[x, y], (*this)[x, y],
				{ (*this)[x - 1, y - 1], (*this)[x - 1, y],
				  (*this)[x, y - 1] });
		std::swap(targetGrid.data, this->data);
	}

	size_t
	count(T const &value) const {
		size_t c(0);
		for (size_t i = 0; i < X * Y; ++i) {
			c += ((*this)[i] == value) ? 1 : 0;
		}
		return c;
	}

private:
	T *data;

};

template<typename T, size_t X, size_t Y = X>
std::ostream&
operator<<(std::ostream &stream, const Grid<T, X, Y> &grid)
{
	for (size_t i = 0; i < X; ++i) {
		for (size_t j = 0; j < Y; ++j) {
			stream << grid[i, j] << (j < Y - 1 ? " " : "");
		}
		stream << (i < X - 1 ? "\n" : "");
	}
	return stream;
}

template<typename T, size_t X, size_t Y = X>
bool
operator>>(std::istream &stream, Grid<T, X, Y> &grid)
{
	for (size_t i = 0; i < X * Y; ++i) {
		if (not (stream >> grid[i])) {
			return false;
		}
	}
	return true;
}

#endif

