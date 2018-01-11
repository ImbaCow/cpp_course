#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <string>

class Math
{
public:
  Math();

  float random(unsigned minValue, unsigned maxValue);

  bool isInRoundRect(sf::Vector2f pointerPos, sf::Vector2f boxPos, sf::Vector2f boxSize, float boxRotatation);

  float toDegrees(float radians);

  float toRadians(float degrees);

  float vectorLenght(sf::Vector2f vector);

  sf::Text initText(sf::Font &font, std::string textString, float charSize, sf::Vector2f textPos);

  sf::RectangleShape initRect(sf::Vector2f size, sf::Vector2f position, sf::Color rectColor);

  std::string toString(int i);

private:
  std::mt19937 generator;

  sf::Text text;
  sf::RectangleShape rect;
};