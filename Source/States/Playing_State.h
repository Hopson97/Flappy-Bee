#ifndef PLAYING_STATE_H_INCLUDED
#define PLAYING_STATE_H_INCLUDED

#include <vector>
#include <SFML/Audio.hpp>

#include "State_Base.h"

#include "../Animation.h"
#include "../Player.h"
#include "Pipe.h"
#include "Display.h"

namespace State
{
    class Playing : public State_Base
    {
        constexpr static int NUM_PIPES = 3;

        public:
            constexpr static int PLAYER_X       = 200;
            constexpr static int DEATH_HEIGHT   = Display::HEIGHT - 100;

            Playing (Application& application);

            void input  (const sf::Event& e);
            void input  ();
            void update (float dt);
            void draw   ();

        private:
            Player m_player;
            sf::RectangleShape m_background;
            sf::RectangleShape m_ground;

            std::vector<Pipe_Pair> m_trapPairs;

            int m_currentScore = 0;

            sf::Text m_scoreText;

            sf::Sound m_hitSound;
    };
}

#endif // PLAYING_STATE_H_INCLUDED
