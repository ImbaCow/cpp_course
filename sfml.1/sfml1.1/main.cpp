#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
 
int main()
{
    sf::RenderWindow window(sf::VideoMode({200, 530}), "sfml1.1");
 
    window.clear();
 
    sf::RectangleShape shape1;
    shape1.setSize({180, 510});
    shape1.setPosition({10, 10});
    shape1.setFillColor(sf::Color(79, 79, 79));
    window.draw(shape1);
 
    sf::CircleShape shape2(75);
    shape2.setPosition({25, 25});
    shape2.setFillColor(sf::Color(0, 0xFF, 0));
    window.draw(shape2);
 
    sf::CircleShape shape3(75);
    shape3.setPosition({25, 190});
    shape3.setFillColor(sf::Color(0xFF, 0xFF, 0));
    window.draw(shape3);
 
    sf::CircleShape shape4(75);
    shape4.setPosition({25, 355});
    shape4.setFillColor(sf::Color(0xFF, 0, 0));
    window.draw(shape4);
 
    window.display();
 
    sf::sleep(sf::seconds(5));
}