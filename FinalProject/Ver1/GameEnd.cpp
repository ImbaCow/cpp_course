#include "GameEnd.h"
#include "consts.h"
#include <string>

GameEnd::GameEnd()
{
    init();
}

void GameEnd::init()
{
    font.loadFromFile("./arial.ttf");
    gameResult = math.initText(font, "YOU WIN", TITLE_CHAR_SIZE, TITLE_TEXT_POS);
    menuText = math.initText(font, "MENU", CHAR_SIZE, MENU_POS);
    scoreText = math.initText(font, "YOUR SCORE: ", SCORE_CHAR_SIZE, SCORE_POS);

    menuShape = math.initRect(BUTTON_SIZE, MENU_POS, BUTTON_DEACTIVE_COLOR);

    backGround.setSize({WINDOW_WIDTH, WINDOW_HEIGHT});
    backGround.setFillColor(sf::Color(0, 0, 0, 100));
}

void GameEnd::checkGameResult(bool isWin, int score)
{
    std::string scoreString = "YOUR SCORE: ";
    scoreString += math.toString(score);
    scoreText.setString(scoreString);

    if (isWin)
        gameResult.setString("YOU WIN");
    else
        gameResult.setString("YOU DIED");
}

void GameEnd::pollEvents(sf::RenderWindow &window, unsigned &GameStatus)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            mousePosition = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
            if (math.isInRoundRect(mousePosition, menuShape.getPosition(), menuShape.getSize(), menuShape.getRotation()))
                menuShape.setFillColor(BUTTON_ACTIVE_COLOR);
            else
                menuShape.setFillColor(BUTTON_DEACTIVE_COLOR);
            break;
        case sf::Event::MouseButtonPressed:
            clickPosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
            if (math.isInRoundRect(clickPosition, menuShape.getPosition(), menuShape.getSize(), menuShape.getRotation()))
                GameStatus = 0;
            break;
        default:
            break;
        }
    }
}

void GameEnd::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(backGround);
    target.draw(menuShape);
    target.draw(menuText);
    target.draw(scoreText);
    target.draw(gameResult);
}
