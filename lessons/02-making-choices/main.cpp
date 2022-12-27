// Lesson 02 - Making Choices
//
// Goal: let the user type something like   12 * 4   and answer with
// only that one operation.
//
// New ideas in this file:
//   * char (a single character like '+')
//   * if / else if / else
//   * switch
//   * checking that input actually worked
//   * returning an error code from main

#include <iostream>

int main() {
    double left = 0.0;
    double right = 0.0;
    char op = ' ';      // a char holds exactly one character

    std::cout << "Type a calculation, like 12 * 4 : ";
    std::cin >> left >> op >> right;

    // If the user typed something that is not a number, std::cin goes into
    // a "failed" state. We check for that before trusting the variables.
    if (!std::cin) {
        std::cout << "That didn't look like  number operator number.\n";
        return 1;       // non-zero means "something went wrong"
    }

    double result = 0.0;

    // A switch picks one branch based on the value of `op`.
    switch (op) {
        case '+':
            result = left + right;
            break;      // without break, C++ "falls through" to the next case!
        case '-':
            result = left - right;
            break;
        case '*':
        case 'x':       // two cases can share one branch
            result = left * right;
            break;
        case '/':
            if (right == 0.0) {
                std::cout << "Error: you can't divide by zero.\n";
                return 1;
            }
            result = left / right;
            break;
        default:
            std::cout << "Error: I don't know the operator '" << op << "'.\n";
            return 1;
    }

    std::cout << left << ' ' << op << ' ' << right << " = " << result << '\n';

    // The same decision written with if / else, just to compare:
    if (result > 0) {
        std::cout << "(the answer is positive)\n";
    } else if (result < 0) {
        std::cout << "(the answer is negative)\n";
    } else {
        std::cout << "(the answer is exactly zero)\n";
    }

    return 0;
}
