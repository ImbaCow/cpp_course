#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>

static constexpr unsigned WINDOW_WIDTH = 800;
static constexpr unsigned WINDOW_HEIGHT = 600;

void pollEvents(sf::RenderWindow &window, sf::Vertex *pointer);

float vectorLenght(sf::Vector2f &argument);

void init(sf::Vertex *pointer);

void redrawFrame(sf::RenderWindow &window, sf::Vertex *pointer);

void onMouseMove(sf::Vector2f centerPosition, sf::Vector2f mousePosition);

void createWindow(sf::RenderWindow &window);