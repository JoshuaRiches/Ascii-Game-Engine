/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File: Constants.h
// Author: Joshua L Riches
// Date Created: December 18th (rough estimate based on first push to github)
// Brief: this contains the constants to be used throughout the main game loop
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CONSTANTS_H
#define CONSTANTS_H

//Headers
#include <Windows.h>

// Defines
#define SCREEN_WIDTH 150
#define SCREEN_HEIGHT 40
#define FRAME_RATE 5

// Keys: these are the keyboard inputs that the player will be able to interface with in the game
const int KEY_ESC = VK_ESCAPE;
const int KEY_ENTER = VK_RETURN;
const int KEY_W = 'W';
const int KEY_A = 'A';
const int KEY_S = 'S';
const int KEY_D = 'D';
const int KEY_1 = '1';
const int KEY_2 = '2';
const int KEY_3 = '3';
const int KEY_4 = '4';

// Player Parameters
const float ACCELERATION_RATE = 0.5f;
const float DECELERATION_RATE = 0.2f;
const float FUEL_CONSUMPTION_RATE = 0.5f;
const int BASE_SCORE = 50; // The score you get for landing which is then multiplied by the modifier

#endif // !CONSTANTS_H

