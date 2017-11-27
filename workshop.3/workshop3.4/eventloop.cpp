#include "eventloop.h"

void createWindow(sf::RenderWindow &window)
{
    sf::VideoMode videoMode(WINDOW_WIDTH, WINDOW_HEIGHT);
    const std::string title = "Initials";
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(videoMode, title, sf::Style::Default, settings);
    window.setKeyRepeatEnabled(false);
}

void pollEvents(sf::RenderWindow &window, Ship &ship)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::KeyPressed:
            ship.keyPressed(event);
            break;
        case sf::Event::KeyReleased:
            ship.keyReleased(event);
            break;
        default:
            break;
        }
    }
}

void redrawFrame(sf::RenderWindow &window, sf::Drawable &ship)
{
    window.clear();
    window.draw(ship);
    window.display();
}