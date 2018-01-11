#include "GameLevel.h"

GameLevel::GameLevel()
{
    enemiesCount.reserve(LEVEL_COUNT);
    for (float i = 0; i < LEVEL_COUNT; ++i)
    {
        enemiesCount[i] = {i + 2, i + 1};
    }

    font.loadFromFile("./arial.ttf");
    levelText = math.initText(font, "LEVEL  ", CHAR_SIZE, LEVEL_TEXT_POS);
}

void GameLevel::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(levelText);
}

void GameLevel::checkLevelUp(float dt, unsigned &GameStatus, Boss &boss)
{
    timer += dt;

    if (currentLevel > LEVEL_COUNT)
    {
        if (timer >= LEVEL_UP_PAUSE)
        {
            GameStatus = 6;
            timer = 0;
            boss.initBoss();
        }
        else
            levelText.setString("BOSS");
    }
    else if (timer >= LEVEL_UP_PAUSE)
    {
        GameStatus = 1;
        timer = 0;
    }
    else 
    {
        std::string levelString = "LEVEL ";
        levelString += math.toString(currentLevel);
        levelText.setString(levelString);
    }
}