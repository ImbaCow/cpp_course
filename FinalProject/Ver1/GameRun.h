#pragma once
#include "SFML/Graphics.hpp"
#include "HeroTank.h"
#include "Enemies.h"
#include "GameEnd.h"
#include "GameLevel.h"
#include "GamePause.h"
#include "Boss.h"
#include "Math.h"

class GameRun
{
public:
  GameRun();

  void run(float dt, sf::RenderWindow &window, unsigned &GameStatus, sf::Vector2f &enemiesCount);
  void end(sf::RenderWindow &window, unsigned &GameStatus);
  void restart(sf::RenderWindow &window, unsigned &GameStatus, sf::Vector2f &enemiesCount);
  void pause(sf::RenderWindow &window, unsigned &GameStatus);
  void levelUp(float dt, sf::RenderWindow &window, unsigned &GameStatus);
  void bossLevel(float dt, sf::RenderWindow &window, unsigned &GameStatus, sf::Vector2f &enemiesCount);

private:
  float score;
  Math math;
  sf::Texture texture;
  sf::Sprite sprite;

  GamePause gamePause;
  GameLevel gameLevel;
  GameEnd gameEnd;

  bool isWin;
  unsigned prevGameStatus;

  Bullets bullets;
  HeroTank heroTank;
  Enemies enemies;
  Boss boss;

  void pollEvents(sf::RenderWindow &window, unsigned &GameStatus);
  void update(float dt);
  void redrawFrame(sf::RenderWindow &window);

  void checkWin(unsigned &GameStatus, sf::Vector2f &enemiesCount);
  void checkHit();

  void initEnemies(float dt, sf::Vector2f &enemiesCount);
};