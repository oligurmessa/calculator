# Lesson 08: A Real Window with SFML

**You will learn:** how to install and link a third-party library, the *game loop*, how to draw shapes and text, and how to handle mouse and keyboard events.

The math engine from lesson 06 is reused **without any changes**. The GUI is just another way of calling `evaluate()`. Keeping the "brain" separate from the "face" is one of the most useful habits in software design.

## Install SFML 2

This lesson uses **SFML 2.x**. SFML 3 changed its API and won't compile this code.

**macOS (Homebrew)**
```bash
brew install sfml@2
```

**Ubuntu / Debian**
```bash
sudo apt install libsfml-dev
```

**Windows (MSYS2 UCRT64 shell)**
```bash
pacman -S mingw-w64-ucrt-x86_64-sfml
```

## Build and run

From the repository root:

```bash
make gui
./build/gui
```

Or compile it by hand. On macOS with Homebrew, use:

```bash
SFML=$(brew --prefix sfml@2)
c++ -std=c++17 main.cpp ../06-classes-and-files/calculator.cpp \
    -I"$SFML/include" -L"$SFML/lib" \
    -lsfml-graphics -lsfml-window -lsfml-system -o gui
./gui
```

`-I` tells the compiler where to find the SFML **headers**. `-L` and `-l` tell the linker where to find the SFML **libraries** and which ones to use.

## Controls

| Input | Action |
|-------|--------|
| Mouse click | press a button |
| `0-9 . + - * / ^ % ( )` | type into the display |
| `Enter` or `=` | evaluate |
| `Backspace` | delete one character |
| `Esc` or `c` | clear |

## Key ideas

### The game loop
Almost every interactive program works the same way:

```cpp
while (window.isOpen()) {
    // 1. handle events  (clicks, keys, close button)
    // 2. update state   (hover colours, calculator input)
    // 3. draw           (clear, draw everything, display)
}
```
This runs about 60 times per second (`setFramerateLimit(60)`). Nothing stays on screen by itself: every frame is drawn from scratch.

### Hit-testing
```cpp
if (button.shape.getGlobalBounds().contains(mousePoint)) { ... }
```
A button is just a rectangle. You click it when the mouse point is inside that rectangle.

### One `press()` for everything
Mouse clicks and key presses both call `screen.press("7")`. Because the logic is written once, the two can never disagree.

## Try it yourself

- [ ] Change the colour theme at the top of the file. Try making a light mode.
- [ ] Add a history panel that shows the last 3 results under the display (hint: `calculator.history()`).
- [ ] Make the buttons rounded. Search the SFML docs for `sf::ConvexShape`, or draw circles at the corners.
- [ ] Add a button for a function you added in lesson 06, such as `sin`.
- [ ] Challenge: make the window resizable and recompute the button layout when it changes size.

**Congratulations!** You built a calculator from `std::cin >> a` all the way to a graphical app with a real parser and tests. Head back to the [main README](../../README.md) for ideas on where to go next.
