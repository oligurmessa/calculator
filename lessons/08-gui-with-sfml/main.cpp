// Lesson 08 - A Real Window with SFML
//
// Goal: put a clickable, keyboard-friendly window in front of the
// calc::Calculator class from lesson 06. Notice that we don't change a single
// line of the math: the GUI is just another way of calling evaluate().
//
// New ideas in this file:
//   * using a third-party library (SFML 2.x)
//   * the game loop: handle events -> update -> draw, many times per second
//   * drawing shapes and text
//   * mouse hit-testing (is the cursor inside this rectangle?)
//
// Every button is drawn with shapes and text, so there are no image files to
// manage. The only asset is the font.

#include <SFML/Graphics.hpp>

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

#include "../06-classes-and-files/calculator.hpp"

// ----- layout ----------------------------------------------------------------
const float kWindowWidth = 360.f;
const float kWindowHeight = 560.f;
const float kPadding = 12.f;
const float kDisplayHeight = 120.f;
const int kColumns = 4;
const int kRows = 6;

// ----- colours (R, G, B) ----------------------------------------------------
const sf::Color kBackground(24, 26, 33);
const sf::Color kDisplayColor(14, 15, 20);
const sf::Color kDigitColor(52, 56, 70);
const sf::Color kOperatorColor(62, 92, 160);
const sf::Color kActionColor(88, 62, 110);
const sf::Color kEqualsColor(40, 140, 100);
const sf::Color kTextColor(236, 238, 245);
const sf::Color kDimTextColor(140, 146, 165);
const sf::Color kErrorColor(240, 110, 110);

struct Button {
    std::string label;     // what is shown on the button
    sf::RectangleShape shape;
    sf::Color baseColor;
};

// Where the button labels go, row by row. "<" is backspace.
const std::vector<std::vector<std::string>> kLayout = {
    {"C", "<", "(", ")"},
    {"sqrt", "^", "%", "/"},
    {"7", "8", "9", "*"},
    {"4", "5", "6", "-"},
    {"1", "2", "3", "+"},
    {"ans", "0", ".", "="},
};

sf::Color colorFor(const std::string& label) {
    if (label == "=") return kEqualsColor;
    if (label == "C" || label == "<" || label == "ans" || label == "sqrt") return kActionColor;
    if (label.size() == 1 && std::string("+-*/^%()").find(label[0]) != std::string::npos) {
        return kOperatorColor;
    }
    return kDigitColor;
}

std::vector<Button> makeButtons() {
    std::vector<Button> buttons;
    const float gap = 8.f;
    const float top = kPadding + kDisplayHeight + kPadding;
    const float width = (kWindowWidth - 2 * kPadding - (kColumns - 1) * gap) / kColumns;
    const float height = (kWindowHeight - top - kPadding - (kRows - 1) * gap) / kRows;

    for (int row = 0; row < kRows; ++row) {
        for (int col = 0; col < kColumns; ++col) {
            Button button;
            button.label = kLayout[row][col];
            button.baseColor = colorFor(button.label);
            button.shape.setSize({width, height});
            button.shape.setPosition(kPadding + col * (width + gap), top + row * (height + gap));
            button.shape.setFillColor(button.baseColor);
            buttons.push_back(button);
        }
    }
    return buttons;
}

// Make a colour a bit brighter (for hover) by moving it towards white.
sf::Color lighten(sf::Color c, int amount) {
    auto up = [amount](sf::Uint8 v) { return static_cast<sf::Uint8>(std::min(255, v + amount)); };
    return sf::Color(up(c.r), up(c.g), up(c.b));
}

// Try a few places so the program works whether you start it from the
// repository root, from this folder, or from build/.
bool loadFont(sf::Font& font) {
    const std::vector<std::string> candidates = {
        "assets/fonts/OpenSans.ttf",
        "../assets/fonts/OpenSans.ttf",
        "../../assets/fonts/OpenSans.ttf",
    };
    for (const std::string& path : candidates) {
        if (font.loadFromFile(path)) {
            return true;
        }
    }
    std::cerr << "Could not find assets/fonts/OpenSans.ttf - run from the repository root.\n";
    return false;
}

// All the "what does this key/button do" logic lives here, so mouse clicks
// and keyboard presses behave exactly the same.
class CalculatorScreen {
public:
    void press(const std::string& key) {
        error_ = false;

        if (key == "C") {
            input_.clear();
            status_.clear();
            justEvaluated_ = false;
        } else if (key == "<") {
            if (!input_.empty()) input_.pop_back();
            justEvaluated_ = false;
        } else if (key == "=") {
            evaluate();
        } else {
            // After "=", typing a digit starts fresh, but typing an operator
            // continues from the result, just like a pocket calculator.
            bool startsNewNumber = std::isdigit(static_cast<unsigned char>(key[0])) ||
                                   key == "." || key == "(" || key == "sqrt" || key == "ans";
            if (justEvaluated_ && startsNewNumber) {
                input_.clear();
            }
            justEvaluated_ = false;
            input_ += (key == "sqrt") ? "sqrt(" : key;
        }
    }

    const std::string& input() const { return input_; }
    const std::string& status() const { return status_; }
    bool hasError() const { return error_; }

private:
    void evaluate() {
        if (input_.empty()) return;
        try {
            double result = calculator_.evaluate(input_);
            status_ = input_ + " =";
            input_ = calc::Calculator::format(result);
            justEvaluated_ = true;
        } catch (const calc::Error& e) {
            status_ = e.what();
            error_ = true;
        }
    }

    calc::Calculator calculator_;
    std::string input_;
    std::string status_;
    bool justEvaluated_ = false;
    bool error_ = false;
};

// Draw `text` right-aligned inside the display. Long text shrinks, and if it
// still does not fit we show only its right-hand end.
void drawRightAligned(sf::RenderWindow& window, sf::Text text, float y, unsigned maxSize) {
    const float maxWidth = kWindowWidth - 4 * kPadding;
    std::string content = text.getString();
    unsigned size = maxSize;
    text.setCharacterSize(size);
    while (text.getLocalBounds().width > maxWidth && size > 18) {
        text.setCharacterSize(--size);
    }
    while (text.getLocalBounds().width > maxWidth && content.size() > 1) {
        content.erase(0, 1);
        text.setString("..." + content);
    }
    text.setPosition(kWindowWidth - 2 * kPadding - text.getLocalBounds().width, y);
    window.draw(text);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(static_cast<unsigned>(kWindowWidth),
                                          static_cast<unsigned>(kWindowHeight)),
                            "Calc From Scratch", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    sf::Font font;
    if (!loadFont(font)) {
        return 1;
    }

    std::vector<Button> buttons = makeButtons();
    CalculatorScreen screen;
    int pressedIndex = -1;   // which button is held down right now (-1 = none)

    sf::RectangleShape display({kWindowWidth - 2 * kPadding, kDisplayHeight});
    display.setPosition(kPadding, kPadding);
    display.setFillColor(kDisplayColor);

    // ----- the game loop -------------------------------------------------
    while (window.isOpen()) {
        // 1. Handle every event that happened since the last frame.
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed &&
                       event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f point(static_cast<float>(event.mouseButton.x),
                                   static_cast<float>(event.mouseButton.y));
                for (std::size_t i = 0; i < buttons.size(); ++i) {
                    if (buttons[i].shape.getGlobalBounds().contains(point)) {
                        pressedIndex = static_cast<int>(i);
                        screen.press(buttons[i].label);
                    }
                }
            } else if (event.type == sf::Event::MouseButtonReleased) {
                pressedIndex = -1;
            } else if (event.type == sf::Event::TextEntered) {
                // Keyboard support: event.text.unicode is the typed character.
                sf::Uint32 c = event.text.unicode;
                if (c == '\r' || c == '=') {
                    screen.press("=");
                } else if (c == '\b') {
                    screen.press("<");
                } else if (c == 27 || c == 'c' || c == 'C') {   // 27 = Escape
                    screen.press("C");
                } else if (c < 128 && std::string("0123456789.+-*/^%()").find(static_cast<char>(c)) !=
                                          std::string::npos) {
                    screen.press(std::string(1, static_cast<char>(c)));
                }
            }
        }

        // 2. Update: colour each button depending on hover / pressed.
        sf::Vector2f mouse(sf::Mouse::getPosition(window));
        for (std::size_t i = 0; i < buttons.size(); ++i) {
            Button& b = buttons[i];
            if (static_cast<int>(i) == pressedIndex) {
                b.shape.setFillColor(lighten(b.baseColor, 60));
            } else if (b.shape.getGlobalBounds().contains(mouse)) {
                b.shape.setFillColor(lighten(b.baseColor, 25));
            } else {
                b.shape.setFillColor(b.baseColor);
            }
        }

        // 3. Draw everything, back to front.
        window.clear(kBackground);
        window.draw(display);

        sf::Text status(screen.status(), font);
        status.setFillColor(screen.hasError() ? kErrorColor : kDimTextColor);
        drawRightAligned(window, status, kPadding + 12.f, 20);

        sf::Text main(screen.input().empty() ? "0" : screen.input(), font);
        main.setFillColor(kTextColor);
        drawRightAligned(window, main, kPadding + 50.f, 44);

        for (const Button& b : buttons) {
            window.draw(b.shape);
            sf::Text label(b.label, font, 24);
            label.setFillColor(kTextColor);
            sf::FloatRect box = b.shape.getGlobalBounds();
            sf::FloatRect bounds = label.getLocalBounds();
            label.setPosition(box.left + (box.width - bounds.width) / 2.f - bounds.left,
                              box.top + (box.height - bounds.height) / 2.f - bounds.top);
            window.draw(label);
        }

        window.display();   // show the finished frame
    }
    return 0;
}
