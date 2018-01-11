#pragma once
#include "GameRun.h"
#include "GameMenu.h"
#include "SFML/Graphics.hpp"

class Game
{
public:
  Game();
  void run();

private:
  sf::RenderWindow window;

  GameRun gameRun;
  GameMenu gameMenu;

  sf::Vector2f enemiesCount = {0, 0};

  unsigned GameStatus = 0;

  void createWindow();
};