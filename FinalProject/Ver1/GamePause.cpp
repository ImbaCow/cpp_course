#include "GamePause.h"
#include "consts.h"
#include <string>

GamePause::GamePause()
{
    init();
}

void GamePause::init()
{
    font.loadFromFile("./arial.ttf");
    menuText = math.initText(font, "MENU", CHAR_SIZE, MENU_POS);
    menuButton = math.initRect(BUTTON_SIZE, MENU_POS, BUTTON_DEACTIVE_COLOR);

    continueText = math.initText(font, "CONTINUE", CHAR_SIZE, CONTINUE_POS);
    continueButton = math.initRect(BUTTON_SIZE, CONTINUE_POS, BUTTON_DEACTIVE_COLOR);

    pauseText = math.initText(font, "PAUSE", TITLE_CHAR_SIZE, TITLE_TEXT_POS);

    backGround.setSize({WINDOW_WIDTH, WINDOW_HEIGHT});
    backGround.setFillColor(sf::Color(0, 0, 0, 100));
}

void GamePause::pollEvents(sf::RenderWindow &window, unsigned &GameStatus, unsigned nextGameStatus)
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
            if (math.isInRoundRect(mousePosition, menuButton.getPosition(), menuButton.getSize(), menuButton.getRotation()))
            {
                menuButton.setFillColor(BUTTON_ACTIVE_COLOR);
            }
            else if (math.isInRoundRect(mousePosition, continueButton.getPosition(), continueButton.getSize(), continueButton.getRotation()))
            {
                continueButton.setFillColor(BUTTON_ACTIVE_COLOR);
            }
            else
            {
                menuButton.setFillColor(BUTTON_DEACTIVE_COLOR);
                continueButton.setFillColor(BUTTON_DEACTIVE_COLOR);
            }
            break;
        case sf::Event::MouseButtonPressed:
            clickPosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
            if (math.isInRoundRect(clickPosition, menuButton.getPosition(), menuButton.getSize(), menuButton.getRotation()))
            {
                GameStatus = 0;
            }
            if (math.isInRoundRect(clickPosition, continueButton.getPosition(), continueButton.getSize(), continueButton.getRotation()))
            {
                GameStatus = nextGameStatus;
            }
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
            {
                GameStatus = nextGameStatus;
            }
            break;
        default:
            break;
        }
    }
}

void GamePause::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(backGround);
    target.draw(menuButton);
    target.draw(continueButton);
    target.draw(menuText);
    target.draw(continueText);
    target.draw(pauseText);
}
