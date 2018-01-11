#include "Game.h"
#include "consts.h"

Game::Game()
{
    createWindow();
}

void Game::run()
{
    sf::Clock clock;

    sf::Event event;

    while (window.isOpen())
    {
        const float dt = clock.restart().asSeconds();
        switch (GameStatus)
        {
        case 0: // Main menu
            gameMenu.run(window, GameStatus);
            break;
        case 1: // Continue game
            gameRun.run(dt, window, GameStatus, enemiesCount);
            break;
        case 2: // End screen
            gameRun.end(window, GameStatus);
            break;
        case 3: // Game restart
            gameRun.restart(window, GameStatus, enemiesCount);
            break;
        case 4: // Pause game
            gameRun.pause(window, GameStatus);
            break;
        case 5: //New game level
            gameRun.levelUp(dt, window, GameStatus);
            break;
        case 6: // Level Boss
            gameRun.bossLevel(dt, window, GameStatus, enemiesCount);
            break;
        default:
            break;
        }
    }
}

void Game::createWindow()
{
    sf::VideoMode videoMode(WINDOW_WIDTH, WINDOW_HEIGHT);
    const std::string title = "BFW";
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(videoMode, title, sf::Style::Default, settings);
    window.setKeyRepeatEnabled(false);
}