# Lesson 02: Making Choices

**You will learn:** the `char` type, `if`/`else`, `switch`, and how to check that user input was valid.

## Build and run

```bash
c++ -std=c++17 -Wall -Wextra main.cpp -o calc
./calc
```

Or run `make lesson02` from the repository root.

Try these inputs:

```
12 * 4
10 / 0
3 ^ 2
banana
```

## Key ideas

### `switch` and `break`
`switch (op)` jumps straight to the matching `case`. The `break` is important. If you leave it out, the program keeps running into the next case. This is called *fall-through*. Sometimes it's useful, like `case '*': case 'x':`, but usually it's a bug.

### Checking `std::cin`
`std::cin >> left` can fail, for example when the user types `banana`. Once it fails, `if (!std::cin)` is true. Always check input before you use it.

### Exit codes
`return 1;` from `main` tells the shell the program failed. Run `echo $?` right after the program finishes to see the code.

## Try it yourself

- [ ] Add `^` for "power" (hint: `#include <cmath>` and `std::pow`).
- [ ] Add `%` for remainder with doubles (hint: `std::fmod`).
- [ ] Rewrite the `switch` with only `if` / `else if`. Which version is easier to read?
- [ ] Take out one `break` and predict what will happen before you run it.

**Next:** [Lesson 03: Loops and Functions](../03-loops-and-functions/)
