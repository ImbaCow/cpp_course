#include "eventloop.h"

int main()
{
    sf::RenderWindow window;
    createWindow(window);

    Line pointer;
    init(pointer);

    while (window.isOpen())
    {
        pollEvents(window, pointer);
        redrawFrame(window, pointer);
    }
}