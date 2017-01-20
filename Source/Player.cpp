#include "Player.h"

#include "Resource_Manager.h"
#include "Display.h"
#include "States/Playing_State.h"

#include <iostream>

Player::Player(const Resource_Holder& resources)
:   m_spacebarToggle (sf::Keyboard::Space)
{
    m_sprite.setSize({50, 50});
    m_sprite.setOrigin({70 / 2, 70 / 2});
    m_sprite.setTexture(&resources.textures.get(Texture_ID::Bee));
    m_sprite.move({State::Playing::PLAYER_X,
                   Display::HEIGHT / 2.5});

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
    if (!m_isDead)
    {
        if (m_spacebarToggle.isDown())
        {
            m_velocity.y = -850;
            rotate(-50);
            m_wingSound.play();
        }
    }
}

void Player::rotate(int degrees)
{
    constexpr int MAX_ROTATION = 30;

    m_rotation += degrees;

    if (m_rotation < -MAX_ROTATION)
    {
        m_rotation          = -MAX_ROTATION;
    }
    else if (m_rotation > MAX_ROTATION)
    {
        m_rotation          = MAX_ROTATION;
    }

    m_sprite.setRotation(m_rotation);
}


void Player::animate()
{
    static sf::Clock timer;
    m_sprite.setTextureRect(m_anim.getFrame());
    if (timer.getElapsedTime() > (m_wingSound.getBuffer()->getDuration()))
    {
        timer.restart();
        m_wingSound.play();
    }
}

void Player::update(float dt)
{
    m_velocity.y += 45;
    rotate(1);

    if (m_sprite.getPosition().y < State::Playing::DEATH_HEIGHT)
    {
        m_sprite.move({0,
                       m_velocity.y * dt});
        m_velocity *= 0.98f;
    }
    else
    {
        m_reachedDeathHeight = true;
        std::cout << "death height is now true" << std::endl;
    }

    if (!m_isDead)
    {
        m_sprite.setTextureRect(m_anim.getFrame());

        if (m_sprite.getPosition().y < 0 )
        {
            m_sprite.setPosition(m_sprite.getPosition().x, 0);
            m_velocity.y = 0;
        }
    }
}

void Player::kill()
{
    m_isDead = true;
}

bool Player::isAtDeathHeight() const
{
    if (m_reachedDeathHeight)
    {
        std::cout << "death height " << m_reachedDeathHeight << std::endl;
    }


    return m_reachedDeathHeight;
}


void Player::draw()
{
    Display::draw(m_sprite);
}
