#pragma once
#include "SFML/Graphics.hpp"
#include "Math.h"

class GameEnd : public sf::Drawable
{
public:
  GameEnd();

  void pollEvents(sf::RenderWindow &window, unsigned &GameStatus);

  void checkGameResult(bool isWin, int score);

  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
  Math math;
  sf::Vector2f mousePosition;
  sf::Vector2f clickPosition;

  sf::Font font;

  sf::Text scoreText;
  sf::Text menuText;
  sf::Text gameResult;

  sf::RectangleShape menuShape;
  sf::RectangleShape backGround;

  void init();

  void redrawFrame(sf::RenderWindow &window);
};