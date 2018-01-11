#include "Bullets.h"
#include <cmath>
void Bullets::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (size_t i = 0; i < bullets.size(); ++i)
    {
        target.draw(bullets[i].shape);
    }
}

void Bullets::addBullet(unsigned affiliation, sf::Vector2f tankPosition, float rotation)
{
    Bullet null;

    sf::Vector2f bulletPosition = tankPosition + sf::Vector2f(BULLET_OFFSET * cos(rotation), BULLET_OFFSET * sin(rotation));

    null.affiliation = affiliation;
    null.direction = sf::Vector2f(cos(rotation), sin(rotation));
    null.shape.setRadius(BULLET_RADIUS);
    null.shape.setPosition(bulletPosition);

    switch (affiliation)
    {
    case 0: // Range enemy bullet
        null.shape.setFillColor(sf::Color::Black);
        break;
    case 1: // Hero bullet
        null.shape.setFillColor(sf::Color::Black);
        break;
    case 2: // Melee fire bullet
        null.fireDmg = FIRE_DMG;
        null.shape.setFillColor(sf::Color::Red);
        break;
    case 3: // Range boss bullet
        null.shape.setFillColor(sf::Color::Black);
        null.shape.setRadius(BOSS_BULLET_RADIUS);
        bulletPosition = tankPosition + sf::Vector2f(BOSS_BULLET_OFFSET * cos(rotation), BOSS_BULLET_OFFSET * sin(rotation));
        break;
    case 4: // Melee boss bullet
        null.fireDmg = BOSS_FIRE_DMG;
        null.shape.setFillColor(sf::Color::Red);
        null.shape.setRadius(BOSS_BULLET_RADIUS);
        bulletPosition = tankPosition + sf::Vector2f(BOSS_BULLET_OFFSET * cos(rotation), BOSS_BULLET_OFFSET * sin(rotation));
        break;
    default:
        break;
    }

    null.shape.setOrigin(null.shape.getRadius() / 2, null.shape.getRadius() / 2);
    null.position = bulletPosition;
    bullets.push_back(null);
}

void Bullets::updateBulletPos(float dt)
{
    for (size_t i = 0; i < bullets.size(); ++i)
    {
        bullets[i].position += bullets[i].direction * dt * BULLET_SPEED;
        bullets[i].shape.setPosition(bullets[i].position);
        if ((bullets[i].affiliation == 2) || (bullets[i].affiliation == 4))
        {
            bullets[i].fireLifeTime -= dt;
        }
    }
}

void Bullets::update(float dt)
{
    updateBulletPos(dt);
    eraseBullet();
}

bool isDead(Bullet bullet)
{
    return ((bullet.position.x >= WINDOW_WIDTH) && (bullet.direction.x > 0) ||
            (bullet.position.x < 0) && (bullet.direction.x < 0) ||
            (bullet.position.y >= WINDOW_HEIGHT) && (bullet.direction.y > 0) ||
            (bullet.position.y < 0) && (bullet.direction.y < 0)) ||
           (bullet.isDead) || (bullet.fireLifeTime <= 0);
}

void Bullets::eraseBullet()
{
    auto newEnd = std::remove_if(bullets.begin(), bullets.end(), isDead);
    bullets.erase(newEnd, bullets.end());
}