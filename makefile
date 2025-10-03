# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -pthread -I./include

# Source files
SRC = main.cpp src/searchForFile.cpp

# Target executable
TARGET = myfind

# Default target: build everything
all: $(TARGET)

# Link sources into executable
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Clean target: remove executable
clean:
	rm -f $(TARGET)
