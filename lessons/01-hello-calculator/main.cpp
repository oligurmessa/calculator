// Lesson 01 - Hello, Calculator
//
// Goal: read two numbers from the keyboard and print their sum,
// difference, product and quotient.
//
// New ideas in this file:
//   * #include and the standard library (std::cout, std::cin)
//   * variables and types (int, double)
//   * arithmetic operators: +  -  *  /  %
//   * why 7 / 2 is 3 for ints but 3.5 for doubles

#include <iostream>   // gives us std::cout (print) and std::cin (read)

int main() {
    // A variable is a named box that holds a value.
    // "double" means "a number that can have a decimal point".
    double first = 0.0;
    double second = 0.0;

    std::cout << "Enter the first number: ";
    std::cin >> first;              // read a number from the keyboard

    std::cout << "Enter the second number: ";
    std::cin >> second;

    std::cout << '\n';
    std::cout << first << " + " << second << " = " << first + second << '\n';
    std::cout << first << " - " << second << " = " << first - second << '\n';
    std::cout << first << " * " << second << " = " << first * second << '\n';
    std::cout << first << " / " << second << " = " << first / second << '\n';
    // What happens if "second" is 0? Try it! We fix this in lesson 02.

    // --- A surprise with whole numbers ---------------------------------
    // "int" can only hold whole numbers, so int division throws away
    // everything after the decimal point.
    int apples = 7;
    int friends = 2;
    std::cout << "\nInteger surprise:\n";
    std::cout << "  7 / 2 as int    = " << apples / friends << '\n';
    std::cout << "  7 % 2 (leftover) = " << apples % friends << '\n';
    std::cout << "  7 / 2 as double = " << static_cast<double>(apples) / friends << '\n';

    return 0;   // 0 tells the operating system "everything went fine"
}
