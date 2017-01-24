#ifndef WORLD_CONSTANTS_H_INCLUDED
#define WORLD_CONSTANTS_H_INCLUDED

#include "Display.h"

namespace World_Constants
{
    constexpr int   GRAVITY         = 100,
                    PLAYER_X        = 200,
                    GROUND_HEIGHT   = Display::HEIGHT - 100;

    namespace Pipe
    {
        constexpr int Y_GAP = 175;
        constexpr int SPEED = 800;
    }
}

#endif // WORLD_CONSTANTS_H_INCLUDED
