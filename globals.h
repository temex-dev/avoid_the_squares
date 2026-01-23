#ifndef GLOBALS_H
#define GLOBALS_H
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>

using namespace std;

const int DISPLAY_WIDTH = 1920;
const int DISPLAY_HEIGHT = 1080;
const int WINDOW_SIZE = 800;


struct vect3 { int r, g, b; };
const vect3 GREEN_VEIN = {75, 83, 32};
const vect3 RED_VEIN = {136, 69, 19};
const vect3 WHITE_VEIN = {210, 180, 140};


const float PLAYER_SPEED = 5.0f;
const float ENEMY_SPEED = 2.0f;

const float PLAYER_SIZE = 20.f;
const float ENEMY_SIZE = 40.f;

#endif // GLOBALS_H