# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -g
LDFLAGS = $(shell pkg-config --libs sfml-graphics sfml-window sfml-system sfml-audio)

# Target executable
TARGET = pokemon

# Source and object files
SRC = $(wildcard *.cpp core/*.cpp)
OBJ = $(SRC:.cpp=.o)
DEP = $(OBJ:.o=.d)

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

# Include dependency files
-include $(DEP)

# Compile source files to object files with dependency generation
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Clean up generated files
clean:
	rm -f $(TARGET) $(OBJ) $(DEP)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean run