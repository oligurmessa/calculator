CXX ?= c++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic -g
.DEFAULT_GOAL := all
.PHONY: all test lesson01 lesson02
all: lesson01 lesson02
build:
	mkdir -p build
lesson01: build/lesson01
build/lesson01: lessons/01-hello-calculator/main.cpp | build
	$(CXX) $(CXXFLAGS) lessons/01-hello-calculator/main.cpp -o $@
lesson02: build/lesson02
build/lesson02: lessons/02-making-choices/main.cpp | build
	$(CXX) $(CXXFLAGS) lessons/02-making-choices/main.cpp -o $@
