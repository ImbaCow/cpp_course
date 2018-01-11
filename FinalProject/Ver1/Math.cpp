#include "Math.h"
#include "consts.h"
#include <math.h>
#include <ctime>
#include <cmath>
#include <sstream>

Math::Math()
{
    const unsigned seed = unsigned(std::time(nullptr));
    generator.seed(seed);
}

float Math::random(unsigned minValue, unsigned maxValue)
{
    std::uniform_int_distribution<unsigned> distribution(minValue, maxValue);
    return distribution(generator);
}

float Math::toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

float Math::toRadians(float degrees)
{
    return float(double(degrees) / 180.0 * M_PI);
}

float Math::vectorLenght(sf::Vector2f vector)
{
    return hypot(vector.x, vector.y);
}

std::string Math::toString(int i)
{
    std::ostringstream str;
    str << i;
    return str.str();
}

bool Math::isInRoundRect(sf::Vector2f pointPos, sf::Vector2f boxPos, sf::Vector2f boxSize, float boxRotatation)
{
    sf::Vector2f delta = pointPos - boxPos;

    sf::Vector2f newPointPos;
    newPointPos.x = delta.x * cos(-toRadians(boxRotatation)) - delta.y * sin(-toRadians(boxRotatation));
    newPointPos.y = delta.x * sin(-toRadians(boxRotatation)) + delta.y * cos(-toRadians(boxRotatation));

    return ((newPointPos.x <= boxSize.x / 2) &&
            (newPointPos.x >= -boxSize.x / 2) &&
            (newPointPos.y <= boxSize.y / 2) &&
            (newPointPos.y >= -boxSize.y / 2));
}

sf::Text Math::initText(sf::Font &font, std::string textString, float charSize, sf::Vector2f textPos)
{
    sf::FloatRect textBox;
    text.setFont(font);

    text.setString(textString);
    text.setCharacterSize(charSize);
    textBox = text.getGlobalBounds();
    text.setOrigin({textBox.width / 2, textBox.height / 2});

    text.setPosition(textPos);
    text.setFillColor(TEXT_COLOR);

    return text;
}

sf::RectangleShape Math::initRect(sf::Vector2f size, sf::Vector2f position, sf::Color rectColor)
{
    rect.setSize(size);
    rect.setPosition(position);
    rect.setOrigin(size * 0.5f);
    rect.setFillColor(rectColor);

    rect.setOutlineThickness(OUT_THICK_SIZE);
    rect.setOutlineColor(OUT_THICK_COLOR);

    return rect;
}