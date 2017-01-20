#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Animation.h"

class Resource_Holder;

class ToggleInput
{
    public:
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

        sf::Keyboard::Key key;
        bool locked = false;
};

class Player
{
    public:
        Player(const Resource_Holder& resources);

        void input  ();
        void update (float dt);
        void draw   ();

        const sf::RectangleShape& getSprite() const { return m_sprite; }

    private:
        void rotate(int degrees);

        sf::Vector2f m_velocity;
        sf::RectangleShape m_sprite;

        ToggleInput keyTest;
        int m_rotation = 0;

        Animation m_anim;
};

#endif // PLAYER_H
