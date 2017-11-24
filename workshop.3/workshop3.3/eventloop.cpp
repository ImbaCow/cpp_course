#include "eventloop.h"
#include <iostream>
#include <cmath>

void createWindow(sf::RenderWindow &window)
{
    window.create(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Line");
}

void pollEvents(sf::RenderWindow &window, Line &pointer)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            pointer.line[1].position = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
            onMouseMove(pointer.line[0].position, pointer.line[1].position);
            break;
        default:
            break;
        }
    }
}

void onMouseMove(sf::Vector2f centerPosition, sf::Vector2f mousePosition)
{
    sf::Vector2f delta = mousePosition - centerPosition;
    std::cout << "distance: " << vectorLenght(delta) << std::endl;
}

float vectorLenght(sf::Vector2f &argument)
{
    return (pow((pow(argument.x, 2.0) + pow(argument.y, 2.0)), 0.5));
}

void init(Line &pointer)
{
    pointer.line[0].position = sf::Vector2f(400, 300);
    pointer.line[1].position = sf::Vector2f(400, 300);
    pointer.line[0].color = sf::Color::Black;
    pointer.line[1].color = sf::Color::Black;
}

void redrawFrame(sf::RenderWindow &window, Line &pointer)
{
    window.clear(sf::Color::White);
    window.draw(pointer.line, 2, sf::Lines);
    window.display();
}