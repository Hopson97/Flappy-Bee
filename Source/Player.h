#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "Animation.h"
#include "Util/Toggle_Key.h"

class Resource_Holder;

class Player
{
    public:
        Player(const Resource_Holder& resources);

        void input  ();
        void update (float dt);
        void draw   ();

        void animate();
        void kill();
        bool isAtDeathHeight() const;

        const sf::RectangleShape& getSprite() const { return m_sprite; }

    private:
        void rotate(int degrees);

        sf::Vector2f m_velocity;
        sf::RectangleShape m_sprite;

        Toggle_Key m_spacebarToggle;
        int m_rotation = -25;

        Animation m_anim;

        sf::Sound m_wingSound;

        bool m_isDead               = false;
        bool m_reachedDeathHeight   = false;
};

#endif // PLAYER_H
