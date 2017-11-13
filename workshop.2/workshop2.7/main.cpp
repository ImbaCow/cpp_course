#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <random>
#include <ctime>

static const float BALL_SIZE = 40;
static const unsigned WINDOW_WIDTH = 800;
static const unsigned WINDOW_HEIGHT = 600;
static const unsigned INTERACTION_COUNT = 10;

struct Color
{
    uint8_t colors[3];
};
// Структура для заполнения массива с шарами
struct Ball
{
    sf::CircleShape shape;
    sf::Vector2f speed;
    float deathTimer = 10;
};

// Для случайного числа
struct PRNG
{
    std::mt19937 engine;
};

// Для случайного числа
void initGenerator(PRNG &generator)
{
    const unsigned seed = unsigned(std::time(nullptr));
    generator.engine.seed(seed);
}

// Для случайного числа, в данной программе для скорости
unsigned random(PRNG &generator, unsigned minValue, unsigned maxValue)
{
    std::uniform_int_distribution<unsigned> distribution(minValue, maxValue);
    return distribution(generator.engine);
}

// Для случайного значения цвета
unsigned random_color(PRNG &generator)
{
    std::uniform_int_distribution<unsigned> distribution(0, 255);
    return distribution(generator.engine);
}

//Для степени (-1) для получения случайного направления скорости
unsigned random_sign(PRNG &generator)
{
    std::uniform_int_distribution<unsigned> distribution(0, 1);
    return distribution(generator.engine);
}

float vectorLenght(sf::Vector2f &argument)
{
    return (pow((pow(argument.x, 2.0) + pow(argument.y, 2.0)), 0.5));
}

// Проверка на отсутствие шаров в радиусе от нажатия мыши
bool isNotShapeRadius(std::vector<Ball> &balls, sf::Vector2f clickPosition)
{
    bool answer = true;
    for (size_t i = 0; i < balls.size(); ++i)
    {
        sf::Vector2f delta = balls[i].shape.getPosition() - clickPosition;
        if (vectorLenght(delta) <= BALL_SIZE * 2)
        {
            answer = false;
        }
    }
    return answer;
}

void initBall(std::vector<Ball> &balls, sf::Vector2f clickPosition, PRNG &generator, std::vector<Color> &colors)
{
    if (isNotShapeRadius(balls, clickPosition))
    {
        Ball null; // Пустая структура для заполнения нового элемента
        balls.push_back(null);

        // Инициализируем новый шар если он не находится в зоне другого шара
        size_t i = balls.size() - 1;
        float signX = random_sign(generator);
        float signY = random_sign(generator);
        float randomSpeedX = random(generator, 50, 250) * pow(-1.0, signX);
        float randomSpeedY = random(generator, 50, 250) * pow(-1.0, signY);
        balls[i].speed = {randomSpeedX, randomSpeedY};
        balls[i].shape.setRadius(BALL_SIZE);

        sf::Color color;

        // Выбираем две случайные строки из массива и берем их номера
        size_t Clr1 = random(generator, 0, colors.size() - 1);
        size_t Clr2 = random(generator, 0, colors.size() - 1);

        //Для каждого цветового сегмента находим среднее арифм. цветов из выбранных выше строк
        color.r = (colors[Clr1].colors[0] + colors[Clr2].colors[0]) / 2;
        color.g = (colors[Clr1].colors[1] + colors[Clr2].colors[1]) / 2;
        color.b = (colors[Clr1].colors[2] + colors[Clr2].colors[2]) / 2;

        balls[i].shape.setFillColor(color);
        balls[i].shape.setPosition({clickPosition});
    }
}

void pollEvents(sf::RenderWindow &window, std::vector<Ball> &balls, PRNG &generator, std::vector<Color> &colors)
{
    sf::Vector2f clickPosition;
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        // Добавляем новый шар при клике мыши
        case sf::Event::MouseButtonReleased:
            clickPosition = {float(event.mouseButton.x) - BALL_SIZE / 2, float(event.mouseButton.y) - BALL_SIZE / 2};
            initBall(balls, clickPosition, generator, colors);
            break;
        default:
            break;
        }
    }
}

void redrawFrame(sf::RenderWindow &window, std::vector<Ball> &balls)
{
    window.clear();
    for (size_t i = 0; i < balls.size(); ++i)
    {
        window.draw(balls[i].shape);
    }
    window.display();
}

// Скалярное произведение
float dot(sf::Vector2f speedVector, sf::Vector2f posVector)
{
    return ((speedVector.x * posVector.x) + (speedVector.y * posVector.y));
}

// Обновление скорости про столкновении с другим шаром
void speedUpdate(std::vector<Ball> &balls, size_t fi, size_t si)
{
    sf::Vector2f deltaPos = balls[fi].shape.getPosition() - balls[si].shape.getPosition();
    sf::Vector2f deltaSpeed = balls[fi].speed - balls[si].speed;
    float speedX = balls[fi].speed.x - (dot(deltaSpeed, deltaPos) / pow(vectorLenght(deltaPos), 2.0)) * deltaPos.x;
    float speedY = balls[fi].speed.y - (dot(deltaSpeed, deltaPos) / pow(vectorLenght(deltaPos), 2.0)) * deltaPos.y;
    balls[fi].speed = {speedX, speedY};

    deltaPos = -deltaPos;
    deltaSpeed = -deltaSpeed;
    speedX = balls[si].speed.x - (dot(deltaSpeed, deltaPos) / pow(vectorLenght(deltaPos), 2.0)) * deltaPos.x;
    speedY = balls[si].speed.y - (dot(deltaSpeed, deltaPos) / pow(vectorLenght(deltaPos), 2.0)) * deltaPos.y;
    balls[si].speed = {speedX, speedY};
}

// Проверка на столкновение шаров и обновление их скорости при его наличии
void checkBallCollision(std::vector<Ball> &balls)
{
    for (size_t fi = 0; fi < balls.size(); ++fi)
    {
        for (size_t si = fi + 1; si < balls.size(); ++si)
        {
            sf::Vector2f delta = balls[fi].shape.getPosition() - balls[si].shape.getPosition();
            if (vectorLenght(delta) <= BALL_SIZE * 2)
            {
                speedUpdate(balls, fi, si);
            }
        }
    }
}

bool isDead(Ball ball)
{
    return (ball.deathTimer <= 0);
}
// Проверка на окончание таймера сверху, снизу удаление шаров отживших 10 секунд
void eraseDeadBall(std::vector<Ball> &balls)
{
    auto newEnd = std::remove_if(balls.begin(), balls.end(), isDead);
    balls.erase(newEnd, balls.end());
}

void checkWallCollision(std::vector<Ball> &balls)
{
    for (size_t i = 0; i < balls.size(); ++i)
    {
        sf::Vector2f position = balls[i].shape.getPosition();

        if ((position.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (balls[i].speed.x > 0))
        {
            balls[i].speed.x = -balls[i].speed.x;
        }
        if ((position.x < 0) && (balls[i].speed.x < 0))
        {
            balls[i].speed.x = -balls[i].speed.x;
        }
        if ((position.y + 2 * BALL_SIZE >= WINDOW_HEIGHT) && (balls[i].speed.y > 0))
        {
            balls[i].speed.y = -balls[i].speed.y;
        }
        if ((position.y < 0) && (balls[i].speed.y < 0))
        {
            balls[i].speed.y = -balls[i].speed.y;
        }
    }
}

void update(sf::Clock &clock, std::vector<Ball> &balls)
{
    eraseDeadBall(balls);
    checkWallCollision(balls);
    const float dt = (clock.restart().asSeconds()) / INTERACTION_COUNT;

    for (unsigned ii = 0; ii < INTERACTION_COUNT; ++ii)
    {
        checkBallCollision(balls);
        for (size_t bi = 0; bi < balls.size(); ++bi)
        {
            balls[bi].shape.setPosition(balls[bi].shape.getPosition() + balls[bi].speed * dt);
            balls[bi].deathTimer -= dt;
        }
    }
}

int main()
{
    PRNG generator;
    initGenerator(generator);

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Moving Ball");
    sf::Clock clock;

    std::vector<Color> colors = {
        {0, 0, 255}, //Каждая строка это отдельный цвет
        {0, 255, 0},
        {0, 255, 255},
        {255, 0, 0},
        {255, 0, 255},
        {255, 255, 0},
        {255, 255, 255}};

    std::vector<Ball> balls;

    while (window.isOpen())
    {
        pollEvents(window, balls, generator, colors);
        update(clock, balls);
        redrawFrame(window, balls);
    }
}