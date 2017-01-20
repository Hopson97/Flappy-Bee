#ifndef SCROLLING_SPRITE_H_INCLUDED
#define SCROLLING_SPRITE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>

class Scolling_Sprite;
{
    public:
        Scrolling_Sprite(sf::Texture& texture,
                         sf::Vector2f& size,
                         sf::Vector2f position,
                         int speed);

    private:
        sf::RectangleShape m_sprtie;

        std::vector<int> xPositions;
};

#endif // SCROLLING_SPRITE_H_INCLUDED
