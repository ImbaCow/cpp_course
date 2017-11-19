#include "main.h"

void createWindow(sf::RenderWindow &window)
{
    window.create(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Line");
}

void pollEvents(sf::RenderWindow &window, sf::Vertex *pointer)
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
            pointer[1].position = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
            onMouseMove(pointer[0].position, pointer[1].position);
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

void init(sf::Vertex *pointer)
{
    pointer[0].position = sf::Vector2f(400, 300);
    pointer[1].position = sf::Vector2f(400, 300);
    pointer[0].color = sf::Color::Black;
    pointer[1].color = sf::Color::Black;
}

void redrawFrame(sf::RenderWindow &window, sf::Vertex *pointer)
{
    window.clear(sf::Color::White);
    window.draw(pointer, 2, sf::Lines);
    window.display();
}