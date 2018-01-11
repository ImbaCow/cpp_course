#include "HeroTank.h"
#include <cmath>
#include <algorithm>

void HeroTank::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(body);
    target.draw(head);
    target.draw(fullHealth);
    target.draw(currentHealth);
    target.draw(cdBar);
}

void HeroTank::checkWallCollision()
{
    if (position.x > WINDOW_WIDTH)
    {
        position.x -= 1;
    }
    if (position.x < 0)
    {
        position.x += 1;
    }
    if (position.y > WINDOW_HEIGHT)
    {
        position.y -= 1;
    }
    if (position.y < 0)
    {
        position.y += 1;
    }
}

void HeroTank::initHero()
{
    blastCD = HERO_BLAST_COOLDOWN;
    isShooting = 0;
    rotation = 0;
    shotCD = 0;
    position = START_POSITION;
    bodyDirection = sf::Vector2f(0, 0);
    healthPoints = MAX_HEALTH;

    texture.loadFromFile("./tank.png");
    body.setTexture(&texture);
    head.setTexture(&texture);
    head.setFillColor(sf::Color(25, 126, 16));
    body.setFillColor(sf::Color(10, 64, 5));

    head.setPointCount(11);
    head.setPoint(0, sf::Vector2f(-10, -8));
    head.setPoint(1, sf::Vector2f(-8, -10));
    head.setPoint(2, sf::Vector2f(6, -10));
    head.setPoint(3, sf::Vector2f(10, -3));
    head.setPoint(4, sf::Vector2f(40, -3));
    head.setPoint(5, sf::Vector2f(40, 3));
    head.setPoint(6, sf::Vector2f(10, 3));
    head.setPoint(7, sf::Vector2f(6, 10));
    head.setPoint(8, sf::Vector2f(-8, 10));
    head.setPoint(9, sf::Vector2f(-10, 8));
    head.setPoint(10, sf::Vector2f(-10, -8));

    body.setPointCount(7);
    body.setPoint(0, sf::Vector2f(-20, -15));
    body.setPoint(1, sf::Vector2f(20, -15));
    body.setPoint(2, sf::Vector2f(25, -10));
    body.setPoint(3, sf::Vector2f(25, 10));
    body.setPoint(4, sf::Vector2f(20, 15));
    body.setPoint(5, sf::Vector2f(-20, 15));
    body.setPoint(6, sf::Vector2f(-20, -15));

    initHealthBars();
}

void HeroTank::initHealthBars()
{
    fullHealth.setSize(HEALTH_BAR_SIZE);
    fullHealth.setFillColor(sf::Color(255, 0, 0, 255));
    fullHealth.setOrigin(HEALTH_BAR_OFFSET);
    fullHealth.setOutlineThickness(2);
    fullHealth.setOutlineColor(sf::Color::Black);

    currentHealth.setSize(HEALTH_BAR_SIZE);
    currentHealth.setFillColor(sf::Color(0, 255, 0, 200));
    currentHealth.setOrigin(HEALTH_BAR_OFFSET);

    cdBar.setFillColor(sf::Color(0, 0, 255, 200));
    sf::Vector2f cdBarOffset = {HEALTH_BAR_OFFSET.x, HEALTH_BAR_OFFSET.y + HEALTH_BAR_SIZE.y + 2};
    cdBar.setOrigin(cdBarOffset);
}

void HeroTank::updateBars()
{
    fullHealth.setPosition(position);
    currentHealth.setPosition(position);
    cdBar.setPosition(position);

    float barLenght = HEALTH_BAR_SIZE.x / MAX_HEALTH * healthPoints;
    currentHealth.setSize({barLenght, HEALTH_BAR_SIZE.y});

    if (blastCD < HERO_BLAST_COOLDOWN)
    {
        barLenght = HEALTH_BAR_SIZE.x * (1 - 1 / HERO_BLAST_COOLDOWN * blastCD);
        cdBar.setSize({barLenght, HEALTH_BAR_SIZE.y});
    }
}

void HeroTank::update(float dt, Bullets &bullets)
{
    bulletShot(bullets);
    checkWallCollision();

    updateBars();
    shotCD += dt;
    blastCD += dt;

    headUpdate(dt);
    bodyUpdate(dt);
}

void HeroTank::headUpdate(float dt)
{
    sf::Vector2f delta = mousePosition - position;
    float angle = atan2(delta.y, delta.x);
    head.setRotation(math.toDegrees(angle));
    head.setPosition(position);
}

void HeroTank::bulletShot(Bullets &bullets)
{
    if ((shotCD * isShooting) > SHOT_COOLDOWN)
    {
        bullets.addBullet(1, position, math.toRadians(head.getRotation()));
        shotCD = 0;
    }
}

void HeroTank::bodyUpdate(float dt)
{
    speedDirection = sf::Vector2f(cos(math.toRadians(rotation)), sin(math.toRadians(rotation)));
    rotation += ROTAION_SPEED * dt * bodyDirection.x;
    body.setRotation(rotation);
    position += speedDirection * TANK_SPEED * dt * bodyDirection.y;
    body.setPosition(position);
}

void HeroTank::keyPressed(sf::Event event, Bullets &bullets)
{
    switch (event.key.code)
    {
    case sf::Keyboard::Left:
        bodyDirection.x = -1;
        break;
    case sf::Keyboard::Right:
        bodyDirection.x = 1;
        break;
    case sf::Keyboard::Up:
        bodyDirection.y = 1;
        break;
    case sf::Keyboard::Down:
        bodyDirection.y = -1;
        break;
    case sf::Keyboard::RControl:
        blastShot(bullets);
        break;
    default:
        break;
    }
}

void HeroTank::keyReleased(sf::Event event)
{
    switch (event.key.code)
    {
    case sf::Keyboard::Left:
        bodyDirection.x = 0;
        break;
    case sf::Keyboard::Right:
        bodyDirection.x = 0;
        break;
    case sf::Keyboard::Up:
        bodyDirection.y = 0;
        break;
    case sf::Keyboard::Down:
        bodyDirection.y = 0;
        break;
    default:
        break;
    }
}

void HeroTank::blastShot(Bullets &bullets)
{
    if (blastCD >= HERO_BLAST_COOLDOWN)
    {
        for (unsigned bi = 0; bi < (HERO_BLAST_COUNT * 3); ++bi)
        {
            float angleStep = 360 / HERO_BLAST_COUNT * bi;
            float nextAngle = body.getRotation() + angleStep;
            bullets.addBullet(1, position, math.toRadians(nextAngle));
        }
        blastCD = 0;
    }
}