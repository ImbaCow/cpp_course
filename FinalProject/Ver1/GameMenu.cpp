#include "GameMenu.h"
#include "consts.h"

GameMenu::GameMenu()
{
    init();
}

void GameMenu::run(sf::RenderWindow &window, unsigned &GameStatus)
{
    pollEvents(window, GameStatus);
    redrawFrame(window);
}

void GameMenu::init()
{
    font.loadFromFile("./arial.ttf");
    playText = math.initText(font, "PLAY", CHAR_SIZE, PLAY_POS);
    playShape = math.initRect(BUTTON_SIZE, PLAY_POS, BUTTON_DEACTIVE_COLOR);

    texture.loadFromFile("./background.png");
    backSprite.setTexture(texture);
}

void GameMenu::pollEvents(sf::RenderWindow &window, unsigned &GameStatus)
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
            if (math.isInRoundRect(mousePosition, playShape.getPosition(), playShape.getSize(), playShape.getRotation()))
                playShape.setFillColor(BUTTON_ACTIVE_COLOR);
            else
                playShape.setFillColor(BUTTON_DEACTIVE_COLOR);
            break;
        case sf::Event::MouseButtonPressed:
            clickPosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
            if (math.isInRoundRect(clickPosition, playShape.getPosition(), playShape.getSize(), playShape.getRotation()))
                GameStatus = 3;
            break;
        default:
            break;
        }
    }
}

void GameMenu::redrawFrame(sf::RenderWindow &window)
{
    window.clear(sf::Color::White);
    window.draw(backSprite);
    window.draw(playShape);
    window.draw(playText);
    window.display();
}
