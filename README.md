# Calc From Scratch

**Learn C++ by building a calculator one small step at a time.**

This course is for students in their first programming course. You start with a program that adds two numbers. Eight lessons later you have a calculator with a real expression parser, automated tests and a graphical window. Every lesson is a small, working program that adds **one** new group of C++ ideas.

```
> (2 + 3) * 4 ^ 2
  = 80
> sqrt(ans) - 1
  = 7.94427191
```

---

## The roadmap

| # | Lesson | The calculator can... | C++ you learn |
|---|--------|-----------------------|---------------|
| 01 | [Hello, Calculator](lessons/01-hello-calculator/) | add, subtract, multiply and divide two numbers | `main`, `cout`/`cin`, variables, `int` vs `double` |
| 02 | [Making Choices](lessons/02-making-choices/) | read `12 * 4` and do only that one operation | `char`, `if`/`else`, `switch`, input validation |
| 03 | [Loops and Functions](lessons/03-loops-and-functions/) | keep a running total like a pocket calculator | `while`, functions, references, `std::string` |
| 04 | [Strings and Tokens](lessons/04-strings-and-tokens/) | read a whole line, though it gets `2+3*4` wrong on purpose | `getline`, `enum class`, `struct`, `std::vector` |
| 05 | [Recursion and Precedence](lessons/05-recursion-and-precedence/) | handle precedence, `( )`, `^` and negative numbers correctly | grammars, recursion, exceptions |
| 06 | [Classes and Multiple Files](lessons/06-classes-and-files/) | use `ans`, `pi`, `sqrt()`, `%` and keep a history | `class`, `.hpp`/`.cpp`, namespaces, `const`, `static` |
| 07 | [Testing](lessons/07-testing/) | prove it works with 31 automated checks | test helpers, float comparison, exit codes |
| 08 | [A Real Window with SFML](lessons/08-gui-with-sfml/) | open a clickable, keyboard-friendly window | third-party libraries, the game loop, events |

Each lesson folder has a `README.md` that explains the new ideas, plus a **Try it yourself** list of exercises. Do the exercises; that's where most of the learning happens.

---

## Getting started

### 1. Install a C++ compiler

| System | How |
|--------|-----|
| macOS | `xcode-select --install` |
| Ubuntu / Debian | `sudo apt install build-essential` |
| Windows | Install [MSYS2](https://www.msys2.org/), then run `pacman -S mingw-w64-ucrt-x86_64-gcc make` in the UCRT64 shell |

Check that it works:

```bash
c++ --version
```

### 2. Build and run a lesson

Every lesson can be built by hand. Learning to type compiler commands yourself is worth it:

```bash
cd lessons/01-hello-calculator
c++ -std=c++17 -Wall -Wextra main.cpp -o calc
./calc
```

Or use the `Makefile` from the repository root:

```bash
make            # build lessons 01-07 and run the tests
make lesson05   # build one lesson  ->  ./build/lesson05
make test       # run the test suite
make gui        # build the window app (needs SFML 2, see lesson 08)
```

### 3. Read the code

Each `main.cpp` starts with a comment that lists the **new ideas** in that file. Read the code before you run it, guess what it will do, and then check.

---

## How the project is organized

```
.
├── lessons/
│   ├── 01-hello-calculator/         single-file programs
│   ├── ...
│   ├── 05-recursion-and-precedence/
│   ├── 06-classes-and-files/        calculator.hpp/.cpp is "the engine"
│   ├── 07-testing/                  tests the engine
│   └── 08-gui-with-sfml/            a window that uses the engine
├── assets/fonts/                    font used by the GUI
└── Makefile
```

From lesson 06 on, the calculator's "brain" (`calc::Calculator`) is kept separate from its "faces": a text prompt, a test program and a window. All three share the same code.

---

## Tips for learning

- **Compile often.** Change one thing, compile, run. Big changes make big, confusing errors.
- **Read the *first* error message.** Later errors are often side effects of the first one.
- **Keep warnings on** (`-Wall -Wextra`). A warning is the compiler trying to help.
- **Break things on purpose.** Remove a `;` or a `break` and see what happens. Now you know what that error looks like.
- **Use a debugger.** Try `lldb ./build/lesson05` (macOS) or `gdb` (Linux). Set a breakpoint in `parseTerm` and step through `2 + 3 * 4`.

## Where to go next

- Add variables (`x = 5`) with `std::map`.
- Support more number formats: hexadecimal, binary, scientific notation (`1e3`).
- Make lesson 08 draw a history panel or switch to a light theme.
- Replace the hand-written tests with [Catch2](https://github.com/catchorg/Catch2) or [GoogleTest](https://github.com/google/googletest).
- Learn [CMake](https://cmake.org/), the most common build tool for real C++ projects.

---

## License

MIT. See [LICENSE](LICENSE) and [CREDITS.md](CREDITS.md).
