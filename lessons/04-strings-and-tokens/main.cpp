// Lesson 04 - Strings and Tokens
//
// Goal: read a whole line like   12.5 + 3*4   and chop it into pieces
// ("tokens") that the computer can work with:
//
//   [Number 12.5] [Op +] [Number 3] [Op *] [Number 4]
//
// Then evaluate it strictly left to right, and discover why that is wrong.
//
// New ideas in this file:
//   * std::getline to read a whole line
//   * looping over the characters of a std::string
//   * enum class - a type with a fixed list of named values
//   * struct     - bundling several values into one thing
//   * std::vector - a list that can grow

#include <cctype>     // std::isdigit, std::isspace
#include <iostream>
#include <string>
#include <vector>

enum class TokenKind {
    Number,
    Operator,
};

struct Token {
    TokenKind kind;
    double value = 0.0;   // only used when kind == Number
    char symbol = ' ';    // only used when kind == Operator
};

// Turn text into tokens. Returns false if we find a character we don't understand.
bool tokenize(const std::string& text, std::vector<Token>& tokens) {
    std::size_t i = 0;                        // current position in the text

    while (i < text.size()) {
        char c = text[i];

        if (std::isspace(static_cast<unsigned char>(c))) {
            ++i;                              // skip spaces
        } else if (std::isdigit(static_cast<unsigned char>(c)) || c == '.') {
            // Collect all digits and dots that belong to this number.
            std::size_t start = i;
            while (i < text.size() &&
                   (std::isdigit(static_cast<unsigned char>(text[i])) || text[i] == '.')) {
                ++i;
            }
            std::string numberText = text.substr(start, i - start);
            try {
                tokens.push_back({TokenKind::Number, std::stod(numberText), ' '});
            } catch (...) {                   // e.g. the text was just "."
                std::cout << "  ! '" << numberText << "' is not a number\n";
                return false;
            }
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            tokens.push_back({TokenKind::Operator, 0.0, c});
            ++i;
        } else {
            std::cout << "  ! unexpected character '" << c << "' at position " << i << '\n';
            return false;
        }
    }
    return true;
}

void printTokens(const std::vector<Token>& tokens) {
    std::cout << "  tokens:";
    // "range-based for": visit every element of the vector in order
    for (const Token& token : tokens) {
        if (token.kind == TokenKind::Number) {
            std::cout << " [Number " << token.value << ']';
        } else {
            std::cout << " [Op " << token.symbol << ']';
        }
    }
    std::cout << '\n';
}

// Evaluate strictly from left to right: number op number op number ...
bool evaluateLeftToRight(const std::vector<Token>& tokens, double& result) {
    if (tokens.empty() || tokens[0].kind != TokenKind::Number) {
        std::cout << "  ! expression must start with a number\n";
        return false;
    }
    result = tokens[0].value;

    // Walk over the rest in pairs: (operator, number)
    for (std::size_t i = 1; i < tokens.size(); i += 2) {
        if (tokens[i].kind != TokenKind::Operator ||
            i + 1 >= tokens.size() || tokens[i + 1].kind != TokenKind::Number) {
            std::cout << "  ! expected: operator then number\n";
            return false;
        }
        double right = tokens[i + 1].value;
        switch (tokens[i].symbol) {
            case '+': result += right; break;
            case '-': result -= right; break;
            case '*': result *= right; break;
            case '/':
                if (right == 0.0) {
                    std::cout << "  ! can't divide by zero\n";
                    return false;
                }
                result /= right;
                break;
        }
    }
    return true;
}

int main() {
    std::cout << "Type an expression (empty line to quit), e.g. 2 + 3 * 4\n";

    std::string line;
    while (std::cout << "> " && std::getline(std::cin, line) && !line.empty()) {
        std::vector<Token> tokens;
        if (!tokenize(line, tokens)) {
            continue;
        }
        printTokens(tokens);

        double result = 0.0;
        if (evaluateLeftToRight(tokens, result)) {
            std::cout << "  = " << result << '\n';
        }
    }
    return 0;
}
