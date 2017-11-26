#pragma once
#include "constants.h"

class initials : public sf::Drawable
{
  private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void checkWallCollision();

    sf::CircleShape initialsBackground;

    sf::Text initialsText;
    sf::Font font;
    sf::FloatRect textBox;
    const unsigned backGroundSize = BALL_RADIUS + OUTLINE_SIZE;
    const unsigned charSize = INITIALS_SIZE;

    sf::Vector2f speed = START_SPEED;
    sf::Vector2f position = START_POSITION;

  public:
    void init();

    void updatePosition(float dt);
};