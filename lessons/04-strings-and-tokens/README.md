# Lesson 04: Strings and Tokens

**You will learn:** how to read a whole line, walk through a string one character at a time, and use `enum class`, `struct` and `std::vector`.

## Build and run

```bash
c++ -std=c++17 -Wall -Wextra main.cpp -o calc
./calc
```

Or run `make lesson04` from the repository root.

```
> 12.5 + 3*4
  tokens: [Number 12.5] [Op +] [Number 3] [Op *] [Number 4]
  = 62
```

## Key ideas

### Tokens
A **token** is the smallest meaningful piece of the input. Humans see `12.5+3` and read "twelve point five plus three" without thinking. A program has to go through it character by character: `1`, `2`, `.`, `5`, `+`, `3`. Grouping those characters into tokens is called **tokenizing** (or *lexing*). Real compilers do this too. It's the first thing the C++ compiler does to your code.

### `enum class`
```cpp
enum class TokenKind { Number, Operator };
```
This is a new type that can only be one of the listed values. It's safer than using magic numbers like `0` and `1`.

### `struct`
```cpp
struct Token { TokenKind kind; double value; char symbol; };
```
A struct groups related values together. You can write `token.kind`, `token.value` and so on.

### `std::vector`
A list that grows when you call `push_back`. You can loop over it with a range-based `for`:
```cpp
for (const Token& token : tokens) { ... }
```

## The bug on purpose

Type `2 + 3 * 4`. The program says **20**. Your math teacher says **14**, because multiplication comes before addition.

Evaluating left to right ignores **operator precedence**. You can't fix this with a few more `if` statements, because you need a smarter way to read the expression. That's lesson 05.

## Try it yourself

- [ ] Add `(` and `)` as tokens. Only print them for now; evaluating them comes later.
- [ ] Make `1.2.3` print a clear error message. What does `std::stod` do with it right now?
- [ ] Count how many numbers and how many operators the line contains.
- [ ] Add `^` as an operator token.

**Next:** [Lesson 05: Recursion and Precedence](../05-recursion-and-precedence/)
