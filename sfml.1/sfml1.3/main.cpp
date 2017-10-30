#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::ConvexShape house1;
    house1.setFillColor(sf::Color(47, 25, 00));
    house1.setPosition({465, 770});
    house1.setPointCount(4);
    house1.setPoint(0, {-350, -225});
    house1.setPoint(1, {-350, +225});
    house1.setPoint(2, {+350, +225});
    house1.setPoint(3, {+350, -225});

    sf::ConvexShape door;
    door.setFillColor(sf::Color(00, 00, 00));
    door.setPosition({235, 890});
    door.setPointCount(4);
    door.setPoint(0, {-75, -125});
    door.setPoint(1, {-75, +125});
    door.setPoint(2, {+75, +125});
    door.setPoint(3, {+75, -125});

    sf::ConvexShape krisha;
    krisha.setFillColor(sf::Color(80, 00, 00));
    krisha.setPosition({465, 438});
    krisha.setPointCount(4);
    krisha.setPoint(0, {-450, +112});
    krisha.setPoint(1, {-235, -113});
    krisha.setPoint(2, {+235, -113});
    krisha.setPoint(3, {+450, +112});

    sf::ConvexShape tube1;
    tube1.setFillColor(sf::Color(79, 79, 79));
    tube1.setPosition({595, 388});
    tube1.setPointCount(4);
    tube1.setPoint(0, {-50, -75});
    tube1.setPoint(1, {-50, +75});
    tube1.setPoint(2, {+50, +75});
    tube1.setPoint(3, {+50, -75});

    sf::ConvexShape tube2;
    tube2.setFillColor(sf::Color(79, 79, 79));
    tube2.setPosition({595, 313});
    tube2.setPointCount(4);
    tube2.setPoint(0, {-75, -50});
    tube2.setPoint(1, {-75, +50});
    tube2.setPoint(2, {+75, +50});
    tube2.setPoint(3, {+75, -50});

    sf::CircleShape shape1(70);
    shape1.setPosition({550, 188});
    shape1.setFillColor(sf::Color(70, 70, 70));

    sf::CircleShape shape2(70);
    shape2.setPosition({610, 118});
    shape2.setFillColor(sf::Color(70, 70, 70));

    sf::CircleShape shape3(70);
    shape3.setPosition({680, 48});
    shape3.setFillColor(sf::Color(70, 70, 70));

    sf::CircleShape shape4(70);
    shape4.setPosition({730, 20});
    shape4.setFillColor(sf::Color(70, 70, 70));

    sf::RenderWindow window(sf::VideoMode({1000, 1000}), "My Future House)0)");
    window.clear();
    window.draw(house1);
    window.draw(door);
    window.draw(shape1);
    window.draw(shape2);
    window.draw(shape3);
    window.draw(shape4);
    window.draw(krisha);
    window.draw(tube1);
    window.draw(tube2);
    window.display();

    sf::sleep(sf::seconds(5));
}