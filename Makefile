CXX ?= c++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic -g
.DEFAULT_GOAL := all
.PHONY: all test lesson01 lesson02 lesson03 lesson04 lesson05 lesson06
all: lesson01 lesson02 lesson03 lesson04 lesson05 lesson06
build:
	mkdir -p build
lesson01: build/lesson01
build/lesson01: lessons/01-hello-calculator/main.cpp | build
	$(CXX) $(CXXFLAGS) lessons/01-hello-calculator/main.cpp -o $@
lesson02: build/lesson02
build/lesson02: lessons/02-making-choices/main.cpp | build
	$(CXX) $(CXXFLAGS) lessons/02-making-choices/main.cpp -o $@
lesson03: build/lesson03
build/lesson03: lessons/03-loops-and-functions/main.cpp | build
	$(CXX) $(CXXFLAGS) lessons/03-loops-and-functions/main.cpp -o $@
lesson04: build/lesson04
build/lesson04: lessons/04-strings-and-tokens/main.cpp | build
	$(CXX) $(CXXFLAGS) lessons/04-strings-and-tokens/main.cpp -o $@
lesson05: build/lesson05
build/lesson05: lessons/05-recursion-and-precedence/main.cpp | build
	$(CXX) $(CXXFLAGS) lessons/05-recursion-and-precedence/main.cpp -o $@
lesson06: build/lesson06
build/lesson06: lessons/06-classes-and-files/main.cpp lessons/06-classes-and-files/calculator.cpp lessons/06-classes-and-files/calculator.hpp | build
	$(CXX) $(CXXFLAGS) lessons/06-classes-and-files/main.cpp lessons/06-classes-and-files/calculator.cpp -o $@
