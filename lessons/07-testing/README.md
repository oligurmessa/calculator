# Lesson 07: Testing

**You will learn:** why and how to write automated tests, how to compare `double` values safely, and how to check that errors really happen.

## Build and run

```bash
c++ -std=c++17 -Wall -Wextra tests.cpp ../06-classes-and-files/calculator.cpp -o tests
./tests
```

Or run `make test` from the repository root.

```
31 passed, 0 failed
```

## Why test?

Up to now you tested by typing expressions and checking the answers by eye. That works for one change. By change number twenty you'll have forgotten to re-check `2 ^ 3 ^ 2`. Automated tests re-check **everything** in milliseconds, every time.

A good habit: **when you find a bug, write a test that fails because of it first, then fix the bug.** That bug can never quietly come back.

## Key ideas

### Never use `==` on computed decimals
```cpp
0.1 + 0.2 == 0.3   // false!
```
Computers store decimals in binary, and most decimal fractions can't be stored exactly. Check that the numbers are *close enough* instead:
```cpp
std::fabs(actual - expected) < 1e-9
```

### Test the failures too
Half of the tests above check that bad input is **rejected**. A calculator that says `1 / 0 = 0` is worse than one that says "division by zero".

### Exit codes and automation
`main` returns `1` if any test failed. Tools like `make` and GitHub Actions use that to tell whether a build is "green" or "red".

## Real-world testing

Professional projects use a testing framework such as [GoogleTest](https://github.com/google/googletest) or [Catch2](https://github.com/catchorg/Catch2). They do the same thing as `expectValue` and `expectError`, with nicer output.

## Try it yourself

- [ ] Go back to lesson 06, deliberately break something (swap `+` and `-`), and watch the tests catch it.
- [ ] Write tests for every function you added in the lesson 06 exercises.
- [ ] Add a test for a very long expression, like 100 `+ 1`s. Build the string with a loop.
- [ ] Some tests share a lot of code. Can you make a helper that removes the repetition?

**Next:** [Lesson 08: A Real Window with SFML](../08-gui-with-sfml/)
