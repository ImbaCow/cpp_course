#pragma once
#include "consts.h"
#include "Bullets.h"
#include "Math.h"
#include <vector>

struct Enemy
{
  sf::ConvexShape body;
  sf::ConvexShape head;

  sf::RectangleShape fullHealth;
  sf::RectangleShape currentHealth;

  sf::Vector2f position;

  float rotateDirection;
  float rotation;
  float healthPoints;
  float shotCooldown = 0;
  float changeMoveRadius;
};

class Enemies : public sf::Drawable
{
public:
  float spawnTime = SPAWN_COOLDOWN;

  std::vector<Enemy> range;
  std::vector<Enemy> melee;

  void addRange(sf::Vector2f newTankPosition);
  void addMelee(sf::Vector2f newTankPosition);

  void update(float dt, sf::Vector2f heroPosition, sf::Vector2f heroDirection, Bullets &bullets);

private:
  sf::Texture texture;
  Math math;

  void initBody(Enemy &enemy);
  void initHealthBars(Enemy &enemy);

  void checkWallCollision(sf::Vector2f &position);
  void updateHealthBar(Enemy &enemy, float maxHealthPoints);
  void headUpdate(sf::Vector2f heroPosition, sf::Vector2f heroDirection, Enemy &enemy);
  void bodyUpdate(float dt, sf::Vector2f heroPosition, Enemy &enemy);
  void bodyRotationUpdate(float dt, sf::Vector2f heroPosition, Enemy &enemy);
  void bulletShot(Bullets &bullets, float dt);

  void checkRotation(float &rotateDirection, float &deltaAngle);
  void checkRangeCollusion(Enemy &enemy, size_t fi);
  void checkMeleeCollusion(Enemy &enemy, size_t fi);

  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  void eraseDeadEnemy();
};