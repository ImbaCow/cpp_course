#pragma once
#include "consts.h"
#include "Boss.h"
#include "Math.h"
#include <string>

class GameLevel : public sf::Drawable
{
public:
  GameLevel();

  void checkLevelUp(float dt, unsigned &GameStatus, Boss &boss);

  size_t currentLevel = 0;

  std::vector<sf::Vector2f> enemiesCount;

private:
  Math math;

  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  sf::Font font;
  sf::Text levelText;
  std::string levelString;

  float timer = 0;
};