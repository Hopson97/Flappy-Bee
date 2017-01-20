#include "Display.h"

#include <memory>

namespace Display
{
    std::unique_ptr<sf::RenderWindow> window;

    void init(const std::string& name)
    {
        window = std::make_unique<sf::RenderWindow>(sf::VideoMode{WIDTH, HEIGHT},
                                                      name,
                                                      sf::Style::Close);
    }

    bool isOpen()
    {
        return window->isOpen();
    }

    sf::RenderWindow& get()
    {
        return *window;
    }

    void close()
    {
        window->close();
    }


    void update()
    {
        window->display();
    }

    void clear (const sf::Color& colour)
    {
        window->clear(colour);
    }

    void toggleVSync()
    {
        window->setFramerateLimit(60);
    }


    void draw(const sf::Drawable& drawable)
    {
        window->draw(drawable);
    }
}
