// Lesson 06 - main.cpp
//
// A command-line front end for calc::Calculator. All the math lives in
// calculator.cpp. This file only handles talking to the user.

#include <iostream>
#include <string>

#include "calculator.hpp"

void printHelp() {
    std::cout << "Examples:  2 + 3 * 4    (1 + 2) ^ 2    sqrt(16)    ans / 2    pi * 2\n"
              << "Commands:  :history  :clear  :help  :quit\n";
}

int main() {
    calc::Calculator calculator;   // create one Calculator object
    printHelp();

    std::string line;
    while (std::cout << "> " && std::getline(std::cin, line)) {
        if (line.empty()) {
            continue;
        }
        if (line == ":quit" || line == ":q") {
            break;
        }
        if (line == ":help") {
            printHelp();
        } else if (line == ":clear") {
            calculator.clear();
            std::cout << "  history cleared, ans = 0\n";
        } else if (line == ":history") {
            // `auto` lets the compiler figure out the type (HistoryEntry here)
            for (const auto& entry : calculator.history()) {
                std::cout << "  " << entry.expression << " = "
                          << calc::Calculator::format(entry.result) << '\n';
            }
        } else {
            try {
                double result = calculator.evaluate(line);
                std::cout << "  = " << calc::Calculator::format(result) << '\n';
            } catch (const calc::Error& error) {
                std::cout << "  ! " << error.what() << '\n';
            }
        }
    }
    return 0;
}
