#include "main.hpp"

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Line");

    sf::Vertex pointer[2];

    init(pointer, std::size(pointer));

    while (window.isOpen())
    {
        pollEvents(window, pointer, std::size(pointer));
        redrawFrame(window, pointer, std::size(pointer));
    }
}