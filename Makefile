# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++20 -Wall -O3 

# Source file
SRC = pthread.cpp timer.cpp

# Executable name
TARGET = prog

# Build rule
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Run rule
run: $(TARGET)
	./$(TARGET)

# Clean rule
clean:
	rm -f $(TARGET)