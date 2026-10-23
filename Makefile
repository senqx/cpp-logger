CXX ?= g++
CPPFLAGS += -Iinclude
CXXFLAGS += -std=c++17 -Wall -Wextra -Werror -pthread
LDLIBS += -pthread

.PHONY: all release debug test clean
all: release
release: bin/logger_test_release
debug: bin/logger_test_debug

obj/release/logger.o: src/logger.cpp include/logger.h
	mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -O3 -DNDEBUG -MMD -MP -c $< -o $@
obj/debug/logger.o: src/logger.cpp include/logger.h
	mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -O0 -g -UNDEBUG -MMD -MP -c $< -o $@
bin/logger_test_release: examples/demo.cpp obj/release/logger.o include/logger.h
	mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -O3 -DNDEBUG examples/demo.cpp obj/release/logger.o $(LDLIBS) -o $@
bin/logger_test_debug: examples/demo.cpp obj/debug/logger.o include/logger.h
	mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -O0 -g -UNDEBUG examples/demo.cpp obj/debug/logger.o $(LDLIBS) -o $@
test: release debug
	python3 tests/test_logger.py
clean:
	rm -rf bin obj

-include obj/release/logger.d obj/debug/logger.d
