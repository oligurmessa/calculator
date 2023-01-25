// Lesson 07 - tests.cpp
//
// Automated tests for calc::Calculator from lesson 06.
// Run them after every change: if something breaks, you find out right away
// instead of when someone else uses your calculator.
//
// New ideas in this file:
//   * writing small test helpers instead of testing by hand
//   * comparing doubles safely (never use == on computed decimals!)
//   * testing that errors happen when they should

#include <cmath>
#include <iostream>
#include <string>

#include "../06-classes-and-files/calculator.hpp"

int passed = 0;
int failed = 0;

// Check that `expression` evaluates to `expected` (within a tiny tolerance).
void expectValue(const std::string& expression, double expected) {
    calc::Calculator calculator;   // fresh calculator for every test
    try {
        double actual = calculator.evaluate(expression);
        if (std::fabs(actual - expected) < 1e-9) {
            ++passed;
        } else {
            ++failed;
            std::cout << "FAIL  " << expression << "  expected " << expected
                      << " but got " << actual << '\n';
        }
    } catch (const calc::Error& error) {
        ++failed;
        std::cout << "FAIL  " << expression << "  threw: " << error.what() << '\n';
    }
}

// Check that `expression` is rejected with a calc::Error.
void expectError(const std::string& expression) {
    calc::Calculator calculator;
    try {
        double actual = calculator.evaluate(expression);
        ++failed;
        std::cout << "FAIL  " << expression << "  should be an error, got " << actual << '\n';
    } catch (const calc::Error&) {
        ++passed;
    }
}

void expectText(const std::string& actual, const std::string& expected) {
    if (actual == expected) {
        ++passed;
    } else {
        ++failed;
        std::cout << "FAIL  format: expected \"" << expected << "\" got \"" << actual << "\"\n";
    }
}

int main() {
    // --- basics -------------------------------------------------------------
    expectValue("1 + 2", 3);
    expectValue("10 - 4", 6);
    expectValue("6 * 7", 42);
    expectValue("9 / 2", 4.5);
    expectValue("  42  ", 42);

    // --- precedence (the whole reason for lesson 05) ------------------------
    expectValue("2 + 3 * 4", 14);
    expectValue("(2 + 3) * 4", 20);
    expectValue("10 - 2 - 3", 5);       // left-to-right for + and -
    expectValue("2 ^ 3 ^ 2", 512);      // right-to-left for ^
    expectValue("-2 ^ 2", -4);
    expectValue("2 ^ -1", 0.5);
    expectValue("--3", 3);

    // --- extras from lesson 06 ----------------------------------------------
    expectValue("10 % 3", 1);
    expectValue("sqrt(16) + abs(-2)", 6);
    expectValue("pi", 3.14159265358979323846);

    // --- things that must fail ----------------------------------------------
    expectError("");
    expectError("1 / 0");
    expectError("5 % 0");
    expectError("(1 + 2");
    expectError("1 +");
    expectError("2 3");
    expectError("1.2.3");
    expectError("sqrt(-1)");
    expectError("banana");
    expectError("3 $ 4");

    // --- state: ans and history ---------------------------------------------
    {
        calc::Calculator calculator;
        calculator.evaluate("20 + 1");
        expectValue("ans", 0);   // a *new* calculator starts with ans = 0
        double doubled = calculator.evaluate("ans * 2");
        if (doubled == 42 && calculator.history().size() == 2) {
            ++passed;
        } else {
            ++failed;
            std::cout << "FAIL  ans/history not remembered\n";
        }
    }

    // --- formatting for the display -----------------------------------------
    expectText(calc::Calculator::format(3.0), "3");
    expectText(calc::Calculator::format(0.1 + 0.2), "0.3");
    expectText(calc::Calculator::format(-0.0), "0");
    expectText(calc::Calculator::format(1.0 / 3.0), "0.333333333333");

    std::cout << "\n" << passed << " passed, " << failed << " failed\n";
    return failed == 0 ? 0 : 1;   // non-zero exit code = tests failed
}
