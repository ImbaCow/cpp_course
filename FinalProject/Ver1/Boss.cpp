#include "Boss.h"
#include <cmath>
#include <math.h>
#include <algorithm>

void Boss::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(body);
    target.draw(head);
    target.draw(fullHealth);
    target.draw(currentHealth);
}

void Boss::initBoss()
{
    bodyDirection = sf::Vector2f(0, 0);
    BossStage = 1;
    rotation = 0;

    spawnCD = BOSS_SPAWN_CD;
    shotCD = 0;
    fireCD = 0;
    blastCD = 0;

    position = BOSS_INIT_POS;
    healthPoints = BOSS_MAX_HEALTH;

    texture.loadFromFile("./tank.png");
    body.setTexture(&texture);
    head.setTexture(&texture);
    head.setFillColor(sf::Color(25, 126, 16));
    body.setFillColor(sf::Color(10, 64, 5));

    head.setPointCount(11);
    head.setPoint(0, sf::Vector2f(-20, -16));
    head.setPoint(1, sf::Vector2f(-16, -20));
    head.setPoint(2, sf::Vector2f(12, -20));
    head.setPoint(3, sf::Vector2f(20, -6));
    head.setPoint(4, sf::Vector2f(80, -6));
    head.setPoint(5, sf::Vector2f(80, 6));
    head.setPoint(6, sf::Vector2f(20, 6));
    head.setPoint(7, sf::Vector2f(12, 20));
    head.setPoint(8, sf::Vector2f(-16, 20));
    head.setPoint(9, sf::Vector2f(-20, 16));
    head.setPoint(10, sf::Vector2f(-20, -16));

    body.setPointCount(7);
    body.setPoint(0, sf::Vector2f(-40, -30));
    body.setPoint(1, sf::Vector2f(40, -30));
    body.setPoint(2, sf::Vector2f(50, -20));
    body.setPoint(3, sf::Vector2f(50, 20));
    body.setPoint(4, sf::Vector2f(40, 30));
    body.setPoint(5, sf::Vector2f(-40, 30));
    body.setPoint(6, sf::Vector2f(-40, -30));

    head.setPosition(position);
    body.setPosition(position);
    initHealthBars();
}

void Boss::initHealthBars()
{
    fullHealth.setSize(BOSS_HEALTH_BAR_SIZE);
    fullHealth.setFillColor(sf::Color(255, 0, 0, 255));
    fullHealth.setOutlineThickness(5);
    fullHealth.setOutlineColor(sf::Color::Black);
    fullHealth.setPosition(BOSS_HEALTH_BAR_POS);

    currentHealth.setSize(BOSS_HEALTH_BAR_SIZE);
    currentHealth.setFillColor(sf::Color(0, 255, 0, 200));
    currentHealth.setPosition(BOSS_HEALTH_BAR_POS);
}

void Boss::update(float dt, sf::Vector2f heroPosition, sf::Vector2f heroDirection, Bullets &bullets, Enemies &enemies)
{
    checkStage(enemies);
    switch (BossStage)
    {
    case 0:
        endScene(dt);
        break;
    case 1:
        stageOneUpdate(dt, heroPosition, heroDirection, bullets);
        break;
    case 2:
        stageTwoUpdate(dt, heroPosition, heroDirection, bullets, enemies);
        break;
    case 3:
        stageThreeUpdate(dt, heroPosition, heroDirection, bullets);
        break;
    default:
        break;
    }
}

void Boss::stageOneUpdate(float dt, sf::Vector2f heroPosition, sf::Vector2f heroDirection, Bullets &bullets)
{
    float healthBarLenght = BOSS_HEALTH_BAR_SIZE.x / BOSS_MAX_HEALTH * healthPoints;
    currentHealth.setSize({healthBarLenght, BOSS_HEALTH_BAR_SIZE.y});
    bodyRotationUpdate(dt, heroPosition);
    bodyUpdate(dt, heroPosition, B_CHANGE_MOVE_RADIUS_1);
    headUpdate(heroPosition, heroDirection);
    checkWallCollision();

    bulletShot(bullets);
    shotCD += dt;
}

void Boss::stageTwoUpdate(float dt, sf::Vector2f heroPosition, sf::Vector2f heroDirection, Bullets &bullets, Enemies &enemies)
{
    float healthBarLenght = BOSS_HEALTH_BAR_SIZE.x / BOSS_MAX_HEALTH * healthPoints;
    currentHealth.setSize({healthBarLenght, BOSS_HEALTH_BAR_SIZE.y});

    bodyRotationUpdate(dt, heroPosition);
    bodyUpdate(dt, heroPosition, B_CHANGE_MOVE_RADIUS_2);
    headUpdate(heroPosition, heroDirection);
    checkWallCollision();
    spawnMinions(enemies, dt);

    bulletShot(bullets);
    shotCD += dt;
}

void Boss::stageThreeUpdate(float dt, sf::Vector2f heroPosition, sf::Vector2f heroDirection, Bullets &bullets)
{
    float healthBarLenght = BOSS_HEALTH_BAR_SIZE.x / BOSS_MAX_HEALTH * healthPoints;
    currentHealth.setSize({healthBarLenght, BOSS_HEALTH_BAR_SIZE.y});

    bodyRotationUpdate(dt, heroPosition);
    bodyUpdate(dt, heroPosition, M_CHANGE_MOVE_RADIUS);
    head.setRotation(body.getRotation());
    head.setPosition(position);
    checkWallCollision();

    fireShot(bullets);
    blastShot(bullets);
    fireCD += dt;
    blastCD += dt;
}

void Boss::endScene(float dt)
{
    float healthBarLenght = 0;
    currentHealth.setSize({healthBarLenght, BOSS_HEALTH_BAR_SIZE.y});

    if (spawnCD >= LEVEL_UP_PAUSE)
    {
        healthPoints = 0;
    }
    spawnCD += dt;
}
void Boss::checkStage(Enemies &enemies)
{
    float percentHealth = healthPoints / BOSS_MAX_HEALTH * 100;

    if ((percentHealth <= 100) && (percentHealth > 80))
    {
        BossStage = 1;
    }
    else if ((percentHealth <= 80) && (percentHealth > 30))
    {
        BossStage = 2;
    }
    else if ((percentHealth <= 30) && (percentHealth > 1))
    {
        BossStage = 3;
        enemies.range.clear();
        enemies.melee.clear();
        spawnCD = 0;
    }
    else if (percentHealth <= 1)
    {
        healthPoints = BOSS_MAX_HEALTH / 100;
        BossStage = 0;
    }
}

void Boss::spawnMinions(Enemies &enemies, float dt)
{
    if (spawnCD >= BOSS_SPAWN_CD)
    {
        enemies.addRange(position);
        enemies.addMelee(position);
        spawnCD = 0;
    }
    else
        spawnCD += dt;
}

void Boss::checkWallCollision()
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

void Boss::bulletShot(Bullets &bullets)
{
    if (shotCD > BOSS_SHOT_COOLDOWN)
    {
        bullets.addBullet(3, position, math.toRadians(head.getRotation()));
        shotCD = 0;
    }
}

void Boss::fireShot(Bullets &bullets)
{
    if (fireCD > M_ENEMY_SHOT_COOLDOWN)
    {
        for (unsigned bi = 0; bi < M_SHOT_COUNT; ++bi)
        {
            float angleStep = M_ENEMY_SHOT_ANGLE / M_SHOT_COUNT * bi;
            float nextAngle = body.getRotation() - M_ENEMY_SHOT_ANGLE / 2 + angleStep;
            bullets.addBullet(4, position, math.toRadians(nextAngle));
        }
        fireCD = 0;
    }
}

void Boss::blastShot(Bullets &bullets)
{
    if (blastCD > BOSS_SHOT_COOLDOWN)
    {
        for (unsigned bi = 0; bi < BOSS_BLAST_COUNT; ++bi)
        {
            float angleStep = 360 / BOSS_BLAST_COUNT * bi;
            float nextAngle = body.getRotation() + angleStep;
            bullets.addBullet(3, position, math.toRadians(nextAngle));
        }
        blastCD = 0;
    }
}

void Boss::headUpdate(sf::Vector2f heroPosition, sf::Vector2f heroDirection)
{
    sf::Vector2f prediction = heroPosition - position;
    prediction += heroDirection * TANK_SPEED * math.vectorLenght(prediction) / BULLET_SPEED * 2.f / 3.f;
    float angle = atan2(prediction.y, prediction.x);
    head.setRotation(math.toDegrees(angle));
    head.setPosition(position);
}

void Boss::bodyRotationUpdate(float dt, sf::Vector2f heroPosition)
{
    sf::Vector2f delta = heroPosition - position;
    float angle = atan2(delta.y, delta.x);
    if (angle < 0)
    {
        angle += 2 * M_PI;
    }

    rotation = body.getRotation();
    float deltaAngle = math.toDegrees(angle) - rotation;

    checkRotation(rotateDirection, deltaAngle);
}

void Boss::bodyUpdate(float dt, sf::Vector2f heroPosition, float changeRadius)
{
    sf::Vector2f delta = heroPosition - position;
    rotation += BOSS_ROTAION_SPEED * dt * rotateDirection;
    sf::Vector2f moveDirection = sf::Vector2f(cos(math.toRadians(rotation)), sin(math.toRadians(rotation)));

    if (hypot(delta.x, delta.y) < changeRadius)
    {
        moveDirection = -moveDirection;
    }

    position += moveDirection * BOSS_TANK_SPEED * dt;
    body.setRotation(rotation);
    body.setPosition(position);
}

void Boss::checkRotation(float &rotateDirection, float &deltaAngle)
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