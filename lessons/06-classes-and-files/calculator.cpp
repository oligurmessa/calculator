// Lesson 06 - calculator.cpp
//
// Definitions for everything declared in calculator.hpp.
// `Calculator::` in front of a name means "this belongs to class Calculator".

#include "calculator.hpp"

#include <cctype>
#include <cmath>
#include <iomanip>
#include <sstream>

namespace calc {

namespace {   // an unnamed namespace = "only visible inside this .cpp file"

constexpr double kPi = 3.14159265358979323846;

bool isDigitOrDot(char c) {
    return std::isdigit(static_cast<unsigned char>(c)) || c == '.';
}

bool isLetter(char c) {
    return std::isalpha(static_cast<unsigned char>(c)) != 0;
}

}  // namespace

double Calculator::evaluate(const std::string& expression) {
    tokens_ = tokenize(expression);
    pos_ = 0;

    if (peek().kind == TokenKind::End) {
        throw Error("empty expression");
    }
    double result = parseExpression();
    if (peek().kind != TokenKind::End) {
        throw Error("unexpected '" + peek().text + "'");
    }
    if (!std::isfinite(result)) {
        throw Error("result is too large");
    }

    // Only remember successful calculations.
    ans_ = result;
    history_.push_back({expression, result});
    return result;
}

void Calculator::clear() {
    ans_ = 0.0;
    history_.clear();
}

std::string Calculator::format(double value, std::size_t maxChars) {
    if (value == 0.0) {
        return "0";   // also turns -0 into 0
    }
    // Try fewer and fewer significant digits until the text fits.
    for (int digits = 12; digits >= 1; --digits) {
        std::ostringstream out;
        out << std::setprecision(digits) << value;
        std::string text = out.str();
        if (text.size() <= maxChars) {
            return text;
        }
    }
    return "overflow";
}

std::vector<Calculator::Token> Calculator::tokenize(const std::string& text) const {
    std::vector<Token> tokens;
    std::size_t i = 0;

    while (i < text.size()) {
        char c = text[i];

        if (std::isspace(static_cast<unsigned char>(c))) {
            ++i;
        } else if (isDigitOrDot(c)) {
            std::size_t start = i;
            while (i < text.size() && isDigitOrDot(text[i])) {
                ++i;
            }
            std::string number = text.substr(start, i - start);
            std::size_t used = 0;
            double value = 0.0;
            try {
                value = std::stod(number, &used);
            } catch (const std::exception&) {
                used = 0;
            }
            if (used != number.size()) {
                throw Error("'" + number + "' is not a valid number");
            }
            tokens.push_back({TokenKind::Number, value, number});
        } else if (isLetter(c)) {
            std::size_t start = i;
            while (i < text.size() && isLetter(text[i])) {
                ++i;
            }
            tokens.push_back({TokenKind::Name, 0.0, text.substr(start, i - start)});
        } else if (std::string("+-*/%^()").find(c) != std::string::npos) {
            tokens.push_back({TokenKind::Symbol, 0.0, std::string(1, c)});
            ++i;
        } else {
            throw Error(std::string("unexpected character '") + c + "'");
        }
    }
    tokens.push_back({TokenKind::End, 0.0, "end of input"});
    return tokens;
}

bool Calculator::accept(const std::string& symbol) {
    if (peek().kind == TokenKind::Symbol && peek().text == symbol) {
        ++pos_;
        return true;
    }
    return false;
}

// expression := term { ('+' | '-') term }
double Calculator::parseExpression() {
    double result = parseTerm();
    while (true) {
        if (accept("+")) {
            result += parseTerm();
        } else if (accept("-")) {
            result -= parseTerm();
        } else {
            return result;
        }
    }
}

// term := unary { ('*' | '/' | '%') unary }
double Calculator::parseTerm() {
    double result = parseUnary();
    while (true) {
        if (accept("*")) {
            result *= parseUnary();
        } else if (accept("/") || accept("%")) {
            bool isRemainder = tokens_[pos_ - 1].text == "%";
            double right = parseUnary();
            if (right == 0.0) {
                throw Error("division by zero");
            }
            result = isRemainder ? std::fmod(result, right) : result / right;
        } else {
            return result;
        }
    }
}

// unary := ('-' | '+') unary | power
double Calculator::parseUnary() {
    if (accept("-")) {
        return -parseUnary();
    }
    if (accept("+")) {
        return parseUnary();
    }
    return parsePower();
}

// power := primary [ '^' unary ]
double Calculator::parsePower() {
    double base = parsePrimary();
    if (accept("^")) {
        return std::pow(base, parseUnary());
    }
    return base;
}

// primary := NUMBER | NAME | NAME '(' expression ')' | '(' expression ')'
double Calculator::parsePrimary() {
    const Token token = peek();   // a copy: pos_ is about to move

    if (token.kind == TokenKind::Number) {
        ++pos_;
        return token.value;
    }
    if (token.kind == TokenKind::Name) {
        ++pos_;
        if (accept("(")) {
            double argument = parseExpression();
            if (!accept(")")) {
                throw Error("missing ')' after " + token.text + "(...");
            }
            return callFunction(token.text, argument);
        }
        if (token.text == "ans") return ans_;
        if (token.text == "pi") return kPi;
        throw Error("unknown name '" + token.text + "'");
    }
    if (accept("(")) {
        double inside = parseExpression();
        if (!accept(")")) {
            throw Error("missing ')'");
        }
        return inside;
    }
    throw Error("expected a number, found '" + token.text + "'");
}

double Calculator::callFunction(const std::string& name, double x) const {
    if (name == "sqrt") {
        if (x < 0) throw Error("sqrt of a negative number");
        return std::sqrt(x);
    }
    if (name == "abs") return std::fabs(x);
    throw Error("unknown function '" + name + "'");
}

}  // namespace calc
