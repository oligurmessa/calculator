// Lesson 06 - calculator.hpp
//
// A header file (.hpp) *declares* what a class looks like: its name, its
// public functions and its private data. The matching .cpp file *defines*
// how those functions actually work.
//
// Any other file that wants to use Calculator just writes
//     #include "calculator.hpp"
// Lessons 07 (tests) and 08 (GUI) both reuse this exact class.

#pragma once   // "only include this file once", even if #included many times

#include <stdexcept>
#include <string>
#include <vector>

namespace calc {   // a namespace keeps our names from clashing with others

// Our own error type. It "is a" std::runtime_error (inheritance), so any
// code that catches std::exception will also catch a calc::Error.
class Error : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;   // reuse the parent's constructors
};

struct HistoryEntry {
    std::string expression;
    double result;
};

class Calculator {
public:
    // Evaluate text like "2 * (ans + 1)". Throws calc::Error on bad input.
    double evaluate(const std::string& expression);

    double lastAnswer() const { return ans_; }
    const std::vector<HistoryEntry>& history() const { return history_; }
    void clear();

    // Formats a number for display: no trailing zeros, at most maxChars long.
    static std::string format(double value, std::size_t maxChars = 15);

private:
    // ----- tokens ---------------------------------------------------------
    enum class TokenKind { Number, Name, Symbol, End };
    struct Token {
        TokenKind kind;
        double value = 0.0;
        std::string text;   // the name ("sqrt") or symbol ("+")
    };
    std::vector<Token> tokenize(const std::string& text) const;

    // ----- parsing (same grammar as lesson 05, plus names and %) -----------
    double parseExpression();
    double parseTerm();
    double parseUnary();
    double parsePower();
    double parsePrimary();
    double callFunction(const std::string& name, double argument) const;

    const Token& peek() const { return tokens_[pos_]; }
    bool accept(const std::string& symbol);

    // ----- state ----------------------------------------------------------
    // The trailing underscore is a common way to mark member variables.
    std::vector<Token> tokens_;
    std::size_t pos_ = 0;
    double ans_ = 0.0;
    std::vector<HistoryEntry> history_;
};

}  // namespace calc
