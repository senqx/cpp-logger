# Compiler settings
CXX         = g++
CXXFLAGS    = -Wall -Wextra -Werror -Iinclude

# Paths
SRC         = src/logger.cpp
EXAMPLES    = examples/demo.cpp
OBJ_DIR     = obj
BIN_DIR     = bin
OBJ         = $(OBJ_DIR)/logger.o

# Executables
RELEASE_TARGET = $(BIN_DIR)/logger_test_release
DEBUG_TARGET   = $(BIN_DIR)/logger_test_debug

# Build options
RELEASE_CXXFLAGS = -O3 -DNDEBUG
DEBUG_CXXFLAGS   = -g -DDEBUG

# Default target (release)
all: release

# Ensure required directories exist
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Release build (Optimized, removes debug info)
release: CXXFLAGS += $(RELEASE_CXXFLAGS)
release: $(BIN_DIR) $(OBJ_DIR) $(RELEASE_TARGET)

# Debug build (Includes debugging symbols)
debug: CXXFLAGS += $(DEBUG_CXXFLAGS)
debug: $(BIN_DIR) $(OBJ_DIR) $(DEBUG_TARGET)

# Compilation rules
$(RELEASE_TARGET): $(OBJ) $(EXAMPLES) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ) $(EXAMPLES)

$(DEBUG_TARGET): $(OBJ) $(EXAMPLES) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ) $(EXAMPLES)

# Object file compilation (incremental builds)
$(OBJ): $(SRC) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $(SRC) -o $(OBJ)

# Clean build artifacts (removes binaries and object files)
clean:
	rm -f $(OBJ) $(RELEASE_TARGET) $(DEBUG_TARGET)
	rm -rf $(BIN_DIR) $(OBJ_DIR)
