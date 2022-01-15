/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File: GameObjects.h
// Author: Joshua L Riches
// Date Created: December 11th (rough estimate based on first push to github)
// Brief: this contains the structs of the different objects within the game
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

#include "Constants.h"

// STRUCTS

/// <summary>
/// This is the Struct that contains all the variables, functions, and sprites relating directly to the player
/// </summary>
struct Player
{
	// Functions
	
	/// <summary>
	/// This Function resets the player's values to their default value needed, this is used so that the gam can be played more than once
	/// </summary>
	void Reset()
	{
		xPos = SCREEN_WIDTH / 4;
		yPos = 5;
		isAccelerating = false;
		acceleration = 0.0f;
		hasLanded = false;
		hasCrashed = false;
		isMovingLeft = false;
		isMovingRight = false;
		fuelCollected = false;
	}
	/// <summary>
	/// This will reset the fuel back to 100, it is a separate function to reset as i only want this to happen upon crashing,
	/// but Reset() gets called on crash and land, so it needed to be separate
	/// </summary>
	void Refill()
	{
		fuel = 100;
	}

	// Constants
	// Height and width of player sprite
	static const int WIDTH = 4;
	static const int HEIGHT = 3;

	// Default player sprite and colours
	const char* CHARACTERS_DEFAULT = {
		R"(=__ )"
		R"( || )"
		R"( /\ )"
	};
	const int COLOURS_DEFAULT[WIDTH * HEIGHT] = {
		0xA, 0xF, 0xF, 0xF,
		0xF, 0xF, 0xF, 0xF,
		0xF, 0xE, 0xE, 0xF,
	};

	// Player sprite when moving left, and its colours
	const char* CHARACTERS_LEFT = {
		R"(=__ )"
		R"( ||<)"
		R"( /\ )"
	};
	const int COLOURS_LEFT[WIDTH * HEIGHT] = {
		0xA, 0xF, 0xF, 0xF,
		0xF, 0xF, 0xF, 0xE,
		0xF, 0xF, 0xF, 0xF,
	};

	// Player sprite when moving right, and its colours
	const char* CHARACTERS_RIGHT = {
		R"(=__ )"
		R"(>|| )"
		R"( /\ )"
	};
	const int COLOURS_RIGHT[WIDTH * HEIGHT] = {
		0xA, 0xF, 0xF, 0xF,
		0xE, 0xF, 0xF, 0xF,
		0xF, 0xF, 0xF, 0xF,
	};

	// Variables: these are the variables used in the main game loop that relate to the player.
	int xPos = SCREEN_WIDTH / 4;
	int yPos = 5;
	bool isAccelerating = false;
	float acceleration = 0.0f;
	bool hasLanded = false;
	bool hasCrashed = false;
	float fuel = 100;
	bool isMovingLeft = false;
	bool isMovingRight = false;
	int currentScore = 0;
	float velocityY;
	bool fuelCollected = false;
};

/// <summary>
/// This struct contains the frames for the explosion animation and the colours for the sprites in the animation
/// </summary>
struct Explosion
{
	// Dimensions of the sprites for the explosion
	static const int WIDTH = 7;
	static const int HEIGHT = 5;

	const char* EMPTY_CHARACTERS{
		R"(       )"
		R"(       )"
		R"(       )"
		R"(       )"
		R"(       )"
	};
	const char* CHARACTERS_SMALL = {
		R"(       )"
		R"(  \|/  )"
		R"(  - -  )"
		R"(  /|\  )"
		R"(       )"
	};
	const char* CHARACTERS_BIG = {
		R"(\  |  /)"
		R"(       )"
		R"(-     -)"
		R"(       )"
		R"(/  |  \)"
	};
	const int COLOURS[WIDTH * HEIGHT] = {
		0xE, 0xE, 0xE, 0xE, 0xE, 0xE, 0xE,
		0xE, 0xE, 0xE, 0xE, 0xE, 0xE, 0xE,
		0xE, 0xE, 0xE, 0xE, 0xE, 0xE, 0xE,
		0xE, 0xE, 0xE, 0xE, 0xE, 0xE, 0xE,
		0xE, 0xE, 0xE, 0xE, 0xE, 0xE, 0xE,
	};

};

/// <summary>
/// This struct contains the character array for the background 
/// </summary>
struct Background
{
	// Constants
	const char* CHARACTERS = {
		R"(                                                                                                                                                      )"
		R"( *               .   *               .             *   .          .            .                                                                      )"
		R"(        *                           *                                                  *          .               .              .                    )"
		R"( .                .                    .                    .                                            *                                  *         )"
		R"(                                                                                                 *   .                .                .              )"
		R"(                                                                      .                                        *                *               *     )"
		R"(.         *              .                          *                           .                                 ___                                 )"
		R"(                                   *                            .              ^             *                   /X2 \     .           *              )"
		R"(      .           *                                .                       *  / \   ___                         /     \__                       .     )"
		R"( *                          .                                  *             /    \/X4 \  .                    /       X4\                            )"
		R"(               .                         *             .                    /           |          *          /           \         *                 )"
		R"(    .                  *                                                   /             \                   |             |                          )"
		R"(             .                      .               *              *      /               |      .           |              \____    .        *       )"
		R"(  *                      .               .                               /                 |                /                 X4 \                    )"
		R"(     .           *                                            .         /                  |               /                      \                   )"
		R"(             .             *                     *                 ____/                    \             |                        |         .        )"
		R"(                                        .                         / X2                       |     .     /                         |                  )"
		R"(       *              *          .               .               /                           |          |                           \   .             )"
		R"(                                                                /                            |          |                            \                )"
		R"(   .           *                         ____             *     |                              \       /                              |____    *      )"
		R"(                            .           | X2 \      .          /                                |     /                                 X2 \          )"
		R"(             .      *                  /      \__            |                                 |     /                                      \         )"
		R"(                                 *    |        x4\      .   /                                  |____/                                        \  .     )"
		R"(    .                       /\       /            \        |                                     X4                                           |       )"
		R"(               .           /  \     |              \  ____/                                                                                    \___ * )"
		R"(                    ___   /    \___/                \/ X2                                                                                        X4\  )"
		R"(       .           /X2 \ /      X4                                                                                                                  \ )"
		R"(             *    /     \                                                                                                                             )"
		R"(  .              /                                                                                                                                    )"
		R"(       ___      /                                                                                                                                     )"
		R"(      /X2 \ .  /                                                                                                                                      )"
		R"(     /     \  /                                                                                                                                       )"
		R"(.   |       \/                                                                                                                                        )"
		R"(    |                                                                                                                                                 )"
		R"(    /                                                                                                                                                 )"
		R"( __/                                                                                                                                                  )"
		R"( X2                                                                                                                                                   )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
	};

};

/// <summary>
/// This struct contains the variables and sprites for the splash screen
/// </summary>
struct Splash
{
	// Constants
	// Dimensions of splash screen sprite
	static const int WIDTH = 16;
	static const int HEIGHT = 6;
	
	// The sprite to be dispalyed as the splash screen and its colours
	const char* CHARACTERS = {
		R"(  Lunar Lander  )"
		R"(       __       )"
		R"(       ||       )"
		R"(       /\       )"
		R"(       By       )"
		R"( Joshua  Riches )"
	};
	const int COLOURS[WIDTH * HEIGHT] = {
		0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,
		0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,
		0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,
		0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,
		0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,
		0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,
	};

	// Variables
	float duration = 0.0f;
};

/// <summary>
/// This struct contains the sprites and variables relating to the fuel pickups you can get in the game
/// </summary>
struct Fuel
{
	// Constants
	// Dimensions of the sprite
	static const int WIDTH = 1;
	static const int HEIGHT = 1;
	// SPrite for fuel and its colours
	const char* CHARACTERS = {
	R"(F)"
	};
	const int COLOURS[WIDTH * HEIGHT] = {
		4,
	};

	// Variables for the fuel pickup
	int fuelX = 0;
	int fuelY = 0;
	bool fuelExists = false;
};

/// <summary>
/// This struct contains the character arrays for what is to be displayed on the menu screen and options screen
/// </summary>
struct Menu
{
	//Main menu screen
	const char* CHARACTERS = {
		R"(                                                                                                                                                      )"
		R"(                         ____            ___________     ___      ___     __________      __________     __________      ____                         )"
		R"(                        |    |          |    ___    |   |   |\   |   |   |   ____   \    |   _______|   |    ____  |    |    |                        )"
		R"(                        |    |          |   |   |   |   |   | \  |   |   |  |    \   |   |  |           |   |____| |    |    |                        )"
		R"(                        |    |          |   |___|   |   |   |  \ |   |   |  |     |  |   |  |_______    |        __|    |    |                        )"
		R"(                        |    |          |   |___|   |   |   |\  \|   |   |  |     |  |   |   _______|   |   |\   \      |____|                        )"
		R"(                        |    |______    |   |   |   |   |   | \  |   |   |  |     |  |   |  |           |   | \   \      ____                         )"
		R"(                        |           |   |   |   |   |   |   |  \ |   |   |  |____/   |   |  |_______    |   |  \   \    |    |                        )"
		R"(                        |___________|   |___|   |___|   |___|   \|___|   |__________/    |__________|   |___|   \___\   |____|                        )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                   __                                                                                 )"
		R"(                                                                  |__| |     /\  \ /                                                                  )"
		R"(                                                                  |    |___ /~~\  |                                                                   )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                              __   __  ___    __        __                                                            )"
		R"(                                                             /  \ |__|  |  | /  \ |\ | /__'                                                           )"
		R"(                                                             \__/ |     |  | \__/ | \| .__/                                                           )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                     __         ___                                                                   )"
		R"(                                                                    /  \ |  | |  |                                                                    )"
		R"(                                                                    \__X \__/ |  |                                                                    )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
	};

	//options page screen
	const char* CHARACTERS_OPTIONS = {
		R"(                                                                                                                                                      )"
		R"(                         ____            ___________     ___      ___     __________      __________     __________      ____                         )"
		R"(                        |    |          |    ___    |   |   |\   |   |   |   ____   \    |   _______|   |    ____  |    |    |                        )"
		R"(                        |    |          |   |   |   |   |   | \  |   |   |  |    \   |   |  |           |   |____| |    |    |                        )"
		R"(                        |    |          |   |___|   |   |   |  \ |   |   |  |     |  |   |  |_______    |        __|    |    |                        )"
		R"(                        |    |          |   |___|   |   |   |\  \|   |   |  |     |  |   |   _______|   |   |\   \      |____|                        )"
		R"(                        |    |______    |   |   |   |   |   | \  |   |   |  |     |  |   |  |           |   | \   \      ____                         )"
		R"(                        |           |   |   |   |   |   |   |  \ |   |   |  |____/   |   |  |_______    |   |  \   \    |    |                        )"
		R"(                        |___________|   |___|   |___|   |___|   \|___|   |__________/    |__________|   |___|   \___\   |____|                        )"
		R"(                                                                                                                                                      )"
		R"(                                                              __   __  ___    __        __                                                            )"
		R"(                                                             /  \ |__|  |  | /  \ |\ | /__'                                                           )"
		R"(                                                             \__/ |     |  | \__/ | \| .__/                                                           )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                __   __             __                                                                )"
		R"(                                                               /__' /  \ |  | |\ | |  \                                                               )"
		R"(                                                               .__/ \__/ \__/ | \| |__/                                                               )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                        __                             __   ___  ___                                                  )"
		R"(                                                       /  \ |\ |                      /  \ |__  |__                                                   )"
		R"(                                                       \__/ | \|                      \__/ |    |                                                     )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                   __        __                                                                       )"
		R"(                                                                  |__|  /\  /  ` |__/                                                                 )"
		R"(                                                                  |__| /~~\ \__, |  \                                                                 )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
		R"(                                                                                                                                                      )"
	};

	// Variables

	int menuSelection = 0;
	int optionsSelection = 0;
};

/// <summary>
/// This struct contains the variables that are used during runtim of the game, they are stored here in order to tidy up the game class a bit and make them more maintainable
/// </summary>
struct RunTime
{
	// Variables
	bool exitGame = false;
	float runTime = 0.0f;
	bool playAgain = false;
};

#endif // !GAME_OBJECTS_H

