#include "Fly_Trap.h"

#include "Display.h"
#include "Util/Random.h"

#include <iostream>

Fly_Trap_Pair::Fly_Trap::Fly_Trap(const Resource_Holder& resources, bool rotate)
{
    m_sprite.setTexture (&resources.textures.get(Texture_ID::Fly_Trap));
    m_sprite.setSize    ({TRAP_WDITH, 512});

    if (rotate)
    {
        m_sprite.setRotation(180);
    }
}

void Fly_Trap_Pair::Fly_Trap::draw()
{
    Display::draw(m_sprite);
}

void Fly_Trap_Pair::Fly_Trap::setY(int y)
{
    m_sprite.setPosition(m_sprite.getPosition().x, y);
}

void Fly_Trap_Pair::Fly_Trap::setX(int x)
{
    m_sprite.setPosition(x, m_sprite.getPosition().y);
}


sf::FloatRect Fly_Trap_Pair::Fly_Trap::getBounds()
{
    return m_sprite.getLocalBounds();
}

//  ===  ===  ===  ===  ===  ===  ===  ===  ===
//              FLY TRAP PAIR BEGIN
//  ===  ===  ===  ===  ===  ===  ===  ===  ===
Fly_Trap_Pair::Fly_Trap_Pair(const Resource_Holder& resources, int initX)
:   m_top               (resources, false)
,   m_bottom            (resources, false)
,   m_currentXPosition  (initX)
{
    auto y = getRandomYPos();

    m_top   .setY   (y);
    m_bottom.setY   (y + GAP_BETWEEN_TRAPS);
}

void Fly_Trap_Pair::update(float dt)
{
    std::cout << m_currentXPosition << std::endl;
     m_currentXPosition -= MOVE_SPEED * dt;

    if (m_currentXPosition == -TRAP_WDITH)
    {
        m_currentXPosition = Display::WIDTH;
    }

    m_top   .setX (m_currentXPosition);
    m_bottom.setX (m_currentXPosition);
}

void Fly_Trap_Pair::draw()
{
    if (m_currentXPosition < Display::WIDTH)
    {
        m_top   .draw();
        m_bottom.draw();
    }
}

int Fly_Trap_Pair::getRandomYPos()
{
    static int minY =                   200;
    static int maxY = 800;

    return Random::integer(minY, maxY);
}

