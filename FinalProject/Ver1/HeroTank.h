#pragma once
#include "SFML/Graphics.hpp"
#include "consts.h"
#include "Bullets.h"
#include "Math.h"

class HeroTank : public sf::Drawable
{
public:
  void initHero();

  sf::Vector2f position;
  sf::Vector2f mousePosition;

  sf::ConvexShape body;

  bool isShooting;
  float healthPoints = MAX_HEALTH;

  sf::Vector2f bodyDirection;
  sf::Vector2f speedDirection;

  void keyPressed(sf::Event event, Bullets &bullets);

  void keyReleased(sf::Event event);

  void update(float dt, Bullets &bullets);

private:
  sf::ConvexShape head;

  sf::RectangleShape fullHealth;
  sf::RectangleShape currentHealth;
  sf::RectangleShape cdBar;

  float rotation;
  float blastCD;
  float shotCD;
  sf::Texture texture;

  void bulletShot(Bullets &bullets);

  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  void checkWallCollision();

  Math math;

  void headUpdate(float dt);
  void bodyUpdate(float dt);
  void updateBars();

  void initHealthBars();

  void blastShot(Bullets &bullets);
};