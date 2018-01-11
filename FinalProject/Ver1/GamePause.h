#pragma once
#include "SFML/Graphics.hpp"
#include "Math.h"

class GamePause : public sf::Drawable
{
public:
  GamePause();

  void pollEvents(sf::RenderWindow &window, unsigned &GameStatus, unsigned nextGameStatus);

  void checkGameResult(bool isWin);

  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
  Math math;
  sf::Vector2f mousePosition;
  sf::Vector2f clickPosition;

  sf::Font font;

  sf::Text menuText;
  sf::Text continueText;
  sf::Text pauseText;

  sf::RectangleShape menuButton;
  sf::RectangleShape continueButton;

  sf::RectangleShape backGround;

  void init();

  void redrawFrame(sf::RenderWindow &window);
};