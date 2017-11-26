#pragma once
#include "constants.h"

void createWindow(sf::RenderWindow &window);

void pollEvents(sf::RenderWindow &window);

void redrawFrame(sf::RenderWindow &window, sf::Drawable &initial);