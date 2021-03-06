#include "Initials.h"

void Initials::init()
{
    font.loadFromFile("./arial.ttf");

    initialsBackground.setRadius(BALL_RADIUS);
    initialsBackground.setOrigin({BALL_RADIUS, BALL_RADIUS});
    initialsBackground.setPosition(position);
    initialsBackground.setFillColor(sf::Color(255, 165, 0));
    initialsBackground.setOutlineThickness(OUTLINE_SIZE);
    initialsBackground.setOutlineColor(sf::Color(70, 130, 180));

    initialsText.setFont(font);
    initialsText.setString(INITIALS_TEXT);
    initialsText.setCharacterSize(INITIALS_SIZE);
    textBox = initialsText.getGlobalBounds();
    initialsText.setOrigin({textBox.width / 2, textBox.height / 2});
    initialsText.setPosition(position);
    initialsText.setFillColor(sf::Color::Black);
}

void Initials::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(initialsBackground, states);
    target.draw(initialsText, states);
}

void Initials::updatePosition(float dt)
{
    checkWallCollision();
    speed.y += GRAVITY_ACCELERATION * dt;
    position += speed * dt;
    initialsText.setPosition(position);
    initialsBackground.setPosition(position);
}

void Initials::checkWallCollision()
{
    if ((position.x + backGroundSize >= WINDOW_WIDTH) && (speed.x > 0))
    {
        speed.x = -speed.x;
    }
    if ((position.x - backGroundSize < 0) && (speed.x < 0))
    {
        speed.x = -speed.x;
    }
    if ((position.y + backGroundSize >= WINDOW_HEIGHT) && (speed.y > 0))
    {
        speed.y = -speed.y;
    }
    if ((position.y - backGroundSize < 0) && (speed.y < 0))
    {
        speed.y = -speed.y;
    }
}