#include "Playing_State.h"

#include "../Resource_Manager.h"
#include "../Application.h"
#include "../Display.h"
#include "World_Constants.h"

namespace State
{
    Playing::Playing(Application& application)
    :   State_Base          (application)
    ,   m_player            (application.getResources())
    ,   m_spacebarToggle    (sf::Keyboard::Space)
    {
        m_background.setTexture     (&getTexture(Texture_ID::Background_Nature));
        m_background.setSize        ({Display::WIDTH, Display::HEIGHT});

        m_ground.setSize        ({Display::WIDTH, 100});
        m_ground.setPosition    (0, World_Constants::GROUND_HEIGHT);
        m_ground.setTexture     (&getTexture(Texture_ID::Ground));

        m_hitSound.setBuffer(getSound(Sound_ID::Hit));

        m_scoreText.setPosition({Display::WIDTH / 2, 0});
        m_scoreText.setFont(getFont(Font_ID::RS));
        m_scoreText.setOutlineColor(sf::Color::Black);
        m_scoreText.setOutlineThickness(2);

        m_pressSpacebar.setPosition({Display::WIDTH / 2, Display::HEIGHT / 2});
        m_pressSpacebar.setFont(getFont(Font_ID::RS));
        m_pressSpacebar.setOutlineColor(sf::Color::Black);
        m_pressSpacebar.setOutlineThickness(2);
        m_pressSpacebar.setString("Press Spacebar to Continue!");

        sf::FloatRect textRect = m_pressSpacebar.getLocalBounds();
        m_pressSpacebar.setOrigin(textRect.left + textRect.width /  2.0f,
                                  textRect.top  + textRect.height / 2.0f);

        reset();
    }

    void Playing::input(const sf::Event& e)
    { }

    void Playing::input()
    {
        switch (m_stage)
        {
            case Stage::Pre:
                if (m_spacebarToggle.isDown())
                {
                    m_stage = Stage::Playing;
                }
                break;

            case Stage::Playing:
                m_player.input();
                break;

            case Stage::Dead:
                if (m_spacebarToggle.isDown())
                {
                    m_stage = Stage::Pre;
                    reset();
                }
                break;

            default:
                break;
        }
    }

    void Playing::update(float dt)
    {
        m_scoreText.setString(std::to_string(m_currentScore));

        switch (m_stage)
        {
            case Stage::Pre:
                m_player.animate();
                break;

            case Stage::Playing:
                m_player.update(dt);

                //Update pipes
                for (auto& trap : m_trapPairs)
                {
                    trap.update(dt, m_currentScore);
                }

                //Test for player collision with pipes/ ground
                for (Pipe_Pair& pair : m_trapPairs)
                {
                    if (pair.colliding(m_player) ||
                        m_player.getBounds().intersects(m_ground.getGlobalBounds()))
                    {
                        m_hitSound.play();
                        m_player.kill();
                        m_stage = Stage::Death_In_Process;
                    }
                }
                break;

            case Stage::Death_In_Process:
                m_player.update(dt);
                if (m_player.isAtDeathHeight())
                {
                    m_stage = Stage::Dead;
                }
                break;


            default:
                break;
        }
    }

    void Playing::draw()
    {
        Display::draw(m_background);

        switch (m_stage)
        {
            case Stage::Pre:
                Display::draw(m_pressSpacebar);
                break;

            case Stage::Playing:
                for (auto& trap : m_trapPairs)
                {
                    trap.draw();
                }
                break;

            case Stage::Death_In_Process:
                for (auto& trap : m_trapPairs)
                {
                    trap.draw();
                }
                break;

            case Stage::Dead:
                for (auto& trap : m_trapPairs)
                {
                    trap.draw();
                }
                Display::draw(m_pressSpacebar);
                break;

            default:
                break;
        }

        Display::draw(m_ground);
        m_player.draw();

        Display::draw(m_scoreText);
    }

    void Playing::reset()
    {
        m_trapPairs.clear();
        for (int i = 0 ; i < NUM_PIPES ; i++)
        {
            m_trapPairs.emplace_back(m_p_application->getResources(),
                                     Display::WIDTH + i * 500);
        }
        m_player.reset();

        m_currentScore = 0;
        m_stage = Stage::Pre;
    }


}
