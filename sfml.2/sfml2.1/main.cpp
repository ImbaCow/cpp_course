#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

int main()
{
     

    constexpr float BALL_SIZE = 40;
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::Vector2f speed = { 100.f, 80.f };

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Wave Moving Ball");
    sf::Clock clock; //Для dt
    sf::Clock totalClock; //Для time, т.к. dt постоянно обнуляет счетчик
    
    sf::CircleShape shape(BALL_SIZE);
    sf::Vector2f position = {10, 200};
    shape.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close(); 
            }
        }

        const float posX = shape.getPosition().x;
        position.x = posX; //Добавил posX для числового увеличения кординаты х, т.к. кордината у увеличивается аналитически
        const float dt = clock.restart().asSeconds();    
        const float time = totalClock.getElapsedTime().asSeconds();

        if ((position.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (speed.x > 0))
        {
            speed.x = -speed.x;
        }
        if ((position.x < 0) && (speed.x < 0))
        {
            speed.x = -speed.x;
        }

        const float x = speed.x * dt;
        const float y = speed.y * std::sin(time * M_PI);
        sf::Vector2f offset = { x, y };

        shape.setPosition(position + offset);

        window.clear();
        window.draw(shape);
        window.display();
    }
}