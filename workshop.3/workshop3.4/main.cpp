#include "eventloop.h"

int main()
{
    sf::RenderWindow window;
    createWindow(window);
    sf::Clock clock;

    Ship ship;
    ship.init();

    while (window.isOpen())
    {
        const float dt = clock.restart().asSeconds();
        pollEvents(window, ship);
        ship.update(dt);
        redrawFrame(window, ship);
    }
}