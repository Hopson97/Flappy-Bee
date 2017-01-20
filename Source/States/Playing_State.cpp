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
        m_background.setSize        ({1280, 720});

        for (int i = 0 ; i < NUM_PIPES ; i++)
        {
            m_trapPairs.emplace_back(application.getResources(), Display::WIDTH);
        }
    }

    void Playing::input(const sf::Event& e)
    {

    }

    void Playing::input()
    {
        m_player.input();
    }

    void Playing::update(float dt)
    {
        m_player.update(dt);

        for (auto& trap : m_trapPairs)
        {
            trap.update(dt);
        }
    }

    void Playing::draw()
    {
        Display::draw(m_background);
        m_player.draw();

        for (auto& trap : m_trapPairs)
        {
            trap.draw();
        }
    }

}
