#pragma once
#include "SFML/Graphics.hpp"
#include "Math.h"

class GameMenu
{
public:
  GameMenu();

  void run(sf::RenderWindow &window, unsigned &GameStatus);

private:
  Math math;
  sf::Vector2f mousePosition;
  sf::Vector2f clickPosition;

  sf::Font font;
  sf::Text playText;

  sf::Texture texture;

  sf::RectangleShape playShape;
  sf::Sprite backSprite;

  void init();

  void pollEvents(sf::RenderWindow &window, unsigned &GameStatus);

  void redrawFrame(sf::RenderWindow &window);
};