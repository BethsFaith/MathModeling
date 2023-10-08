//
// Created by VerOchka on 30.09.2023.
//

#include "InputSystem.h"

InputSystem::InputSystem()
{ }
InputSystem::InputSystem(const sf::RenderWindow& window)
{
    this->window = &window;
    isMouseMoved = 0;
    isMouseEntered = 0;
    isMouseLeft = 0;
    mouseX = sf::Mouse::getPosition(window).x;
    mouseY = sf::Mouse::getPosition(window).y;
    isMouseWheelScrolled = 0;
    mouseWheelDelta = 0;
}

void InputSystem::keyboardKeyPressed(sf::Keyboard::Key key)
{
    keyboardKeysState[key] = DOWN;
}
void InputSystem::keyboardKeyReleased(sf::Keyboard::Key key)
{
    keyboardKeysState[key] = UP;
}
void InputSystem::mouseButtonPressed(sf::Mouse::Button button)
{
    mouseButtonsState[button] = DOWN;
}
void InputSystem::mouseButtonReleased(sf::Mouse::Button button)
{
    mouseButtonsState[button] = UP;
}

bool InputSystem::isKeyboardKeyPressed(sf::Keyboard::Key key) const
{
    return keyboardKeysState[key] == DOWN || keyboardKeysState[key] == PRESSED;
}
bool InputSystem::isKeyboardKeyDown(sf::Keyboard::Key key) const
{
    return keyboardKeysState[key] == DOWN;
}
bool InputSystem::isKeyboardKeyUp(sf::Keyboard::Key key) const
{
    return keyboardKeysState[key] == UP;
}
bool InputSystem::isMouseButtonPressed(sf::Mouse::Button button) const
{
    return mouseButtonsState[button] == DOWN || mouseButtonsState[button] == PRESSED;
}
bool InputSystem::isMouseButtonDown(sf::Mouse::Button button) const
{
    return mouseButtonsState[button] == DOWN;
}
bool InputSystem::isMouseButtonUp(sf::Mouse::Button button) const
{
    return mouseButtonsState[button] == UP;
}

void InputSystem::refresh()
{
    for (int i = 0; i < sf::Keyboard::KeyCount; i++)
    {
        if (keyboardKeysState[i] == DOWN)
            keyboardKeysState[i] = PRESSED;
        if (keyboardKeysState[i] == UP)
            keyboardKeysState[i] = FREE;
    }
    for (int i = 0; i < sf::Mouse::ButtonCount; i++)
    {
        if (mouseButtonsState[i] == DOWN)
            mouseButtonsState[i] = PRESSED;
        if (mouseButtonsState[i] == UP)
            mouseButtonsState[i] = FREE;
    }
    isMouseMoved = 0;
    isMouseEntered = 0;
    isMouseLeft = 0;
    isMouseWheelScrolled = 0;
    mouseWheelDelta = 0;
}
