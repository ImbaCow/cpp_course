#pragma once
#include "constants.h"

class Ship : public sf::Drawable
{
private:
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  void checkWallCollision();

  sf::Vertex ship[5];
  sf::Vertex shipBoost[5];

  float rotation = 0;
  sf::Vector2f speed = sf::Vector2f(0, 0);
  sf::Vector2f position = START_POSITION;
  sf::Vector2f direction = sf::Vector2f(0, 0); // Кордината х отвечает за поворот, у - за движение вперед
  sf::Vector2f boostDirection;
  float rotationSum = 0;

  sf::Transform transform;

public:
  void init();

  void updatePosition();

  void update(float dt);

  void keyPressed(sf::Event event);

  void keyReleased(sf::Event event);
};
