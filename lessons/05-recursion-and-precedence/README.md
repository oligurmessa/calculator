# Lesson 05: Recursion and Precedence

**You will learn:** how to describe an expression with a **grammar**, how to turn that grammar into **recursive functions**, and how to handle errors with **exceptions**.

This is the hardest lesson so far, so take it slowly. Once you get it, you'll understand how calculators, spreadsheets and compilers read math.

## Build and run

```bash
c++ -std=c++17 -Wall -Wextra main.cpp -o calc
./calc
```

Or run `make lesson05` from the repository root.

```
> 2 + 3 * 4
  = 14
> (2 + 3) * 4
  = 20
> 2 ^ 3 ^ 2
  = 512
> 1 / (3 - 3)
  ! division by zero
```

## The big idea: precedence lives in the call stack

```
expression := term   { ('+' | '-') term }
term       := unary  { ('*' | '/') unary }
unary      := '-' unary | power
power      := primary [ '^' unary ]
primary    := NUMBER | '(' expression ')'
```

Each rule is **one function**. A lower-precedence rule (`+`) calls the higher-precedence rule (`*`) to get its pieces. So `*` is always worked out *first*, deeper in the call stack.

Here's how `2 + 3 * 4` gets evaluated:

```
parseExpression
├── parseTerm → parseUnary → parsePower → parsePrimary → 2
├── sees '+'
└── parseTerm
    ├── parseUnary → ... → 3
    ├── sees '*'
    └── parseUnary → ... → 4        term returns 3*4 = 12
                                    expression returns 2+12 = 14
```

Parentheses work because `parsePrimary` calls `parseExpression` again. That's **recursion**. This technique is called a *recursive descent parser*.

## Exceptions

```cpp
throw std::runtime_error("division by zero");
```
`throw` stops the current function right away, and every function that called it, until something **catches** the error:

```cpp
try {
    std::cout << evaluate(line);
} catch (const std::exception& error) {
    std::cout << error.what();
}
```

In lesson 03 every function had to return `bool` and pass the result through a reference. Exceptions let the normal code stay clean.

## Try it yourself

- [ ] Add `%` (remainder, `std::fmod`) with the same precedence as `*` and `/`.
- [ ] Add a unary `+`, so `+5` is allowed.
- [ ] Add functions: `sqrt(9)`. Hint: tokenize letters into a name, then handle `name '(' expression ')'` in `parsePrimary`.
- [ ] Put `std::cout << "parseTerm\n";` at the start of each parse function and watch the recursion happen.
- [ ] Why does `2 ^ 3 ^ 2` give 512 and not 64? Change one line to make it 64.

**Next:** [Lesson 06: Classes and Multiple Files](../06-classes-and-files/)
