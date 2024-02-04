# Compiler
CXX = g++

N = 5000
THREADS = 5

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -O3

# Source file
SRC = pthread.cpp timer.cpp

# Executable name
TARGET = prog

# Build rule
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Run rule
run:$(TARGET)
	./$(TARGET) $(N) $(THREADS)

# Clean rule
clean:
	rm -f $(TARGET)