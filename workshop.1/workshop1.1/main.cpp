#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &pointer)
{
    window.clear(sf::Color(255, 255, 255));
    window.draw(pointer);
    window.display();
}

void pollEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

void init(sf::ConvexShape &pointer)
{
    pointer.setFillColor(sf::Color(255, 255, 0));
    pointer.setPosition(400, 300);
    pointer.setPointCount(7);
    pointer.setPoint(0, {0, -100});
    pointer.setPoint(1, {100, 0});
    pointer.setPoint(2, {0, 100});
    pointer.setPoint(3, {0, 50});
    pointer.setPoint(4, {-100, 50});
    pointer.setPoint(5, {-100, -50});
    pointer.setPoint(6, {0, -50});
    pointer.setOutlineThickness(3);
    pointer.setOutlineColor(sf::Color(0, 0, 0));
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Pointer2.0",
        sf::Style::Default, settings);

    sf::ConvexShape pointer;

    init(pointer);

    while (window.isOpen())
    {
        pollEvents(window);
        redrawFrame(window, pointer);
    }
}