#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <algorithm>

struct Figure
{
    sf::ConvexShape eyeL; // Левый зрачок
    sf::ConvexShape eyeR; // Правый
    const int pointCount = 200;
    const sf::Vector2f eyeRadius = {33, 56};
    sf::Vector2f eyePositionL = {250, 320};
    sf::Vector2f eyePositionR = {550, 320};
};

void init(Figure &eye, sf::ConvexShape &base)
{
    base.setFillColor(sf::Color(255, 255, 255));
    base.setPointCount(eye.pointCount);
    for (int pointNo = 0; pointNo < eye.pointCount; pointNo++)
    {
        float angle = float(2 * M_PI * pointNo) / float(eye.pointCount);
        sf::Vector2f point = sf::Vector2f{
            eye.eyeRadius.x * 3 * std::sin(angle),
            eye.eyeRadius.y * 3 * std::cos(angle)};
        base.setPoint(pointNo, point);
    }

    eye.eyeL.setPosition(eye.eyePositionL);
    eye.eyeL.setFillColor(sf::Color(0, 0, 0));
    eye.eyeL.setPointCount(eye.pointCount);
    for (int pointNo = 0; pointNo < eye.pointCount; pointNo++)
    {
        float angle = float(2 * M_PI * pointNo) / float(eye.pointCount);
        sf::Vector2f point = sf::Vector2f{
            eye.eyeRadius.x * std::sin(angle),
            eye.eyeRadius.y * std::cos(angle)};
        eye.eyeL.setPoint(pointNo, point);
    }

    eye.eyeR.setPosition(eye.eyePositionR);
    eye.eyeR.setFillColor(sf::Color(0, 0, 0));
    eye.eyeR.setPointCount(eye.pointCount);
    for (int pointNo = 0; pointNo < eye.pointCount; pointNo++)
    {
        float angle = float(2 * M_PI * pointNo) / float(eye.pointCount);
        sf::Vector2f point = sf::Vector2f{
            eye.eyeRadius.x * std::sin(angle),
            eye.eyeRadius.y * std::cos(angle)};
        eye.eyeR.setPoint(pointNo, point);
    }
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition)
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
            mousePosition = {float(event.mouseMove.x), float(event.mouseMove.y)};
            break;
        default:
            break;
        }
    }
}

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &base, Figure &eye)
{
    window.clear();
    base.setPosition(eye.eyePositionL);
    window.draw(base);
    window.draw(eye.eyeL);
    base.setPosition(eye.eyePositionR);
    window.draw(base);
    window.draw(eye.eyeR);
    window.display();
}

sf::Vector2f toEuclidean(float angle, sf::Vector2f vector)
{
    return {
        vector.x * std::cos(angle),
        vector.y * std::sin(angle)};
}

float vectorLenght(sf::Vector2f &argument)
{
    return pow((pow(argument.x, 2.0) + pow(argument.y, 2.0)), 0.5);
}

void update(sf::Vector2f &mousePosition, Figure &eye)
{
    sf::Vector2f delta = mousePosition - eye.eyePositionL;
    float eyeRotation = atan2(delta.y, delta.x);
    sf::Vector2f eyeOffset = toEuclidean(eyeRotation, eye.eyeRadius);
    float nom = vectorLenght(delta) / vectorLenght(eyeOffset);                // Коэффициент отношения длины вектора позиции мыши к длине позиции глаза
    sf::Vector2f mouseOffset = toEuclidean(eyeRotation, eye.eyeRadius * nom); //
    if (vectorLenght(eyeOffset) >= vectorLenght(delta))
    {
        eye.eyeL.setPosition(eye.eyePositionL + mouseOffset);
    }
    else
    {
        eye.eyeL.setPosition(eye.eyePositionL + eyeOffset);
    }

    delta = mousePosition - eye.eyePositionR;
    eyeRotation = atan2(delta.y, delta.x);
    eyeOffset = toEuclidean(eyeRotation, eye.eyeRadius);
    nom = vectorLenght(delta) / vectorLenght(eyeOffset);
    mouseOffset = toEuclidean(eyeRotation, eye.eyeRadius * nom);
    if (vectorLenght(eyeOffset) >= vectorLenght(delta))
    {
        eye.eyeR.setPosition(eye.eyePositionR + mouseOffset);
    }
    else
    {
        eye.eyeR.setPosition(eye.eyePositionR + eyeOffset);
    }
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Eye",
        sf::Style::Default, settings);

    Figure eye; // Левый и правый зрачок
    sf::Vector2f mousePosition;
    sf::ConvexShape base; // Оболочка глаза

    init(eye, base);

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, eye);
        redrawFrame(window, base, eye);
    }
}