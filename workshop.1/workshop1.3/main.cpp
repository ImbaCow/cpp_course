#include <SFML/Graphics.hpp>
#include <iostream>

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

void redrawFrame(sf::RenderWindow &window, sf::Sprite &cat)
{
    window.clear(sf::Color(255, 255, 255));
    window.draw(cat);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "cat");

    sf::Texture catT;
    catT.loadFromFile("./cat.png");

    sf::Sprite cat;
    cat.setTexture(catT);
    cat.setTextureRect(sf::IntRect(0, 0, 38, 35));
    cat.setPosition({400, 300});

    while (window.isOpen())
    {
        pollEvents(window);
        redrawFrame(window, cat);
    }
}