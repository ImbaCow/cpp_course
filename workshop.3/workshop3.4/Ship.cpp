#include "Ship.h"
#include <cmath>

void Ship::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(ship, 5, sf::LineStrip);
    if (direction.y > 0)
    {
        target.draw(shipBoost, 5, sf::LineStrip);
    }
}

void Ship::init()
{
    for (size_t i = 0; i < 5; ++i)
    {
        shipBoost[i].color = sf::Color::White;
        ship[i].color = sf::Color::White;
    }
    updatePosition();
}

void Ship::updatePosition()
{
    shipBoost[0].position = position + transform.transformPoint(sf::Vector2f(-55, 0));
    shipBoost[1].position = position + transform.transformPoint(sf::Vector2f(-20, -20));
    shipBoost[2].position = position + transform.transformPoint(sf::Vector2f(-10, 0));
    shipBoost[3].position = position + transform.transformPoint(sf::Vector2f(-20, 20));
    shipBoost[4].position = position + transform.transformPoint(sf::Vector2f(-55, 0));

    ship[0].position = position + transform.transformPoint(sf::Vector2f(-10, 0));
    ship[1].position = position + transform.transformPoint(sf::Vector2f(-30, 40));
    ship[2].position = position + transform.transformPoint(sf::Vector2f(50, 0));
    ship[3].position = position + transform.transformPoint(sf::Vector2f(-30, -40));
    ship[4].position = position + transform.transformPoint(sf::Vector2f(-10, 0));
}

void Ship::checkWallCollision()
{
    if ((position.x >= WINDOW_WIDTH) && (speed.x > 0))
    {
        position.x = 0;
    }
    if ((position.x < 0) && (speed.x < 0))
    {
        position.x = WINDOW_WIDTH;
    }
    if ((position.y >= WINDOW_HEIGHT) && (speed.y > 0))
    {
        position.y = 0;
    }
    if ((position.y < 0) && (speed.y < 0))
    {
        position.y = WINDOW_HEIGHT;
    }
}

void Ship::update(float dt)
{
    checkWallCollision();

    rotation = ROTAION_SPEED * dt * direction.x;
    rotationSum += rotation;

    boostDirection = sf::Vector2f(cos(rotationSum * M_PI / 180), sin(rotationSum * M_PI / 180));
    speed += direction.y * BOOST_ACCELERATION * boostDirection;

    position += speed * dt;
    transform.rotate(rotation);
    updatePosition();
}

void Ship::keyPressed(sf::Event event)
{
    switch (event.key.code)
    {
    case sf::Keyboard::Left:
        direction.x -= 1;
        break;
    case sf::Keyboard::Right:
        direction.x += 1;
        break;
    case sf::Keyboard::Up:
        direction.y += 1;
        break;
    default:
        break;
    }
}

void Ship::keyReleased(sf::Event event)
{
    switch (event.key.code)
    {
    case sf::Keyboard::Left:
        direction.x += 1;
        break;
    case sf::Keyboard::Right:
        direction.x -= 1;
        break;
    case sf::Keyboard::Up:
        direction.y -= 1;
        break;
    default:
        break;
    }
}