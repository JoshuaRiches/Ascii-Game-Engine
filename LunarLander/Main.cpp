/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File: Main.cpp
// Author: Joshua L Riches
// Date Created: Novemeber 20th (rough estimate based on first push to github)
// Brief: this file is the main class for the lunar lander game, it is the first thing that will get exectuted,
// and it triggers everything else
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES
#include <Windows.h>
#include <chrono>
#include "GameObjects.h"
#include "Game.h"

// TYPEDEFS: this defines new names for these values, making it easier to reference them
typedef std::chrono::steady_clock::time_point Time;
typedef std::chrono::high_resolution_clock HiResClock;
typedef std::chrono::duration<float> TimeDiff;

/// <summary>
/// This is the main class that will run when the program is started, it is what triggers everything else to execute at the right time.
/// </summary>
/// <returns> As there is no specific return needed from main, it will return 0 </returns>
int main()
{
	Game gameInstance;

	// Initialise console window
	gameInstance.Initialise();

	// Initialise variables
	float deltaTime = 0.0f;
	Time currentFrameTime = HiResClock::now();
	Time previousFrameTime = HiResClock::now();

	bool exitGame = false;
	// Main game loop
	// This will repeat the game loop until the value of exit game changes
	while (!exitGame)
	{
		// Calculate our delta time (time since last frame)
		currentFrameTime = HiResClock::now();
		TimeDiff diff = currentFrameTime - previousFrameTime;
		deltaTime = diff.count();

		if (deltaTime >= (1.0f / FRAME_RATE))
		{
			// Update our application
			gameInstance.Update(deltaTime);
			// Cache the timestamp of this frame
			previousFrameTime = currentFrameTime;
		}
		gameInstance.Draw();
		
		// This retrieves the value of exit game within the game class and sets it as the exit game variable here,
		// this enable the game to be quit
		exitGame = gameInstance.GetQuit();
	}
	return 0;
}