#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Resource_Holder;

struct ToggleInput
{
    sf::Keyboard::Key key;

    bool isDown()
    {
        if (locked)
        {
            if (!sf::Keyboard::isKeyPressed(key))
            {
                locked = false;
            }
            return false;
        }
        else if (!locked)
        {
            if (sf::Keyboard::isKeyPressed(key))
            {
                locked = true;
                return true;
            }
        }
        return false;
    }

    bool locked = false;
};

class Player
{
    public:
        Player(const Resource_Holder& resources);

        void input  ();
        void update (float dt);
        void draw   ();

    private:
        sf::Vector2f m_velocity;
        sf::RectangleShape m_sprite;

        ToggleInput keyTest;
};

#endif // PLAYER_H
