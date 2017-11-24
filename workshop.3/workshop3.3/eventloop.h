#pragma once
#include <SFML/Graphics.hpp>

static constexpr unsigned WINDOW_WIDTH = 800;
static constexpr unsigned WINDOW_HEIGHT = 600;

struct Line
{
    sf::Vertex line[2];
};

void pollEvents(sf::RenderWindow &window, Line &pointer);

float vectorLenght(sf::Vector2f &argument);

void init(Line &pointer);

void redrawFrame(sf::RenderWindow &window, Line &pointer);

void onMouseMove(sf::Vector2f centerPosition, sf::Vector2f mousePosition);

void createWindow(sf::RenderWindow &window);