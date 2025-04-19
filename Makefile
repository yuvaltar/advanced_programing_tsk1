# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Source files
SRC = main.cpp BloomFilter.cpp BlackList.cpp HashFunctions.cpp
OBJ = $(SRC:.cpp=.o)

# Output binary
TARGET = main

# Build rule
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Clean object files and binary
clean:
	rm -f $(OBJ) $(TARGET)

