# Lesson 06: Classes and Multiple Files

**You will learn:** how to split a program into `.hpp` and `.cpp` files, how to write a `class` with `public` and `private` parts, namespaces, `const` member functions, and a bit of inheritance.

The parser from lesson 05 now lives inside a reusable **`calc::Calculator` class**. It also gets a few new features: `ans` (the last answer), `pi`, `sqrt(...)`, `abs(...)`, `%` and a history.

## Build and run

With more than one `.cpp` file, you have to give the compiler **all** of them:

```bash
c++ -std=c++17 -Wall -Wextra main.cpp calculator.cpp -o calc
./calc
```

Or run `make lesson06` from the repository root.

```
> 2 + 3 * 4
  = 14
> ans * 2
  = 28
> sqrt(ans - 3)
  = 5
> :history
  2 + 3 * 4 = 14
  ans * 2 = 28
  sqrt(ans - 3) = 5
```

## Key ideas

### Header vs source
| File | Contains | Analogy |
|------|----------|---------|
| `calculator.hpp` | *Declarations*: what exists | a restaurant menu |
| `calculator.cpp` | *Definitions*: how it works | the kitchen |
| `main.cpp` | Code that *uses* the class | a customer |

`main.cpp` only needs the menu. It never has to see the kitchen.

### How the build works
1. The **compiler** turns each `.cpp` into an object file (`.o`) on its own.
2. The **linker** joins the object files into one program.

You can do the two steps yourself to see this:
```bash
c++ -std=c++17 -c calculator.cpp      # -> calculator.o
c++ -std=c++17 -c main.cpp            # -> main.o
c++ main.o calculator.o -o calc       # link
```

### public vs private
Code outside the class can call anything under `public:` (`evaluate`, `history`, ...). Everything under `private:` (the tokens, `pos_`, the parse functions) is hidden. That way nobody can break the calculator by setting `pos_` to a wrong value from outside.

### `const` member functions
`double lastAnswer() const` promises that calling it won't change the object. The compiler checks that promise.

### `static`
`Calculator::format` doesn't need a calculator object, because it only formats a number. You call it on the class itself: `calc::Calculator::format(3.5)`.

## Try it yourself

- [ ] Add more functions to `callFunction`: `sin`, `cos`, `log`, `round`.
- [ ] Add a constant `e` next to `pi`.
- [ ] Add a `:undo` command that removes the last history entry.
- [ ] Challenge: let users make variables, like `x = 5` and then `x * 2`. Hint: `std::map<std::string, double>`.

**Next:** [Lesson 07: Testing](../07-testing/)
