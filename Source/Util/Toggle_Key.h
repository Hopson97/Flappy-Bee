#ifndef TOGGLE_KEY_H_INCLUDED
#define TOGGLE_KEY_H_INCLUDED

#include <SFML/Window/Keyboard.hpp>

class Toggle_Key
{
    public:
        Toggle_Key(sf::Keyboard::Key);

        bool isDown();

    private:
        sf::Keyboard::Key   m_key;
        bool                m_isLocked = false;
};

#endif // TOGGLE_KEY_H_INCLUDED
