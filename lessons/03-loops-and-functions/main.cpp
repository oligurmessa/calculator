// Lesson 03 - Loops and Functions
//
// Goal: a "pocket calculator" that keeps a running total.
//
//   total: 0
//   > + 5
//   total: 5
//   > * 3
//   total: 15
//   > sqrt
//   total: 3.87298
//   > q
//
// New ideas in this file:
//   * while loops
//   * writing your own functions
//   * pass-by-value vs pass-by-reference (&)
//   * bool return values to signal success or failure
//   * std::string

#include <cmath>
#include <iostream>
#include <string>

// A function takes inputs (parameters) and gives back one output (return value).
// `result` is a *reference* (double&): the function writes straight into the
// caller's variable instead of into a copy.
bool applyOperator(double left, char op, double right, double& result) {
    switch (op) {
        case '+': result = left + right; return true;
        case '-': result = left - right; return true;
        case '*': result = left * right; return true;
        case '/':
            if (right == 0.0) {
                std::cout << "  ! can't divide by zero\n";
                return false;
            }
            result = left / right;
            return true;
        case '^': result = std::pow(left, right); return true;
    }
    std::cout << "  ! unknown operator '" << op << "'\n";
    return false;
}

// Functions without a useful return value use `void`.
void printHelp() {
    std::cout << "Commands:\n"
              << "  + N   - N   * N   / N   ^ N   change the total\n"
              << "  sqrt                        square root of the total\n"
              << "  neg                         flip the sign\n"
              << "  c                           clear (total = 0)\n"
              << "  help                        show this text\n"
              << "  q                           quit\n";
}

bool isOperator(const std::string& word) {
    return word == "+" || word == "-" || word == "*" || word == "/" || word == "^";
}

int main() {
    double total = 0.0;
    std::string command;

    printHelp();

    // Keep asking for commands until we are told to stop.
    while (true) {
        std::cout << "total: " << total << "\n> ";

        if (!(std::cin >> command)) {
            break;                  // input closed (Ctrl+D / Ctrl+Z)
        }

        if (command == "q") {
            break;                  // leave the loop
        } else if (command == "help") {
            printHelp();
        } else if (command == "c") {
            total = 0.0;
        } else if (command == "neg") {
            total = -total;
        } else if (command == "sqrt") {
            if (total < 0) {
                std::cout << "  ! no square root of a negative number\n";
            } else {
                total = std::sqrt(total);
            }
        } else if (isOperator(command)) {
            double number = 0.0;
            if (!(std::cin >> number)) {
                std::cout << "  ! expected a number after " << command << '\n';
                std::cin.clear();                 // reset the error flag
                std::cin.ignore(10000, '\n');     // throw away the rest of the line
                continue;                         // jump to the next loop turn
            }
            double newTotal = 0.0;
            if (applyOperator(total, command[0], number, newTotal)) {
                total = newTotal;
            }
        } else {
            std::cout << "  ! unknown command, type help\n";
        }
    }

    std::cout << "Final total: " << total << "\nBye!\n";
    return 0;
}
