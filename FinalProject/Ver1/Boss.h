#pragma once
#include "SFML/Graphics.hpp"
#include "consts.h"
#include "Bullets.h"
#include "Enemies.h"
#include "Math.h"

class Boss : public sf::Drawable
{
public:
  sf::Vector2f position;

  sf::ConvexShape body;
  sf::ConvexShape head;
  sf::RectangleShape fullHealth;
  sf::RectangleShape currentHealth;

  float healthPoints;

  sf::Vector2f bodyDirection;
  sf::Vector2f speedDirection;

  void initBoss();

  void update(float dt, sf::Vector2f heroPosition, sf::Vector2f heroDirection, Bullets &bullets, Enemies &enemies);

private:
  Math math;

  float spawnCD;
  unsigned BossStage;

  float shotCD;
  float fireCD;
  float blastCD;

  sf::Texture texture;
  float rotateDirection;
  float rotation;

  void initHealthBars();

  void bulletShot(Bullets &bullets);
  void fireShot(Bullets &bullets);
  void blastShot(Bullets &bullets);

  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  void stageOneUpdate(float dt, sf::Vector2f heroPosition, sf::Vector2f heroDirection, Bullets &bullets);
  void stageTwoUpdate(float dt, sf::Vector2f heroPosition, sf::Vector2f heroDirection, Bullets &bullets, Enemies &enemies);
  void stageThreeUpdate(float dt, sf::Vector2f heroPosition, sf::Vector2f heroDirection, Bullets &bullets);
  void endScene(float dt);
  void checkStage(Enemies &enemies);

  void headUpdate(sf::Vector2f heroPosition, sf::Vector2f heroDirection);
  void bodyUpdate(float dt, sf::Vector2f heroPosition, float changeRadius);
  void bodyRotationUpdate(float dt, sf::Vector2f heroPosition);
  void checkRotation(float &rotateDirection, float &deltaAngle);
  void checkWallCollision();

  void spawnMinions(Enemies &enemies, float dt);
};