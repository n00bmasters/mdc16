# Python venv
VENV_PATH = $(shell cd .. && pwd)/.venv
VENV_BIN = $(VENV_PATH)/bin
COCAS = $(VENV_BIN)/cocas

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
LDFLAGS = 

# Directories
SRC_DIR = .
BUILD_DIR = build
BIN_DIR = bin
EXAMPLES_DIR = examples

# Target executable
TARGET = $(BIN_DIR)/app

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

# Default target
all: $(TARGET)

# Create directories
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Link
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Compile
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Run
run: $(TARGET)
	./$(TARGET)

# Examples
EXAMPLE_SOURCES = $(wildcard $(EXAMPLES_DIR)/*.asm)
EXAMPLE_TARGETS = $(patsubst $(EXAMPLES_DIR)/%.asm,$(EXAMPLES_DIR)/%.img,$(EXAMPLE_SOURCES))

examples: $(EXAMPLE_TARGETS)

$(EXAMPLES_DIR)/%.img: $(EXAMPLES_DIR)/%.asm
	-$(COCAS) $< -o $@

clean-examples:
	rm -f $(EXAMPLE_TARGETS)

# Phony targets
.PHONY: all clean run examples clean-examples
