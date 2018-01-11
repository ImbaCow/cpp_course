#include <cmath>
#include "Enemies.h"

void Enemies::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (size_t i = 0; i < range.size(); ++i)
    {
        target.draw(range[i].body);
        target.draw(range[i].head);
        target.draw(range[i].fullHealth);
        target.draw(range[i].currentHealth);
    }

    for (size_t i = 0; i < melee.size(); ++i)
    {
        target.draw(melee[i].body);
        target.draw(melee[i].head);
        target.draw(melee[i].fullHealth);
        target.draw(melee[i].currentHealth);
    }
}

void Enemies::addRange(sf::Vector2f newTankPosition)
{
    Enemy null;
    texture.loadFromFile("./tank.png");
    null.body.setTexture(&texture);
    null.head.setTexture(&texture);
    null.head.setFillColor(sf::Color(178, 34, 34));
    null.body.setFillColor(sf::Color(80, 10, 10));

    null.head.setPointCount(11);
    null.head.setPoint(0, sf::Vector2f(-10, -8));
    null.head.setPoint(1, sf::Vector2f(-8, -10));
    null.head.setPoint(2, sf::Vector2f(6, -10));
    null.head.setPoint(3, sf::Vector2f(10, -3));
    null.head.setPoint(4, sf::Vector2f(40, -3));
    null.head.setPoint(5, sf::Vector2f(40, 3));
    null.head.setPoint(6, sf::Vector2f(10, 3));
    null.head.setPoint(7, sf::Vector2f(6, 10));
    null.head.setPoint(8, sf::Vector2f(-8, 10));
    null.head.setPoint(9, sf::Vector2f(-10, 8));
    null.head.setPoint(10, sf::Vector2f(-10, -8));

    initBody(null);
    initHealthBars(null);

    null.position = newTankPosition;
    null.shotCooldown -= math.random(0, MAX_SHOT_DELAY);
    null.changeMoveRadius = R_CHANGE_MOVE_RADIUS;
    null.healthPoints = RANGE_MAX_HEALTH;

    range.push_back(null);
}

void Enemies::addMelee(sf::Vector2f newTankPosition)
{
    Enemy null;

    texture.loadFromFile("./tank.png");
    null.body.setTexture(&texture);
    null.head.setTexture(&texture);
    null.head.setFillColor(sf::Color(250, 85, 9));
    null.body.setFillColor(sf::Color(210, 90, 34));

    null.head.setPointCount(11);
    null.head.setPoint(0, sf::Vector2f(-10, -8));
    null.head.setPoint(1, sf::Vector2f(-8, -10));
    null.head.setPoint(2, sf::Vector2f(6, -10));
    null.head.setPoint(3, sf::Vector2f(10, -3));
    null.head.setPoint(4, sf::Vector2f(40, -3));
    null.head.setPoint(5, sf::Vector2f(40, 3));
    null.head.setPoint(6, sf::Vector2f(10, 3));
    null.head.setPoint(7, sf::Vector2f(6, 10));
    null.head.setPoint(8, sf::Vector2f(-8, 10));
    null.head.setPoint(9, sf::Vector2f(-10, 8));
    null.head.setPoint(10, sf::Vector2f(-10, -8));

    initBody(null);
    initHealthBars(null);

    null.position = newTankPosition;
    null.shotCooldown -= math.random(0, MAX_SHOT_DELAY);
    null.changeMoveRadius = M_CHANGE_MOVE_RADIUS;
    null.healthPoints = MELEE_MAX_HEALTH;

    melee.push_back(null);
}

void Enemies::initBody(Enemy &enemy)
{
    enemy.body.setPointCount(7);
    enemy.body.setPoint(0, sf::Vector2f(-20, -15));
    enemy.body.setPoint(1, sf::Vector2f(20, -15));
    enemy.body.setPoint(2, sf::Vector2f(25, -10));
    enemy.body.setPoint(3, sf::Vector2f(25, 10));
    enemy.body.setPoint(4, sf::Vector2f(20, 15));
    enemy.body.setPoint(5, sf::Vector2f(-20, 15));
    enemy.body.setPoint(6, sf::Vector2f(-20, -15));
}

void Enemies::initHealthBars(Enemy &enemy)
{
    enemy.fullHealth.setSize(HEALTH_BAR_SIZE);
    enemy.fullHealth.setFillColor(sf::Color(255, 0, 0, 255));
    enemy.fullHealth.setOrigin(HEALTH_BAR_OFFSET);
    enemy.fullHealth.setOutlineThickness(2);
    enemy.fullHealth.setOutlineColor(sf::Color::Black);

    enemy.currentHealth.setSize(HEALTH_BAR_SIZE);
    enemy.currentHealth.setFillColor(sf::Color(0, 255, 0, 200));
    enemy.currentHealth.setOrigin(HEALTH_BAR_OFFSET);
}

void Enemies::updateHealthBar(Enemy &enemy, float maxHealthPoints)
{
    enemy.fullHealth.setPosition(enemy.position);
    enemy.currentHealth.setPosition(enemy.position);
    float healthBarLenght = HEALTH_BAR_SIZE.x / maxHealthPoints * enemy.healthPoints;
    enemy.currentHealth.setSize({healthBarLenght, HEALTH_BAR_SIZE.y});
}

void Enemies::update(float dt, sf::Vector2f heroPosition, sf::Vector2f heroDirection, Bullets &bullets)
{
    eraseDeadEnemy();

    for (size_t i = 0; i < range.size(); ++i)
    {
        checkWallCollision(range[i].position);
        bodyRotationUpdate(dt, heroPosition, range[i]);
        checkRangeCollusion(range[i], i);
        bodyUpdate(dt, heroPosition, range[i]);
        headUpdate(heroPosition, heroDirection, range[i]);
        updateHealthBar(range[i], RANGE_MAX_HEALTH);
    }

    for (size_t i = 0; i < melee.size(); ++i)
    {
        checkWallCollision(melee[i].position);
        bodyRotationUpdate(dt, heroPosition, melee[i]);
        checkMeleeCollusion(melee[i], i);
        bodyUpdate(dt, heroPosition, melee[i]);
        melee[i].head.setRotation(melee[i].body.getRotation());
        melee[i].head.setPosition(melee[i].position);
        updateHealthBar(melee[i], MELEE_MAX_HEALTH);
    }

    bulletShot(bullets, dt);
}

void Enemies::checkWallCollision(sf::Vector2f &position)
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

void Enemies::headUpdate(sf::Vector2f heroPosition, sf::Vector2f heroDirection, Enemy &enemy)
{
    sf::Vector2f delta = heroPosition - enemy.position + heroDirection * ENEMY_PREDICTION_LEVEL;
    float angle = atan2(delta.y, delta.x);
    enemy.head.setRotation(math.toDegrees(angle));
    enemy.head.setPosition(enemy.position);
}

void Enemies::bodyRotationUpdate(float dt, sf::Vector2f heroPosition, Enemy &enemy)
{
    sf::Vector2f delta = heroPosition - enemy.position;
    float angle = atan2(delta.y, delta.x);
    if (angle < 0)
    {
        angle += 2 * M_PI;
    }

    enemy.rotation = enemy.body.getRotation();
    float deltaAngle = math.toDegrees(angle) - enemy.rotation;

    checkRotation(enemy.rotateDirection, deltaAngle);
}

void Enemies::bodyUpdate(float dt, sf::Vector2f heroPosition, Enemy &enemy)
{
    sf::Vector2f delta = heroPosition - enemy.position;
    enemy.rotation += ENEMY_ROTAION_SPEED * dt * enemy.rotateDirection;
    sf::Vector2f moveDirection = sf::Vector2f(cos(math.toRadians(enemy.rotation)), sin(math.toRadians(enemy.rotation)));

    if (math.vectorLenght(delta) < enemy.changeMoveRadius)
    {
        moveDirection = -moveDirection;
    }

    enemy.position += moveDirection * ENEMY_TANK_SPEED * dt;
    enemy.body.setRotation(enemy.rotation);
    enemy.body.setPosition(enemy.position);
}

void Enemies::checkRotation(float &rotateDirection, float &deltaAngle)
{
    if (deltaAngle < 0)
    {
        if (deltaAngle < -180)
        {
            rotateDirection = 1;
        }
        else
        {
            rotateDirection = -1;
        }
    }
    else
    {
        if (deltaAngle > 180)
        {
            rotateDirection = -1;
        }
        else
        {
            rotateDirection = 1;
        }
    }
}

void Enemies::checkRangeCollusion(Enemy &enemy, size_t fi)
{
    for (size_t mi = 0; mi < melee.size(); ++mi)
    {
        sf::Vector2f deltaPos = enemy.position - melee[mi].position;
        if (math.vectorLenght(deltaPos) < COLLUSION_RADIUS)
        {
            enemy.rotateDirection = -enemy.rotateDirection;
        }
    }
    for (size_t si = fi + 1; si < range.size(); ++si)
    {
        sf::Vector2f deltaPos = enemy.position - range[si].position;
        if (math.vectorLenght(deltaPos) < COLLUSION_RADIUS)
        {
            enemy.rotateDirection = -enemy.rotateDirection;
        }
    }
}

void Enemies::checkMeleeCollusion(Enemy &enemy, size_t fi)
{
    for (size_t si = fi + 1; si < melee.size(); ++si)
    {
        sf::Vector2f deltaPos = enemy.position - melee[si].position;
        if (math.vectorLenght(deltaPos) < COLLUSION_RADIUS)
        {
            enemy.rotateDirection = -enemy.rotateDirection;
        }
    }
}

void Enemies::bulletShot(Bullets &bullets, float dt)
{
    for (size_t i = 0; i < range.size(); ++i)
    {
        if (range[i].shotCooldown > R_ENEMY_SHOT_COOLDOWN)
        {
            bullets.addBullet(0, range[i].position, math.toRadians(range[i].head.getRotation()));
            range[i].shotCooldown = 0;
        }
        range[i].shotCooldown += dt;
    }

    for (size_t i = 0; i < melee.size(); ++i)
    {
        if (melee[i].shotCooldown > M_ENEMY_SHOT_COOLDOWN)
        {
            for (unsigned bi = 0; bi < M_SHOT_COUNT; ++bi)
            {
                float angleStep = M_ENEMY_SHOT_ANGLE / M_SHOT_COUNT * bi;
                float nextAngle = melee[i].body.getRotation() - M_ENEMY_SHOT_ANGLE / 2 + angleStep;
                bullets.addBullet(2, melee[i].position, math.toRadians(nextAngle));
            }
            melee[i].shotCooldown = 0;
        }
        melee[i].shotCooldown += dt;
    }
}

bool isDead(Enemy enemy)
{
    return (enemy.healthPoints <= 0);
}

void Enemies::eraseDeadEnemy()
{
    auto rangeNewEnd = std::remove_if(range.begin(), range.end(), isDead);
    range.erase(rangeNewEnd, range.end());

    auto meleeNewEnd = std::remove_if(melee.begin(), melee.end(), isDead);
    melee.erase(meleeNewEnd, melee.end());
}
