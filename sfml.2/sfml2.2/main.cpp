#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

int main() //Добавил вращение розы относительно своей оси и 
           //перемещение центра цветка по окружности вместе, т.к. непонял задание
{
    constexpr int pointCount = 200;
    float shapeRadius = 100;
    sf::Vector2f shapeCenter = {400, 300};
    sf::Clock totalClock;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({800, 600}), "Polar Rose",
        sf::Style::Default, settings);
    
    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        const float time = totalClock.getElapsedTime().asSeconds(); //Время добавил для скорости перемещения розы
        float speed = time * 100;
        float shapeAngle = float(2* M_PI * speed) / float(pointCount);
        sf::Vector2f shapePoint = sf::Vector2f
        {
            shapeRadius * std::sin(shapeAngle),
            shapeRadius * std::cos(shapeAngle)
        }; //Добавил перемещение центра розы по окружности радиусом shapeRadius

        sf::ConvexShape rose;
        rose.setPosition(shapeCenter + shapePoint); //Сложили начальные кординаты центра круга и кординаты перемещения
        rose.setFillColor(sf::Color(0xD2, 0x69, 0x1E));

        rose.setPointCount(pointCount);

        float koef = M_PI * time; //Добавил коэффициент для вращения розы вокруг своей оси
        
        for (int pointNo = 0; pointNo < pointCount; pointNo ++)
        {
            float angle = float(2* M_PI * pointNo) / float(pointCount);
            float roseRadius = 200 * std::sin(6 * angle + koef); //Прибавил коеф к углу для вращения цветка
            sf::Vector2f point = sf::Vector2f
            {
                roseRadius * std::sin(angle),
                roseRadius * std::cos(angle)
            };
            rose.setPoint(pointNo, point);
        }  

        window.clear();
        window.draw(rose);
        window.display();
    }
}