# Calc From Scratch - build every lesson with one tool.
#
#   make            build lessons 01-07 and run the tests
#   make lesson03   build one lesson into build/lesson03
#   make test       build and run the lesson 07 tests
#   make gui        build the SFML app (needs SFML 2, see lesson 08)
#   make clean      delete build/

CXX      ?= c++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic -g
BUILD    := build
L        := lessons
ENGINE   := $(L)/06-classes-and-files/calculator.cpp $(L)/06-classes-and-files/calculator.hpp

# SFML 2: use Homebrew's keg-only sfml@2 if present, otherwise pkg-config.
SFML_PREFIX := $(shell brew --prefix sfml@2 2>/dev/null)
ifneq ($(wildcard $(SFML_PREFIX)/include/SFML),)
  SFML_FLAGS := -I$(SFML_PREFIX)/include -L$(SFML_PREFIX)/lib -Wl,-rpath,$(SFML_PREFIX)/lib
else
  SFML_FLAGS := $(shell pkg-config --cflags sfml-graphics 2>/dev/null)
endif
SFML_LIBS := -lsfml-graphics -lsfml-window -lsfml-system

.PHONY: all lessons test gui clean \
        lesson01 lesson02 lesson03 lesson04 lesson05 lesson06 lesson07

all: lessons test

lessons: lesson01 lesson02 lesson03 lesson04 lesson05 lesson06 lesson07

lesson01: $(BUILD)/lesson01
lesson02: $(BUILD)/lesson02
lesson03: $(BUILD)/lesson03
lesson04: $(BUILD)/lesson04
lesson05: $(BUILD)/lesson05
lesson06: $(BUILD)/lesson06
lesson07: $(BUILD)/tests

$(BUILD):
	mkdir -p $(BUILD)

# Lessons 01-05 are a single main.cpp each.
$(BUILD)/lesson01: $(L)/01-hello-calculator/main.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) $< -o $@
$(BUILD)/lesson02: $(L)/02-making-choices/main.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) $< -o $@
$(BUILD)/lesson03: $(L)/03-loops-and-functions/main.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) $< -o $@
$(BUILD)/lesson04: $(L)/04-strings-and-tokens/main.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) $< -o $@
$(BUILD)/lesson05: $(L)/05-recursion-and-precedence/main.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) $< -o $@

# From lesson 06 on, programs are made of several .cpp files.
$(BUILD)/lesson06: $(L)/06-classes-and-files/main.cpp $(ENGINE) | $(BUILD)
	$(CXX) $(CXXFLAGS) $(L)/06-classes-and-files/main.cpp $(L)/06-classes-and-files/calculator.cpp -o $@

$(BUILD)/tests: $(L)/07-testing/tests.cpp $(ENGINE) | $(BUILD)
	$(CXX) $(CXXFLAGS) $(L)/07-testing/tests.cpp $(L)/06-classes-and-files/calculator.cpp -o $@

test: $(BUILD)/tests
	./$(BUILD)/tests

gui: $(BUILD)/gui

$(BUILD)/gui: $(L)/08-gui-with-sfml/main.cpp $(ENGINE) | $(BUILD)
	$(CXX) $(CXXFLAGS) $(L)/08-gui-with-sfml/main.cpp $(L)/06-classes-and-files/calculator.cpp \
	    $(SFML_FLAGS) $(SFML_LIBS) -o $@

clean:
	rm -rf $(BUILD)
