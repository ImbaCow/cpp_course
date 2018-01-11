#pragma once
#include "consts.h"

struct Bullet
{
  sf::CircleShape shape;
  sf::Vector2f position;
  sf::Vector2f direction;
  bool isDead = 0;
  unsigned affiliation;
  float fireDmg;
  float fireLifeTime = FIRE_LIFE_TIME;
};

class Bullets : public sf::Drawable
{
public:
  std::vector<Bullet> bullets;

  void update(float dt);

  void addBullet(unsigned affiliation, sf::Vector2f tankPosition, float rotation);

private:
  void updateBulletPos(float dt);

  void eraseBullet();

  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};