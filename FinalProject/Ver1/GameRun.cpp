#include "GameRun.h"
#include "consts.h"

GameRun::GameRun()
{
    texture.loadFromFile("./background.png");
    sprite.setTexture(texture);
}

void GameRun::run(float dt, sf::RenderWindow &window, unsigned &GameStatus, sf::Vector2f &enemiesCount)
{
    prevGameStatus = GameStatus;

    pollEvents(window, GameStatus);
    initEnemies(dt, enemiesCount);
    checkHit();
    update(dt);
    checkWin(GameStatus, enemiesCount);

    redrawFrame(window);
    window.display();
}

void GameRun::levelUp(float dt, sf::RenderWindow &window, unsigned &GameStatus)
{
    prevGameStatus = GameStatus;

    pollEvents(window, GameStatus);
    checkHit();
    update(dt);
    gameLevel.checkLevelUp(dt, GameStatus, boss);

    redrawFrame(window);
    window.draw(gameLevel);
    window.display();
}

void GameRun::restart(sf::RenderWindow &window, unsigned &GameStatus, sf::Vector2f &enemiesCount)
{
    score = 0;
    enemies.melee.clear();
    enemies.range.clear();
    bullets.bullets.clear();

    heroTank.initHero();

    boss.body.setPointCount(0);
    boss.head.setPointCount(0);
    boss.healthPoints = 0;
    boss.currentHealth.setSize({0, 0});
    boss.fullHealth.setSize({0, 0});

    enemiesCount = {0, 0};
    GameStatus = 5;

    if (0 < LEVEL_COUNT)
    {
        enemiesCount = gameLevel.enemiesCount[0];
    }
    gameLevel.currentLevel = 1;
}

void GameRun::end(sf::RenderWindow &window, unsigned &GameStatus)
{
    gameEnd.checkGameResult(isWin, (int)score);
    gameEnd.pollEvents(window, GameStatus);

    redrawFrame(window);
    window.draw(gameEnd);
    window.display();
}

void GameRun::pause(sf::RenderWindow &window, unsigned &GameStatus)
{
    gamePause.pollEvents(window, GameStatus, prevGameStatus);

    redrawFrame(window);
    window.draw(boss);
    window.draw(gameLevel);
    window.draw(gamePause);
    window.display();
}

void GameRun::bossLevel(float dt, sf::RenderWindow &window, unsigned &GameStatus, sf::Vector2f &enemiesCount)
{
    prevGameStatus = GameStatus;
    sf::Vector2f predictionDirection = heroTank.speedDirection * heroTank.bodyDirection.y;

    pollEvents(window, GameStatus);
    checkHit();
    update(dt);
    boss.update(dt, heroTank.position, predictionDirection, bullets, enemies);
    checkWin(GameStatus, enemiesCount);

    redrawFrame(window);
    window.display();
}

void GameRun::pollEvents(sf::RenderWindow &window, unsigned &GameStatus)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
                GameStatus = 4;
            else
                heroTank.keyPressed(event, bullets);
            break;
        case sf::Event::KeyReleased:
            heroTank.keyReleased(event);
            break;
        case sf::Event::MouseMoved:
            heroTank.mousePosition = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
            break;
        case sf::Event::MouseButtonPressed:
            heroTank.isShooting = 1;
            break;
        case sf::Event::MouseButtonReleased:
            heroTank.isShooting = 0;
            break;
        default:
            break;
        }
    }
}

void GameRun::initEnemies(float dt, sf::Vector2f &enemiesCount)
{
    enemies.spawnTime += dt;
    sf::Vector2f newTankPosition = {math.random(0, WINDOW_WIDTH), math.random(0, WINDOW_HEIGHT)};
    if ((enemies.spawnTime >= SPAWN_COOLDOWN) && (0 < enemiesCount.x))
    {
        enemies.addMelee(newTankPosition);
        enemiesCount.x -= 1;
        enemies.spawnTime = 0;
    }
    else if ((enemies.spawnTime >= SPAWN_COOLDOWN) && (0 < enemiesCount.y))
    {
        enemies.addRange(newTankPosition);
        enemiesCount.y -= 1;
        enemies.spawnTime = 0;
    }
}

void GameRun::update(float dt)
{
    heroTank.update(dt, bullets);
    sf::Vector2f predictionDirection = heroTank.speedDirection * heroTank.bodyDirection.y;
    enemies.update(dt, heroTank.position, predictionDirection, bullets);
    bullets.update(dt);
}

void GameRun::checkWin(unsigned &GameStatus, sf::Vector2f &enemiesCount)
{
    if (heroTank.healthPoints <= 0)
    {
        isWin = 0;
        GameStatus = 2;
    }
    else if ((enemies.range.size() == 0) && (enemies.melee.size() == 0) && (enemiesCount == sf::Vector2f(0, 0)) && (boss.healthPoints <= 0))
    {
        if (gameLevel.currentLevel <= LEVEL_COUNT)
        {
            if (gameLevel.currentLevel < LEVEL_COUNT)
                enemiesCount = gameLevel.enemiesCount[gameLevel.currentLevel];
            gameLevel.currentLevel += 1;
            GameStatus = 5;
        }
        else
        {
            float scoreMp = heroTank.healthPoints / MAX_HEALTH * 10;
            isWin = 1;
            score *= scoreMp;
            GameStatus = 2;
        }
    }
}

void GameRun::checkHit()
{
    for (size_t bi = 0; bi < bullets.bullets.size(); ++bi)
    {
        switch (bullets.bullets[bi].affiliation)
        {
        case 0:
            if (math.isInRoundRect(bullets.bullets[bi].position, heroTank.position, HIT_BOX_SIZE, heroTank.body.getRotation()))
            {
                bullets.bullets[bi].isDead = 1;
                heroTank.healthPoints -= BULLET_DMG;
            }
            break;
        case 1:
            for (size_t ei = 0; ei < enemies.range.size(); ++ei)
            {
                if (math.isInRoundRect(bullets.bullets[bi].position, enemies.range[ei].position, HIT_BOX_SIZE, enemies.range[ei].body.getRotation()))
                {
                    bullets.bullets[bi].isDead = 1;
                    enemies.range[ei].healthPoints -= HERO_BULLET_DMG;
                    score += SCORE_PER_RANGE_DMG;
                }
            }
            for (size_t ei = 0; ei < enemies.melee.size(); ++ei)
            {
                if (math.isInRoundRect(bullets.bullets[bi].position, enemies.melee[ei].position, HIT_BOX_SIZE, enemies.melee[ei].body.getRotation()))
                {
                    bullets.bullets[bi].isDead = 1;
                    enemies.melee[ei].healthPoints -= HERO_BULLET_DMG;
                    score += SCORE_PER_MELEE_DMG;
                }
            }
            if ((prevGameStatus == 6) && (math.isInRoundRect(bullets.bullets[bi].position, boss.position, BOSS_HIT_BOX_SIZE, boss.body.getRotation())))
            {
                bullets.bullets[bi].isDead = 1;
                boss.healthPoints -= HERO_BULLET_DMG;
                score += SCORE_PER_BOSS_DMG;
            }
            break;
        case 2:
            if (math.isInRoundRect(bullets.bullets[bi].position, heroTank.position, HIT_BOX_SIZE, heroTank.body.getRotation()))
            {
                heroTank.healthPoints -= bullets.bullets[bi].fireDmg;
                bullets.bullets[bi].fireDmg = 0;
            }
            break;
        case 3:
            if (math.isInRoundRect(bullets.bullets[bi].position, heroTank.position, HIT_BOX_SIZE, heroTank.body.getRotation()))
            {
                bullets.bullets[bi].isDead = 1;
                heroTank.healthPoints -= BOSS_BULLET_DMG;
            }
            break;
        case 4:
            if (math.isInRoundRect(bullets.bullets[bi].position, heroTank.position, HIT_BOX_SIZE, heroTank.body.getRotation()))
            {
                heroTank.healthPoints -= bullets.bullets[bi].fireDmg;
                bullets.bullets[bi].fireDmg = 0;
            }
            break;
        default:
            break;
        }
    }
}

void GameRun::redrawFrame(sf::RenderWindow &window)
{
    window.clear(sf::Color::White);
    window.draw(sprite);
    window.draw(bullets);
    window.draw(heroTank);
    window.draw(enemies);
    window.draw(boss);
}