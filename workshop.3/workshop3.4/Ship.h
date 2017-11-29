#pragma once
#include "constants.h"

class Ship : public sf::Drawable
{
private:
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  void checkWallCollision(); // Чтобы не терять корабль за пределами экрана, перемещаем корабль
                             // при прохождении через край окна на противоположный конец

  void updatePosition();

  sf::Vertex ship[5];
  sf::Vertex shipBoost[3];

  float rotation = 0;
  sf::Vector2f speed = sf::Vector2f(0, 0);
  sf::Vector2f position = START_POSITION;
  sf::Vector2f direction = sf::Vector2f(0, 0); // Координата х принимает одно из 3-х значений(-1; 0; 1). -1: Разворот влево. 1: Разворот вправо. 0: Не разворачивается
                                               // Кордината у принимет одно из 2-х значений(1, 0). 1: Увеличение скорости. 0: Скорость не изменяется.

  sf::Vector2f boostDirection; // Направление вектора ускорения
  float rotationSum = 0;

  sf::Transform transform; // Для разворота системы координат вершин коробля

public:
  void init();

  void update(float dt);

  void keyPressed(sf::Event event);

  void keyReleased(sf::Event event);
};