#include <cmath>
#include <SFML/Graphics.hpp>

void pollEvents(sf::RenderWindow &window, sf::Vertex *pointer, size_t count);

float vectorLenght(sf::Vector2f &argument);

void init(sf::Vertex *pointer, size_t count);

void redrawFrame(sf::RenderWindow &window, sf::Vertex *pointer, size_t count);

void onMouseMove(sf::Vector2f centerPosition, sf::Vector2f mousePosition);