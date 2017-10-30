#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>

float toDegrees(float radians)
{
    // Перевод радиан в градусы
    return float(double(radians) * 180.0 / M_PI);
}

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &pointer)
{
    // Вывод стрелки на экран
    window.clear(sf::Color(255, 255, 255));
    window.draw(pointer);
    window.display();
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition)
{
    // Обработка события закрытия окна и передвижения мыши
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            // Обновление вектора позиции мыши относительно ее перемещения
            mousePosition = {float(event.mouseMove.x), float(event.mouseMove.y)};
            break;
        default:
            break;
        }
    }
}

float vectorLenght(sf::Vector2f &argument)
{
    // Расчет длины вектора
    return {
        pow((pow(argument.x, 2.0) + pow(argument.y, 2.0)), 0.5)};
}

sf::Vector2f normalize(sf::Vector2f &vector)
{
    // Нормализация вектора при помощи длины вектора
    if (vectorLenght(vector) == 0)
    {
        return {
            0,
            0};
    }
    else
    {
        return {
            vector.x / vectorLenght(vector),
            vector.y / vectorLenght(vector)};
    }
}

void update(sf::Vector2f &mousePosition, sf::ConvexShape &pointer, float dt)
{
    // Изменение угла поворота в сторону мыши с ограничением скорости поворота при помощи счетчика
    const float pointerRotationSpeed = 90;
    const float pointerMoveSpeed = 100;
    sf::Vector2f delta = mousePosition - pointer.getPosition();
    float angle = atan2(delta.y, delta.x);
    if (angle < 0)
    {
        angle += 2 * M_PI;
    }
    const float pointerRotation = pointer.getRotation();
    const float mouseRotation = toDegrees(angle);
    const float maxRotation = pointerRotationSpeed * dt;

    // Поворот стрелки в сторону мыши с ограничением сорости
    float nextRotation = std::min(std::abs(mouseRotation - maxRotation), maxRotation);
    if (mouseRotation < pointerRotation)
    {
        if ((mouseRotation + 180) < pointerRotation)
        {
            pointer.setRotation(pointerRotation + nextRotation);
        }
        else
        {
            pointer.setRotation(pointerRotation - nextRotation);
        }
    }
    else
    {
        if ((mouseRotation - 180) > pointerRotation)
        {
            pointer.setRotation(pointerRotation - nextRotation);
        }
        else
        {
            pointer.setRotation(pointerRotation + nextRotation);
        }
    }

    // Обновление позиции стрелки относительно мыши при помощи счетчика и нормализации вектора
    const float pxPerFrame = pointerMoveSpeed * dt;
    sf::Vector2f direction = normalize(delta);
    pointer.setPosition(pointer.getPosition() + direction * pxPerFrame);
}

void init(sf::ConvexShape &pointer)
{
    // Инициализация цвета стрелки
    pointer.setFillColor(sf::Color(255, 255, 0));

    // Инициализация позиции стрелки
    pointer.setPosition(400, 300);

    // Инициализация формы стрелки
    pointer.setPointCount(7);
    pointer.setPoint(0, {0, -100});
    pointer.setPoint(1, {100, 0});
    pointer.setPoint(2, {0, 100});
    pointer.setPoint(3, {0, 50});
    pointer.setPoint(4, {-100, 50});
    pointer.setPoint(5, {-100, -50});
    pointer.setPoint(6, {0, -50});
    pointer.setOutlineThickness(3);
    pointer.setOutlineColor(sf::Color(0, 0, 0));
}

int main()
{
    // Инициализация окна
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Pointer2.0",
        sf::Style::Default, settings);

    // Инициализация счетчика
    sf::Clock clock;

    //Объявление стрелки и вектор позиции мыши
    sf::ConvexShape pointer;
    sf::Vector2f mousePosition = {400, 300};

    // Инициализация позиции, цвета и формы стрелки
    init(pointer);

    // Объявление цикла, работающего каждый кадр
    while (window.isOpen())
    {
        // Обработка событий и обновление вектора позиции мыши
        pollEvents(window, mousePosition);
        // Обновление позиции и поворот стрелки относительно мыши при помощи счетчика и нормализации вектора
        const float dt = clock.restart().asSeconds();
        update(mousePosition, pointer, dt);
        // Вывод стрелки и указки на экран
        redrawFrame(window, pointer);
    }
}