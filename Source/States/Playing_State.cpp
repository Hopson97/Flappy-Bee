#include "Playing_State.h"

#include "../Resource_Manager.h"
#include "../Application.h"
#include "../Display.h"

namespace State
{
    Playing::Playing(Application& application)
    :   State_Base (application)
    ,   m_player    (application.getResources())
    {

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
    }

    void Playing::draw()
    {
        m_player.draw();
    }

}
