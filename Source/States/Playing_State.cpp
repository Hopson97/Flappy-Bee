#include "Playing_State.h"

#include "../Resource_Manager.h"
#include "../Application.h"
#include "../Display.h"

namespace State
{
    Playing::Playing(Application& application)
    :   State_Base  (application)
    ,   m_player    (application.getResources())
    {
        m_background.setTexture     (&getTexture(Texture_ID::Background_Nature));
        m_background.setSize        ({Display::WIDTH, Display::HEIGHT});

        m_ground.setSize        ({Display::WIDTH, 100});
        m_ground.setPosition    (0, DEATH_HEIGHT);
        m_ground.setTexture     (&getTexture(Texture_ID::Ground));

        for (int i = 0 ; i < NUM_PIPES ; i++)
        {
            m_trapPairs.emplace_back(application.getResources(),
                                     Display::WIDTH + i * 500);
        }
        m_scoreText.setPosition({Display::WIDTH / 2, 0});
        m_scoreText.setFont(getFont(Font_ID::RS));
        m_scoreText.setOutlineColor(sf::Color::Black);
        m_scoreText.setOutlineThickness(2);

        m_hitSound.setBuffer(getSound(Sound_ID::Hit));

    }

    void Playing::input(const sf::Event& e)
    { }

    void Playing::input()
    {
        m_player.input();
    }

    void Playing::update(float dt)
    {
        m_player.update(dt);

        for (auto& trap : m_trapPairs)
        {
            trap.update(dt, m_currentScore);
        }
        m_scoreText.setString(std::to_string(m_currentScore));

        for (Pipe_Pair& pair : m_trapPairs)
        {
            if (pair.colliding(m_player))
            {
                m_hitSound.play();
            }
        }
    }

    void Playing::draw()
    {
        Display::draw(m_background);


        for (auto& trap : m_trapPairs)
        {
            trap.draw();
        }

        Display::draw(m_ground);
        m_player.draw();

        Display::draw(m_scoreText);
    }

}
