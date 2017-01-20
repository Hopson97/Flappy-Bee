#include "Player.h"

#include "Resource_Manager.h"
#include "Display.h"
#include "States/Playing_State.h"

Player::Player(const Resource_Holder& resources)
{
    keyTest.key = sf::Keyboard::Space;

    m_sprite.setSize({50, 50});
    m_sprite.setOrigin({70 / 2, 70 / 2});
    m_sprite.setTexture(&resources.textures.get(Texture_ID::Bee));
    m_sprite.move({State::Playing::PLAYER_X,
                   Display::HEIGHT / 1.5});

    m_wingSound.setBuffer(resources.sounds.get(Sound_ID::Wing));

    constexpr int NUM_FRAMES      = 3;
    constexpr int FRAME_WIDTH     = 17;
    constexpr int FRAME_HEIGHT    = 12;

    for (int i = 0 ; i < NUM_FRAMES ; i++)
    {
        m_anim.addFrame({i * FRAME_WIDTH, 0, FRAME_WIDTH, FRAME_HEIGHT}, 0.5f);
    }
}

void Player::input()
{
    if (keyTest.isDown())
    {
        m_velocity.y = -750;
        rotate(-20);
        m_wingSound.play();
    }
    m_velocity.y += 50;
    rotate(1);
}

void Player::rotate(int degrees)
{
    constexpr int MAX_ROTATION = 30;

    m_rotation += degrees;
    m_sprite.rotate(degrees);

    if (m_rotation < -MAX_ROTATION)
    {
        m_sprite.setRotation( -MAX_ROTATION);
        m_rotation          = -MAX_ROTATION;
    }
    else if (m_rotation > MAX_ROTATION)
    {
        m_sprite.setRotation (MAX_ROTATION);
        m_rotation          = MAX_ROTATION;
    }
}




void Player::update(float dt)
{
    m_sprite.setTextureRect(m_anim.getFrame());

    m_sprite.move({0,
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
