# Lesson 03: Loops and Functions

**You will learn:** `while` loops, `break` and `continue`, how to write your own functions, and the difference between passing *by value* and *by reference*.

The calculator now works like a real pocket calculator. It keeps a running **total** that each command changes.

## Build and run

```bash
c++ -std=c++17 -Wall -Wextra main.cpp -o calc
./calc
```

Or run `make lesson03` from the repository root.

## Key ideas

### The loop
```cpp
while (true) {
    ...
    if (command == "q") break;
}
```
`while (true)` would run forever. `break` is the only way out. `continue` skips the rest of this turn and goes back to the top of the loop.

### Functions
```cpp
bool applyOperator(double left, char op, double right, double& result)
```
- `bool` is the return type. It tells the caller whether the operation worked.
- `left`, `op` and `right` are passed **by value**. The function gets its own copies.
- `result` is passed **by reference** (`&`). The function writes into the caller's variable.

`const std::string& word` in `isOperator` is a *const reference*. It avoids copying the string, and `const` promises the function won't change it.

### Recovering from bad input
If `std::cin >> number` fails, you have to do two things before you can read again:
1. `std::cin.clear()` resets the error state.
2. `std::cin.ignore(...)` throws away the bad characters.

## Try it yourself

- [ ] Add a `%` command that divides the total by 100.
- [ ] Add an `m+` / `mr` memory: `m+` saves the total and `mr` brings it back.
- [ ] Count how many commands the user typed and print the count when they quit.
- [ ] Move the `sqrt` logic into its own function `bool squareRoot(double& value)`.

## What's still annoying?

You can't type `2 + 3 * 4` in one go. For that, the program has to understand a whole line of text. That's the next lesson.

**Next:** [Lesson 04: Strings and Tokens](../04-strings-and-tokens/)
