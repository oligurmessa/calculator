# Lesson 01: Hello, Calculator

**You will learn:** how a C++ program starts, how to print and read values, variables, `int` vs `double`, and the arithmetic operators.

## Build and run

```bash
c++ -std=c++17 -Wall -Wextra main.cpp -o calc
./calc
```

You can also run `make lesson01` from the repository root. That puts the program in `build/lesson01`.

## Reading the code

| Line | What it means |
|------|---------------|
| `#include <iostream>` | Brings in the part of the standard library that does input and output. |
| `int main() { ... }` | Every C++ program starts running at `main`. |
| `double first = 0.0;` | Makes a variable called `first` that holds a decimal number, starting at 0. |
| `std::cin >> first;` | Waits for the user to type a number and stores it in `first`. |
| `std::cout << ...` | Prints things. You can chain several `<<` in one line. |
| `'\n'` | A newline, like pressing Enter. |
| `static_cast<double>(x)` | Turns the `int` `x` into a `double` before we do the math. |

## Things to notice

1. `7 / 2` gives `3` when both numbers are `int`. C++ drops the fractional part; it does not round.
2. `%` (modulo) gives the remainder. It only works on whole numbers.
3. Type `5` and `0`. Division by zero with doubles prints `inf`. With ints the program would crash (it's undefined behaviour).
4. Type `hello` instead of a number. The program gets confused. Lesson 02 fixes that.

## Try it yourself

- [ ] Also print the average of the two numbers.
- [ ] Ask for a **third** number and print the sum of all three.
- [ ] Change `double` to `int` everywhere. Which answers change? Why?
- [ ] Add `#include <cmath>` and print `std::sqrt(first)` and `std::pow(first, second)`.

**Next:** [Lesson 02: Making Choices](../02-making-choices/)
