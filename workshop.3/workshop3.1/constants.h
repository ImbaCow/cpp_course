#pragma once
#include <SFML/Graphics.hpp>

static const unsigned WINDOW_WIDTH = 800;
static const unsigned WINDOW_HEIGHT = 600;
static const unsigned INITIALS_SIZE = 30;
static const unsigned BALL_RADIUS = 120;
static const unsigned OUTLINE_SIZE = 3;
static const float GRAVITY_ACCELERATION = 100; //px per second^2
static const sf::Vector2f START_POSITION(WINDOW_WIDTH / 2, WINDOW_HEIGHT - BALL_RADIUS - OUTLINE_SIZE);
static const sf::Vector2f START_SPEED({100, 200});
static const char *INITIALS_TEXT = "YES"; // Yambakov Egor Sergeevich