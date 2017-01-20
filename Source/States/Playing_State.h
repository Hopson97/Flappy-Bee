#ifndef PLAYING_STATE_H_INCLUDED
#define PLAYING_STATE_H_INCLUDED

#include <vector>

#include "State_Base.h"

#include "../Animation.h"
#include "../Player.h"
#include "Fly_Trap.h"

namespace State
{
    class Playing : public State_Base
    {
        constexpr static int NUM_PIPES = 1;

        public:
            Playing (Application& application);

            void input  (const sf::Event& e);
            void input  ();
            void update (float dt);
            void draw   ();

        private:
            Player m_player;
            sf::RectangleShape m_background;

            std::vector<Fly_Trap_Pair> m_trapPairs;
    };
}

#endif // PLAYING_STATE_H_INCLUDED
