#include "Toggle_Key.h"

Toggle_Key::Toggle_Key(sf::Keyboard::Key key)
:   m_key (key)
{ }

bool Toggle_Key::isDown()
{
    if (m_isLocked)
    {
        if (!sf::Keyboard::isKeyPressed(m_key))
        {
            m_isLocked = false;
        }
        return false;
    }
    else if (!m_isLocked)
    {
        if (sf::Keyboard::isKeyPressed(m_key))
        {
            m_isLocked = true;
            return true;
        }
    }
    return false;
}
