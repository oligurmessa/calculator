// Lesson 05 - Recursion and Precedence
//
// Goal: finally get   2 + 3 * 4 = 14   right, and support parentheses,
// powers and negative numbers:
//
//   > (2 + 3) * 4        = 20
//   > 2 ^ 3 ^ 2          = 512      (powers group right-to-left)
//   > -2 ^ 2             = -4       (like in math class)
//
// New ideas in this file:
//   * a grammar: rules that describe what a valid expression looks like
//   * recursion: functions that call themselves (directly or indirectly)
//   * exceptions: throw / try / catch for error handling
//
// The grammar, from lowest to highest precedence:
//
//   expression := term   { ('+' | '-') term }
//   term       := unary  { ('*' | '/') unary }
//   unary      := '-' unary | power
//   power      := primary [ '^' unary ]
//   primary    := NUMBER | '(' expression ')'
//
// { ... } means "repeat zero or more times", [ ... ] means "optional".
// Each rule becomes one function below. Since `primary` can contain a whole
// `expression` again, the functions end up calling each other recursively.

#include <cctype>
#include <cmath>
#include <iostream>
#include <stdexcept>   // std::runtime_error
#include <string>
#include <vector>

enum class TokenKind { Number, Symbol, End };

struct Token {
    TokenKind kind;
    double value = 0.0;
    char symbol = ' ';
};

std::vector<Token> tokenize(const std::string& text) {
    std::vector<Token> tokens;
    std::size_t i = 0;
    while (i < text.size()) {
        char c = text[i];
        if (std::isspace(static_cast<unsigned char>(c))) {
            ++i;
        } else if (std::isdigit(static_cast<unsigned char>(c)) || c == '.') {
            std::size_t start = i;
            while (i < text.size() &&
                   (std::isdigit(static_cast<unsigned char>(text[i])) || text[i] == '.')) {
                ++i;
            }
            std::string numberText = text.substr(start, i - start);
            std::size_t used = 0;
            double value = 0.0;
            try {
                value = std::stod(numberText, &used);
            } catch (const std::exception&) {
                used = 0;
            }
            if (used != numberText.size()) {
                throw std::runtime_error("'" + numberText + "' is not a valid number");
            }
            tokens.push_back({TokenKind::Number, value, ' '});
        } else if (std::string("+-*/^()").find(c) != std::string::npos) {
            tokens.push_back({TokenKind::Symbol, 0.0, c});
            ++i;
        } else {
            throw std::runtime_error(std::string("unexpected character '") + c + "'");
        }
    }
    tokens.push_back({TokenKind::End, 0.0, ' '});   // marks the end of input
    return tokens;
}

// Keeps track of where we are in the token list while parsing.
struct Parser {
    std::vector<Token> tokens;
    std::size_t pos = 0;
};

const Token& peek(const Parser& p) { return p.tokens[p.pos]; }

bool isSymbol(const Parser& p, char c) {
    return peek(p).kind == TokenKind::Symbol && peek(p).symbol == c;
}

// If the next token is `c`, consume it and return true.
bool accept(Parser& p, char c) {
    if (isSymbol(p, c)) {
        ++p.pos;
        return true;
    }
    return false;
}

// Functions must be declared before use. parseExpression is needed by
// parsePrimary (for parentheses), so we announce it up here.
double parseExpression(Parser& p);
double parseUnary(Parser& p);

double parsePrimary(Parser& p) {
    if (peek(p).kind == TokenKind::Number) {
        return p.tokens[p.pos++].value;
    }
    if (accept(p, '(')) {
        double inside = parseExpression(p);        // <- recursion!
        if (!accept(p, ')')) {
            throw std::runtime_error("missing ')'");
        }
        return inside;
    }
    throw std::runtime_error("expected a number or '('");
}

double parsePower(Parser& p) {
    double base = parsePrimary(p);
    if (accept(p, '^')) {
        double exponent = parseUnary(p);           // right side can be another power
        return std::pow(base, exponent);
    }
    return base;
}

double parseUnary(Parser& p) {
    if (accept(p, '-')) {
        return -parseUnary(p);                     // handles --5 too
    }
    return parsePower(p);
}

double parseTerm(Parser& p) {
    double result = parseUnary(p);
    while (true) {
        if (accept(p, '*')) {
            result *= parseUnary(p);
        } else if (accept(p, '/')) {
            double divisor = parseUnary(p);
            if (divisor == 0.0) {
                throw std::runtime_error("division by zero");
            }
            result /= divisor;
        } else {
            return result;
        }
    }
}

double parseExpression(Parser& p) {
    double result = parseTerm(p);
    while (true) {
        if (accept(p, '+')) {
            result += parseTerm(p);
        } else if (accept(p, '-')) {
            result -= parseTerm(p);
        } else {
            return result;
        }
    }
}

double evaluate(const std::string& text) {
    Parser p;
    p.tokens = tokenize(text);
    double result = parseExpression(p);
    if (peek(p).kind != TokenKind::End) {
        throw std::runtime_error("unexpected leftover input");
    }
    return result;
}

int main() {
    std::cout << "Type an expression (empty line to quit), e.g. (2 + 3) * 4\n";

    std::string line;
    while (std::cout << "> " && std::getline(std::cin, line) && !line.empty()) {
        // Any `throw` inside evaluate() jumps straight to the matching catch.
        try {
            double result = evaluate(line);
            std::cout << "  = " << result << '\n';
        } catch (const std::exception& error) {
            std::cout << "  ! " << error.what() << '\n';
        }
    }
    return 0;
}
