#include "Player.h"

#include "Resource_Manager.h"
#include "Display.h"

Player::Player(const Resource_Holder& resources)
{
    keyTest.key = sf::Keyboard::Space;

    m_sprite.setSize({70, 70});
    m_sprite.setTexture(&resources.textures.get(Texture_ID::Bee));
    m_sprite.move({300, 150});
}

void Player::input()
{
    if (keyTest.isDown())
    {
        m_velocity.y = -800;
    }
    m_velocity.y += 30;


}

void Player::update(float dt)
{
    m_sprite.move({  0,
                     m_velocity.y * dt});

    m_velocity *= 0.98f;

    if (m_sprite.getPosition().y < 0 )
    {
        m_sprite.setPosition(m_sprite.getPosition().x, 0);
        m_velocity.y = 0;
    }
}

void Player::draw()
{
    Display::draw(m_sprite);
}
