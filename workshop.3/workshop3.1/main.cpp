#include "eventloop.h"
#include "Initials.h"

int main()
{
    sf::RenderWindow window;
    createWindow(window);
    sf::Clock clock;

    Initials initial;
    initial.init();

    while (window.isOpen())
    {
        const float dt = clock.restart().asSeconds();
        pollEvents(window);
        initial.updatePosition(dt);
        redrawFrame(window, initial);
    }
}