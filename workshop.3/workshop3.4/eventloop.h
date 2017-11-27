#pragma once
#include "Ship.h"

void createWindow(sf::RenderWindow &window);

void pollEvents(sf::RenderWindow &window, Ship &ship);

void redrawFrame(sf::RenderWindow &window, sf::Drawable &ship);
