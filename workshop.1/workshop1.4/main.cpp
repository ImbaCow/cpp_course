#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>

struct Texture
// Объявление структуры, которая хранит:
{
    // Текстуру переменной
    sf::Texture texture;
    // Спрайт переменной
    sf::Sprite sprite;
    // Позицию переменной
    sf::Vector2f position = {400, 300};
};

void pollEvents(sf::RenderWindow &window, Texture &pointer)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            // Обработка события закрытия окна, и нажатия мыши
            window.close();
            break;
        case sf::Event::MouseButtonReleased:
            // Обновление позиции указки относительно точки нажатия кнопки мыши
            pointer.sprite.setPosition(event.mouseButton.x - 16, event.mouseButton.y - 16);
            pointer.position = {pointer.sprite.getPosition()};
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

void init(Texture &cat, Texture &pointer)
{
    // Полное объявление позиции и текстуры кота
    cat.sprite.setTexture(cat.texture);
    cat.sprite.setTextureRect(sf::IntRect(0, 0, 38, 35));
    cat.sprite.setPosition(cat.position);
    // Полное объявление позиции и текстуры указки
    pointer.sprite.setTexture(pointer.texture);
    pointer.sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
    pointer.sprite.setPosition(pointer.position);
}

void redrawFrame(sf::RenderWindow &window, Texture &cat, Texture &pointer)
{
    // Вывод кота и указки на экран
    window.clear();
    window.draw(cat.sprite);
    window.draw(pointer.sprite);
    window.display();
}

void update(Texture &cat, Texture &pointer, float dt)
{
    // Обновление позиции кота относительно указки при помощи счетчика и нормализации вектора
    const float catMoveSpeed = 100;
    const float pxPerFrame = catMoveSpeed * dt;
    sf::Vector2f delta = pointer.position - cat.position;
    sf::Vector2f direction = normalize(delta);
    cat.position += direction * std::min(pxPerFrame, vectorLenght(delta));

    // Разворот спрайта влево/вправо при движении кота влево/вправо и вывод его на экран
    if (delta.x < 0)
    {
        cat.sprite.setPosition(cat.position.x + 38, cat.position.y);
        cat.sprite.setScale(-1, 1);
    }
    else
    {
        cat.sprite.setPosition(cat.position);
        cat.sprite.setScale(1, 1);
    }
}

int main()
{
    // Инициализация окна
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "cat");

    // Инициализация счетчика
    sf::Clock clock;

    // Объявление текстур кота и указки
    Texture cat;
    Texture pointer;
    pointer.texture.loadFromFile("./red_pointer.png");
    cat.texture.loadFromFile("./cat.png");

    // Полное объявление позиции и текстуры кота и указки
    init(cat, pointer);

    // Объявление цикла, работающего каждый кадр
    while (window.isOpen())
    {
        // Обработка событий, обновление позиции указки
        pollEvents(window, pointer);
        // Обновление позиции кота относительно указки при помощи счетчика и нормализации вектора
        const float dt = clock.restart().asSeconds();
        update(cat, pointer, dt);
        // Вывод кота и указки на экран
        redrawFrame(window, cat, pointer);
    }
}
