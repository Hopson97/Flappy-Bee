#include "Pipe.h"

#include "Display.h"
#include "Player.h"
#include "Util/Random.h"
#include "States/Playing_State.h"

Pipe_Pair::Pipe::Pipe(const Resource_Holder& resources, bool rotate)
:   m_isFlipped (rotate)
{
    if (rotate)
    {
        m_sprite.setTexture (&resources.textures.get(Texture_ID::Pipe_Top));
        m_sprite.setRotation(180);
    }
    else
    {
        m_sprite.setTexture (&resources.textures.get(Texture_ID::Pipe_Bottom));
    }

    m_sprite.setSize    ({TRAP_WIDTH, 1000});
}

void Pipe_Pair::Pipe::draw()
{
    Display::draw(m_sprite);
}

void Pipe_Pair::Pipe::setY(int y)
{
    m_sprite.setPosition(m_sprite.getPosition().x, y);
}

void Pipe_Pair::Pipe::setX(int x)
{
    m_sprite.setPosition(x, m_sprite.getPosition().y);
    if (m_isFlipped)
    {
        m_sprite.move(TRAP_WIDTH, 0);
    }
}


sf::FloatRect Pipe_Pair::Pipe::getBounds() const
{
    return m_sprite.getGlobalBounds();
}

//  ===  ===  ===  ===  ===  ===  ===  ===  ===
//              FLY TRAP PAIR BEGIN
//  ===  ===  ===  ===  ===  ===  ===  ===  ===
Pipe_Pair::Pipe_Pair(const Resource_Holder& resources, int initX)
:   m_top               (resources, true)
,   m_bottom            (resources, false)
,   m_currentXPosition  (initX)
{
    setRandomY();

    m_scoreSound.setBuffer(resources.sounds.get(Sound_ID::Score));
}

void Pipe_Pair::update(float dt, int& score)
{
    m_currentXPosition -= MOVE_SPEED * dt;

    if (m_currentXPosition <= -TRAP_WIDTH)
    {
        m_currentXPosition = Display::WIDTH;
        setRandomY();
        m_scoreGot = false;
    }

    if (m_currentXPosition <= State::Playing::PLAYER_X &&
        !m_scoreGot)
    {
        m_scoreGot = true;
        score++;
        m_scoreSound.play();
    }

    m_top   .setX (m_currentXPosition);
    m_bottom.setX (m_currentXPosition);
}

void Pipe_Pair::draw()
{
    if (m_currentXPosition < Display::WIDTH)
    {
        m_top   .draw();
        m_bottom.draw();
    }
}

bool Pipe_Pair::colliding(Player& player) const
{
    auto& sprite = player.getSprite();

    return sprite.getGlobalBounds().intersects(m_bottom. getBounds()) ||
           sprite.getGlobalBounds().intersects(m_top.    getBounds());
}

int Pipe_Pair::getRandomYPos()
{
    static int minY = 50;
    static int maxY = 400;

    return Random::integer(minY, maxY);
}

void Pipe_Pair::setRandomY()
{
    auto y = getRandomYPos();
    m_top   .setY   (y);
    m_bottom.setY   (y + GAP_BETWEEN_TRAPS);
}


