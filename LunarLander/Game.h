/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File: Game.h
// Author: Joshua L Riches
// Date Created: December 18th (rough estimate based on first push to github)
// Brief: this contains the definitions for the main game loop
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GAME_H
#define GAME_H

// Includes
#include <Windows.h>
#include "GameObjects.h"

/// <summary>
/// This class contains the definitions for the functions and the game console window
/// </summary>
class Game
{
public:
	// Functions: these are the definitions for the functions that will be used in the main game loop
	void Initialise();
	void Update(float deltaTime);
	void Draw();
	void AddScore();
	bool GetQuit();
	void ScoreReset();
	int RandIntLength();
	int RandIntHeight();
	void FuelPickup();
	void LevelWrap();
	void PlayAudio();

private:
	// ENUMS
	// These are the different game states that the game loop can be in, they are the scenes of the game
	enum GAME_STATE
	{
		SPLASH,
		MENU,
		PLAY,
		OPTIONS,
	};

	// Console Variables
	// Window size coordinates, be sure to start at zero
	SMALL_RECT windowSize{ 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };
	// A COORD struct for specifying the console's screen buffer dimensions
	COORD bufferSize = { SCREEN_WIDTH, SCREEN_HEIGHT };
	// Setting up different variables for passing to WriteConsoleOutput
	COORD characterBufferSize = { SCREEN_WIDTH, SCREEN_HEIGHT };
	COORD characterPosition = { 0,0 };
	SMALL_RECT consoleWriteArea = { 0,0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };
	// A CHAR_INFO structure containing data about our frame
	CHAR_INFO consoleBuffer[SCREEN_WIDTH * SCREEN_HEIGHT];
	// Initialise handles
	HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE rHnd = GetStdHandle(STD_INPUT_HANDLE);

	// Game Variables
	GAME_STATE currentGameState = SPLASH;
	// The following relate to the structs within GameObjects.h, it allows other scripts to easily reference those structs
	Background background;
	Player player;
	Explosion explosion;
	Fuel fuel;
	Menu menu;
	RunTime gameSequence;
};

#endif // !GAME_H
