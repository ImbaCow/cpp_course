#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({700, 330}), "Yambakov Egor Sergeevich");

    window.clear();

    sf::RectangleShape shape11;
    shape11.setSize({180, 45});
    shape11.setPosition({285, 25});
    shape11.setFillColor(sf::Color(79, 79, 79));
    window.draw(shape11);

    sf::RectangleShape shape12;
    shape12.setSize({45, 290});
    shape12.setPosition({285, 25});
    shape12.setFillColor(sf::Color(79, 79, 79));
    window.draw(shape12);

    sf::RectangleShape shape13;
    shape13.setSize({180, 45});
    shape13.setPosition({285, 275});
    shape13.setFillColor(sf::Color(79, 79, 79));
    window.draw(shape13);

    sf::RectangleShape shape14;
    shape14.setSize({180, 45});
    shape14.setPosition({285, 145});
    shape14.setFillColor(sf::Color(79, 79, 79));
    window.draw(shape14);

    sf::RectangleShape shape21;
    shape21.setSize({180, 45});
    shape21.setPosition({495, 25});
    shape21.setFillColor(sf::Color(79, 79, 79));
    window.draw(shape21);

    sf::RectangleShape shape22;
    shape22.setSize({45, 130});
    shape22.setPosition({495, 25});
    shape22.setFillColor(sf::Color(79, 79, 79));
    window.draw(shape22);

    sf::RectangleShape shape23;
    shape23.setSize({180, 45});
    shape23.setPosition({495, 150});
    shape23.setFillColor(sf::Color(79, 79, 79));
    window.draw(shape23);

    sf::RectangleShape shape24;
    shape24.setSize({45, 150});
    shape24.setPosition({630, 150});
    shape24.setFillColor(sf::Color(79, 79, 79));
    window.draw(shape24);

    sf::RectangleShape shape25;
    shape25.setSize({180, 45});
    shape25.setPosition({495, 275});
    shape25.setFillColor(sf::Color(79, 79, 79));
    window.draw(shape25);

    sf::RectangleShape shape31;
    shape31.setSize({45, 165});
    shape31.setPosition({113, 150});
    shape31.setFillColor(sf::Color(79, 79, 79));
    window.draw(shape31);

    sf::RectangleShape shape32;
    shape32.setRotation(-225);
    shape32.setSize({45, 180});
    shape32.setPosition({167, 155});
    shape32.setFillColor(sf::Color(79, 79, 79));
    window.draw(shape32);

    sf::RectangleShape shape33;
    shape33.setRotation(-135);
    shape33.setSize({45, 135});
    shape33.setPosition({167, 155});
    shape33.setFillColor(sf::Color(79, 79, 79));
    window.draw(shape33);

    window.display();

    sf::sleep(sf::seconds(5));
}