CXX=g++
CXXFLAGS=-Wall -O0 -I../../include/
TARGET=main
SOURCES=main.cpp

.PHONY: all clean run

all: $(TARGET)

clean:
	rm -f $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

run: $(TARGET)
	if [ -f solution ]; then \
		diff -y <(time ./$(TARGET) input) solution \
			&& echo 'Solution is correct' \
			|| echo 'Solution is incorrect'; \
	else \
		time ./$(TARGET) <input | tee solution; \
	fi
