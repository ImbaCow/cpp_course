#include "main.hpp"

int main()
{
    sf::RenderWindow window;
    createWindow(window);

    sf::Vertex pointer[2];
    init(pointer);

    while (window.isOpen())
    {
        pollEvents(window, pointer);
        redrawFrame(window, pointer);
    }
}