//
// Created by VerOchka on 30.09.2023.
//

#ifndef LAB1_KOSHI_INPUTSYSTEM_H
#define LAB1_KOSHI_INPUTSYSTEM_H

#include <sfml/Graphics.hpp>
#include <array>

class InputSystem {
public:
    InputSystem();

    InputSystem(const sf::RenderWindow &window);

    void keyboardKeyPressed(sf::Keyboard::Key key);

    void keyboardKeyReleased(sf::Keyboard::Key key);

    void mouseButtonPressed(sf::Mouse::Button button);

    void mouseButtonReleased(sf::Mouse::Button button);

    bool isKeyboardKeyPressed(sf::Keyboard::Key key) const;

    bool isKeyboardKeyDown(sf::Keyboard::Key key) const;

    bool isKeyboardKeyUp(sf::Keyboard::Key key) const;

    bool isMouseButtonPressed(sf::Mouse::Button button) const;

    bool isMouseButtonDown(sf::Mouse::Button button) const;

    bool isMouseButtonUp(sf::Mouse::Button button) const;

    void refresh();

    bool isMouseMoved;
    bool isMouseEntered;
    bool isMouseLeft;
    int mouseX;
    int mouseY;
    bool isMouseWheelScrolled;
    float mouseWheelDelta;
private:
    const sf::RenderWindow *window;
    enum KeyState {
        FREE, DOWN, PRESSED, UP
    };

    std::array<KeyState, sf::Keyboard::KeyCount> keyboardKeysState;
    std::array<KeyState, sf::Mouse::ButtonCount> mouseButtonsState;
};


#endif //LAB1_KOSHI_INPUTSYSTEM_H
