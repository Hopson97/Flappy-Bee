#ifndef FLY_TRAP_H_INCLUDED
#define FLY_TRAP_H_INCLUDED

#include <Resource_Manager.h>

class Fly_Trap_Pair
{
    constexpr static int GAP_BETWEEN_TRAPS = 210;
    constexpr static int MOVE_SPEED        = 100;

    class Fly_Trap
    {
        public:
            Fly_Trap(const Resource_Holder& resources, bool rotate);

            void setY   (int y);
            void setX   (int x);

            void draw   ();

            sf::FloatRect getBounds();

        private:
            sf::RectangleShape m_sprite;
    };

    public:
        constexpr static int TRAP_WDITH = 128;

        Fly_Trap_Pair(const Resource_Holder& resources,
                      int initX);

        void update     (float dt);
        void draw       ();

    private:
        int getRandomYPos();

        Fly_Trap m_top;
        Fly_Trap m_bottom;

        int m_currentXPosition;

};

#endif // FLY_TRAP_H_INCLUDED
