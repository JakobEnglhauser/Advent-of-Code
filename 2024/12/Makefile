SIZE=140
CXX=g++
CXXFLAGS=-Wall -O3 -I../../include/ -std=c++2b -DSIZE=$(SIZE)
TARGET=main
SOURCES=main.cpp

.PHONY: all clean run

all: $(TARGET)

clean:
	rm -f $(TARGET)

$(TARGET): $(SOURCES)
	@echo Input is assumed to be a square grid with side length $(SIZE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

run: $(TARGET)
	if [ -f solution ]; then \
		diff -y <(time ./$(TARGET) input) solution \
			&& echo 'Solution is correct' \
			|| echo 'Solution is incorrect'; \
	else \
		time ./$(TARGET) <input | tee solution; \
	fi
