#pragma once
#include <SFML/Graphics.hpp>

// Global
static const unsigned WINDOW_WIDTH = 1000;
static const unsigned WINDOW_HEIGHT = 800;

static const sf::Vector2f HIT_BOX_SIZE = {40, 30};

static const float LEVEL_UP_PAUSE = 3;
static const unsigned LEVEL_COUNT = 5;

static const float BULLET_OFFSET = 45;

// Score
static const unsigned SCORE_PER_RANGE_DMG = 15;
static const unsigned SCORE_PER_MELEE_DMG = 10;
static const unsigned SCORE_PER_BOSS_DMG = 20;

// Hero
static const sf::Vector2f START_POSITION(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
static const float TANK_SPEED = 150;
static const float ROTAION_SPEED = 150;

static const unsigned MAX_HEALTH = 100;

static const float HERO_BLAST_COUNT = 40;
static const float HERO_BLAST_COOLDOWN = 15;

static const float SHOT_COOLDOWN = 0.4;
static const float HERO_BULLET_DMG = 1;

// Enemy
static const float ENEMY_TANK_SPEED = 75;
static const float ENEMY_ROTAION_SPEED = 100;

static const float SPAWN_COOLDOWN = 0.7;
static const float MAX_SHOT_DELAY = 2;

static const sf::Vector2f HEALTH_BAR_SIZE = {35, 5};
static const sf::Vector2f HEALTH_BAR_OFFSET = {HEALTH_BAR_SIZE.x / 2, -25};

// Boss
static const unsigned BOSS_BLAST_COUNT = 20;
static const float BOSS_FIRE_DMG = 0.14;
static const float BOSS_SPAWN_CD = 5;
static const float B_CHANGE_MOVE_RADIUS_1 = 250;
static const float B_CHANGE_MOVE_RADIUS_2 = 450;
static const float BOSS_TANK_SPEED = 100;
static const float BOSS_SHOT_COOLDOWN = 1;
static const float BOSS_BULLET_DMG = 2;
static const float BOSS_BULLET_RADIUS = 8;
static const sf::Vector2f BOSS_HIT_BOX_SIZE = {80, 60};
static const float BOSS_MAX_HEALTH = 100;
static const sf::Vector2f BOSS_INIT_POS = {200, 400};
static const float BOSS_ROTAION_SPEED = 100;
static const float BOSS_BULLET_OFFSET = 90;
static const sf::Vector2f BOSS_HEALTH_BAR_SIZE = {800, 30};
static const sf::Vector2f BOSS_HEALTH_BAR_POS = {100, 50};

// Enemy AI
static const float COLLUSION_RADIUS = 60;
static const float ENEMY_PREDICTION_LEVEL = 75;
static const float R_CHANGE_MOVE_RADIUS = 300;
static const float M_CHANGE_MOVE_RADIUS = 75;

// Range enemy
static const unsigned RANGE_MAX_HEALTH = 3;
static const float R_ENEMY_SHOT_COOLDOWN = 2;
static const float BULLET_DMG = 1;

// Melee enemy
static const unsigned MELEE_MAX_HEALTH = 3;

static const float M_ENEMY_SHOT_COOLDOWN = 0.15;
static const float M_ENEMY_SHOT_ANGLE = 70;
static const unsigned M_SHOT_COUNT = 10;
static const float FIRE_LIFE_TIME = 0.3;
static const float FIRE_DMG = 0.07;

// Bullet
static const float BULLET_SPEED = 500;
static const float BULLET_RADIUS = 4;

// Buttons
static const sf::Vector2f BUTTON_SIZE = {200, 55};
static const sf::Color BUTTON_DEACTIVE_COLOR = {24, 95, 14};
static const sf::Color BUTTON_ACTIVE_COLOR = {24, 198, 18};
static const float OUT_THICK_SIZE = 3;
static const sf::Color OUT_THICK_COLOR = sf::Color::Black;

static const sf::Vector2f PLAY_POS = {500, 400};
static const sf::Vector2f MENU_POS = {500, 600};
static const sf::Vector2f CONTINUE_POS = {500, 500};

// Text
static const sf::Color TEXT_COLOR = sf::Color::Black;
static const float CHAR_SIZE = 35;
static const float TITLE_CHAR_SIZE = 100;
static const float SCORE_CHAR_SIZE = 30;

static const sf::Vector2f SCORE_POS = {500, 350};
static const sf::Vector2f TITLE_TEXT_POS = {500, 200};
static const sf::Vector2f LEVEL_TEXT_POS = {500, 600};