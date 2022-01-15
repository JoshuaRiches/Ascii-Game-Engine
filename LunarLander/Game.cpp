/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File: Game.cpp
// Author: Joshua L Riches
// Date Created: December 18th (rough estimate based on first push to github)
// Brief: this contains the functions of the main game loop itself. This is the game and its processes.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// This classes header
#include "Game.h"
// Includes
#include "Utility.h"
#include "Constants.h"
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <Windows.h>

/// <summary>
/// This function will initialise what is needed for the game upon startup
/// </summary>
void Game::Initialise()
{
	// Set the console title
	SetConsoleTitle(L"Lunar Lander");

	// Set screen buffer size
	SetConsoleScreenBufferSize(wHnd, bufferSize);
	// Set the window size
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);

	// When you first load up the game it will open the file that stores the state of whenever sound is on or off
	// And sets the stored value to be 1 as i want sound to be on by default when you open the game.
	std::ofstream soundStateTxt;
	soundStateTxt.open("SoundState.txt");
	soundStateTxt << std::to_string(1);
	soundStateTxt.close();
}

/// <summary>
/// This function is called every frame, it is the game loop itself
/// </summary>
/// <param name="deltaTime"> Passed in is the change in time since the last frame </param>
void Game::Update(float deltaTime)
{
	// This checks the current state/scene the game is on
	switch (currentGameState)
	{
		/*
			This is the splash screen game state, it will display the splash screen sprite for 3 seconds and will then change the game state to be the menu
		*/
		case SPLASH:
		{
			// Create new splash screen
			static Splash splash;

			// Calculate current splash duration
			splash.duration += deltaTime;

			if (splash.duration < 3.0f)
			{
				// Draw splash image
				WriteImageToBuffer(consoleBuffer, splash.CHARACTERS, splash.COLOURS, splash.HEIGHT, splash.WIDTH,
					(SCREEN_WIDTH / 2) - (splash.WIDTH / 2), (SCREEN_HEIGHT / 2) - (splash.HEIGHT / 2));
			}
			else
			{
				// Move to menu state and reset splash duration
				splash.duration = 0.0f;
				currentGameState = MENU;
			}
			break;
		}

		/*
			This is the menu game state, it displays the different options that the player can pick and allows them to select them
		*/
		case MENU:
		{
			// Sets the timer to be 0 when not in game as i dont want it to be counting up when the player isnt in game
			gameSequence.runTime = 0.0f;

			// This will set the sound to null as i have a bug where if the sound is playing when you land or crash, then it wont stop
			PlaySound(NULL, 0, 0);

			// Clear any previous images
			ClearScreen(consoleBuffer);
			// Draw the menu to the buffer
			WriteImageToBuffer(consoleBuffer, menu.CHARACTERS, nullptr, SCREEN_HEIGHT, SCREEN_WIDTH, 0, 0);

			// Opens the highscore file and saves it to an integer variable
			int score;
			std::ifstream highScoreTxt("HighScore.txt", std::ios::in);
			highScoreTxt >> score;

			// this is a variable that will enable the highscore text to blink (in proper retro fashion)
			static float blinkTimer = 0.0f;
			blinkTimer += deltaTime; // increment blink timer by delta time

			// if blink timer is more than 0.5 or less than 2, display the highscore text
			if (blinkTimer >= 0.5f && blinkTimer < 2.0f)
			{
				WriteTextToBuffer(consoleBuffer, "H I G H  S C O R E : " + std::to_string(score), 65, 13);
			}
			//else display that nothing, this creates a blinking animation for the highscore text
			else if(blinkTimer > 2.0f)
			{
				WriteTextToBuffer(consoleBuffer, "", 65, 13);
				blinkTimer = 0.0f;
			}
			highScoreTxt.close();
			
			// This displays the selection sprite at the position correlating to the currently selected option
			if (menu.menuSelection == 0)
			{
				// draw select icon to the position for having play selected
				WriteImageToBuffer(consoleBuffer, player.CHARACTERS_DEFAULT, player.COLOURS_DEFAULT, player.HEIGHT, player.WIDTH, 60, 15);
			}
			else if (menu.menuSelection == 1)
			{
				// draw select icon to the position for having options selected
				WriteImageToBuffer(consoleBuffer, player.CHARACTERS_DEFAULT, player.COLOURS_DEFAULT, player.HEIGHT, player.WIDTH, 55, 21);
			}
			else if (menu.menuSelection == 2)
			{
				// draw select icon to the position for having quit selected
				WriteImageToBuffer(consoleBuffer, player.CHARACTERS_DEFAULT, player.COLOURS_DEFAULT, player.HEIGHT, player.WIDTH, 62, 27);
			}

			// Take the input of either w or s, this will then move the select icon accordingly and change the value for which option is selected
			if (GetAsyncKeyState(KEY_S) && menu.menuSelection == 0)
			{
				// if they currently have play selected and press s, move the icon to be next to options and change the menu selection
				WriteImageToBuffer(consoleBuffer, player.CHARACTERS_DEFAULT, player.COLOURS_DEFAULT, player.HEIGHT, player.WIDTH, 55, 21);
				menu.menuSelection = 1;
			}
			else if (GetAsyncKeyState(KEY_S) && menu.menuSelection == 1)
			{
				// if they currently have options selected and press s, move the icon to be next to quit and change the menu selection
				WriteImageToBuffer(consoleBuffer, player.CHARACTERS_DEFAULT, player.COLOURS_DEFAULT, player.HEIGHT, player.WIDTH, 62, 27);
				menu.menuSelection = 2;
			}
			else if (GetAsyncKeyState(KEY_S) && menu.menuSelection == 2)
			{
				// if they currently have quit selected and press s, move the icon to be next to play so that it loops back to the top and change the menu selection
				WriteImageToBuffer(consoleBuffer, player.CHARACTERS_DEFAULT, player.COLOURS_DEFAULT, player.HEIGHT, player.WIDTH, 60, 15);
				menu.menuSelection = 0;
			}

			if (GetAsyncKeyState(KEY_W) && menu.menuSelection == 0)
			{
				// if they currently have play selected and press w, move the icon to be next to quit so that it loops back to the bottom and change the menu selection
				WriteImageToBuffer(consoleBuffer, player.CHARACTERS_DEFAULT, player.COLOURS_DEFAULT, player.HEIGHT, player.WIDTH, 62, 27);
				menu.menuSelection = 2;
			}
			else if (GetAsyncKeyState(KEY_W) && menu.menuSelection == 1)
			{
				// if they currently have options selected and press w, move the icon next to play and change menu selection
				WriteImageToBuffer(consoleBuffer, player.CHARACTERS_DEFAULT, player.COLOURS_DEFAULT, player.HEIGHT, player.WIDTH, 60, 15);
				menu.menuSelection = 0;
			}
			else if (GetAsyncKeyState(KEY_W) && menu.menuSelection == 2)
			{
				// if they currently have quit selected and press w, move the icon next to options and change menu selection
				WriteImageToBuffer(consoleBuffer, player.CHARACTERS_DEFAULT, player.COLOURS_DEFAULT, player.HEIGHT, player.WIDTH, 55, 21);
				menu.menuSelection = 1;
			}
			
			// when the player presses enter on the menu, it will get what option is currently selected and react appropriately
			if (GetAsyncKeyState(KEY_ENTER) && menu.menuSelection == 0)
			{
				// if play is selected then load the play game state
				currentGameState = PLAY;
			}
			else if (GetAsyncKeyState(KEY_ENTER) && menu.menuSelection == 1)
			{
				// if options is selected then load the options game state
				currentGameState = OPTIONS;
			}
			else if (GetAsyncKeyState(KEY_ENTER) && menu.menuSelection == 2)
			{
				// if quit is selected then the game will quite when enter is pressed
				gameSequence.exitGame = true;
			}

			break;
		}

		/*
			This is the game state for the options screen, on here the player can turn sound on or off and return to the main menu
		*/
		case OPTIONS:
		{
			// Sets the timer to be 0 when not in game as i dont want it to be counting up when the player isnt in game
			gameSequence.runTime = 0.0f;

			// Clear any previous images
			ClearScreen(consoleBuffer);
			// Draw the options screen to the buffer
			WriteImageToBuffer(consoleBuffer, menu.CHARACTERS_OPTIONS, nullptr, SCREEN_HEIGHT, SCREEN_WIDTH, 0, 0);

			// Display select option next to currently selected option
			if (menu.optionsSelection == 0)
			{
				// position for sound on
				WriteImageToBuffer(consoleBuffer, player.CHARACTERS_DEFAULT, player.COLOURS_DEFAULT, player.HEIGHT, player.WIDTH, 49, 22);
			}
			else if (menu.optionsSelection == 1)
			{
				// position for sound off
				WriteImageToBuffer(consoleBuffer, player.CHARACTERS_DEFAULT, player.COLOURS_DEFAULT, player.HEIGHT, player.WIDTH, 80, 22);
			}
			else if (menu.optionsSelection == 2)
			{
				// position for sound back
				WriteImageToBuffer(consoleBuffer, player.CHARACTERS_DEFAULT, player.COLOURS_DEFAULT, player.HEIGHT, player.WIDTH, 60, 32);
			}

			// Take the input of a or d and move the icon and change selection appropriately
			if (GetAsyncKeyState(KEY_D) && menu.optionsSelection == 0)
			{
				// if selected sound on, move icon to sound off and change selection
				WriteImageToBuffer(consoleBuffer, player.CHARACTERS_DEFAULT, player.COLOURS_DEFAULT, player.HEIGHT, player.WIDTH, 80, 22);
				menu.optionsSelection = 1;
			}
			else if (GetAsyncKeyState(KEY_D) && menu.optionsSelection == 1)
			{
				// if selected sound off, move icon to back and change selection
				WriteImageToBuffer(consoleBuffer, player.CHARACTERS_DEFAULT, player.COLOURS_DEFAULT, player.HEIGHT, player.WIDTH, 60, 32);
				menu.optionsSelection = 2;
			}
			else if (GetAsyncKeyState(KEY_D) && menu.optionsSelection == 2)
			{
				// if selected sound back, move icon to sound on and change selection
				WriteImageToBuffer(consoleBuffer, player.CHARACTERS_DEFAULT, player.COLOURS_DEFAULT, player.HEIGHT, player.WIDTH, 49, 22);
				menu.optionsSelection = 0;
			}

			if (GetAsyncKeyState(KEY_A) && menu.optionsSelection == 0)
			{
				// if selected sound on, move icon to back and change selection
				WriteImageToBuffer(consoleBuffer, player.CHARACTERS_DEFAULT, player.COLOURS_DEFAULT, player.HEIGHT, player.WIDTH, 60, 32);
				menu.optionsSelection = 2;
			}
			else if (GetAsyncKeyState(KEY_A) && menu.optionsSelection == 1)
			{
				// if selected sound off, move icon to sound on and change selection
				WriteImageToBuffer(consoleBuffer, player.CHARACTERS_DEFAULT, player.COLOURS_DEFAULT, player.HEIGHT, player.WIDTH, 49, 22);
				menu.optionsSelection = 0;
			}
			else if (GetAsyncKeyState(KEY_A) && menu.optionsSelection == 2)
			{
				// if selected back, move icon to sound off and change selection
				WriteImageToBuffer(consoleBuffer, player.CHARACTERS_DEFAULT, player.COLOURS_DEFAULT, player.HEIGHT, player.WIDTH, 80, 22);
				menu.optionsSelection = 1;
			}

			if (GetAsyncKeyState(KEY_ENTER) && menu.optionsSelection == 0)
			{
				//if they have sound on selected and press enter, replace the value in sound state file with the value of 1
				std::ofstream soundStateTxt;
				soundStateTxt.open("SoundState.txt");
				soundStateTxt << std::to_string(1);
				soundStateTxt.close();
			}
			else if (GetAsyncKeyState(KEY_ENTER) && menu.optionsSelection == 1)
			{
				//if they have sound off selected and press enter, replace the value in sound state file with the value of 0
				std::ofstream soundStateTxt;
				soundStateTxt.open("SoundState.txt");
				soundStateTxt << std::to_string(0);
				soundStateTxt.close();
			}
			else if (GetAsyncKeyState(KEY_ENTER) && menu.optionsSelection == 2)
			{
				//if they have back selected and press enter, load the game menu state
				currentGameState = MENU;
			}
			break;
		}

		/*
			This is the game state for the play scene, this is where the actual gameplay happens
		*/
		case PLAY:
		{
			if (!player.hasCrashed && !player.hasLanded)
			{
				// Increments run time, this will count how long the player has been playing for
				// will reset state of moving left and right each frame
				gameSequence.runTime += deltaTime;
				player.isMovingLeft = false;
				player.isMovingRight = false;
			}

			if (GetAsyncKeyState(KEY_ESC))
			{
				//exit the game if they press esc
				gameSequence.exitGame = true;
			}

			if (GetAsyncKeyState(KEY_ENTER) && (player.hasCrashed || player.hasLanded))
			{
				if (gameSequence.playAgain)
				{
					//if they landed they can play again, this will then reset the player and reset fuel pickup and audio
					player.Reset();
					gameSequence.playAgain = false;
					fuel.fuelExists = false;
					PlayAudio(); //this is called here so that it updates the fact that audio shouldnt be playing now
				}
				else
				{
					// if they crash then it will reset everything and load the menu game state
					player.Reset();
					player.Refill();
					ScoreReset();
					fuel.fuelExists = false;
					PlayAudio(); //this is called here so that it updates the fact that audio shouldnt be playing now
					menu.menuSelection = 0;
					currentGameState = MENU;
				}
			}

			if (!player.hasLanded && !player.hasCrashed)
			{
				if (GetAsyncKeyState(KEY_W) && player.fuel > 0.0f)
				{
					// the lander will accelerate upwards if they have fuel
					player.isAccelerating = true;
					// spend fuel
					player.fuel -= FUEL_CONSUMPTION_RATE;
				}
				if (GetAsyncKeyState(KEY_A) && player.fuel > 0.0f)
				{
					//move left, use fuel, set moving left as true
					player.xPos--;
					player.fuel -= FUEL_CONSUMPTION_RATE;
					player.isMovingLeft = true;

				}
				if (GetAsyncKeyState(KEY_D) && player.fuel > 0.0f)
				{
					// move right, use fuel, set moving right as true
					player.xPos++;
					player.fuel -= FUEL_CONSUMPTION_RATE;
					player.isMovingRight = true;
				}
				// Will play thruster sound if the lander is moving
				PlayAudio();

				// sets the players acceleration
				if (player.isAccelerating)
				{
					// This is actually velocity as velocity is acceleration * time but i kept as this cos i didnt want to screw other things up
					player.acceleration += (ACCELERATION_RATE * deltaTime);
				}
				else
				{
					player.acceleration -= (DECELERATION_RATE * deltaTime);
				}

				// Reset acceleration flag
				player.isAccelerating = false;

				// Clamp our acceleration
				player.acceleration = ClampFloat(player.acceleration, 0.0f, 1.5f);

				if (player.acceleration >= 0.5f)
				{
					//increment y position of lander (it starts at 0 at top so - is increasing height)
					player.yPos--;
				}
				else if (player.acceleration < 0.5f)
				{
					//decrement y position of lander
					player.yPos++;
				}

				// Clamp the position of the lander so it cant go beyond the borders
				player.xPos = ClampInt(player.xPos, 0, (SCREEN_WIDTH - player.WIDTH));
				LevelWrap(); //call the level wrap function
				player.yPos = ClampInt(player.yPos, 0, (SCREEN_HEIGHT - player.HEIGHT));

				// Get the two characters under the landing gear
				char bottomLeftChar = background.CHARACTERS[(player.xPos + (player.WIDTH - 3)) +SCREEN_WIDTH * (player.yPos + (player.HEIGHT - 1))];
				char bottomRightChar = background.CHARACTERS[(player.xPos + (player.WIDTH - 2)) + SCREEN_WIDTH * (player.yPos + (player.HEIGHT - 1))];

				// Landed?
				if (bottomLeftChar == '_' && bottomRightChar == '_' && player.velocityY > -0.2f)
				{
					// if it is a platform under the lander and they arent going too fast then tehy have landed and it calls addscore()
					player.hasLanded = true;
					AddScore();
				}
				else if (bottomLeftChar != ' ' && bottomLeftChar != '*' && bottomLeftChar != '.' || bottomRightChar != ' ' && bottomRightChar != '*' && bottomRightChar != '.')
				{
					//otherwise they have crashed
					player.hasCrashed = true;
				}
			}

			// Clear the previous 'frame' before we start build the next one
			ClearScreen(consoleBuffer);

			// Draw the background image
			WriteImageToBuffer(consoleBuffer, background.CHARACTERS, nullptr, SCREEN_HEIGHT, SCREEN_WIDTH, 0, 0);

			FuelPickup(); //call the fuel pickup function which will check if the player can pickup the fuel

			if (!fuel.fuelExists)
			{
				//if their isnt a fuel pickup on the map then generate random coordinates and place it there, set it as existing now
				fuel.fuelX = RandIntLength();
				fuel.fuelY = RandIntHeight();
				fuel.fuelExists = true;
			}

			if (!player.fuelCollected)
			{
				//if the fuel hasnt been collected, continue to draw it each for each frame
				WriteImageToBuffer(consoleBuffer, fuel.CHARACTERS, fuel.COLOURS, fuel.HEIGHT, fuel.WIDTH, fuel.fuelX, fuel.fuelY);
			}
			
			if (player.hasCrashed)
			{
				//if the player has crashed then display the explosion animation
				static float explosionFlashTimer = 0.0f;

				explosionFlashTimer += deltaTime;
				
				if (explosionFlashTimer >= 0.5f && explosionFlashTimer < 1.0f)
				{
					// Draw first frame of explosion
					WriteImageToBuffer(consoleBuffer, explosion.CHARACTERS_SMALL, explosion.COLOURS, explosion.HEIGHT, explosion.WIDTH, player.xPos, player.yPos);
					
				}
				else if (explosionFlashTimer >= 1.0f)
				{
					// Draw second frame of explosion
					WriteImageToBuffer(consoleBuffer, explosion.CHARACTERS_BIG, explosion.COLOURS, explosion.HEIGHT, explosion.WIDTH, player.xPos, player.yPos);
					explosionFlashTimer = 0.0f;
				}
				else
				{
					// Draw empty Characters
					WriteImageToBuffer(consoleBuffer, explosion.EMPTY_CHARACTERS, explosion.COLOURS, explosion.HEIGHT, explosion.WIDTH, player.xPos, player.yPos);
				}

				// Write the text to the screen to tell player what to do
				WriteTextToBuffer(consoleBuffer, "COMMAND, MISSION HAS FAILED!", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
				WriteTextToBuffer(consoleBuffer, "Press 'Enter' to return to menu...", SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 1);
			}
			else if(player.hasLanded)
			{
				// Draw player image
				WriteImageToBuffer(consoleBuffer, player.CHARACTERS_DEFAULT, player.COLOURS_DEFAULT, player.HEIGHT, player.WIDTH, player.xPos, player.yPos);

				// Write the text to the screen to tell the player what to do
				WriteTextToBuffer(consoleBuffer, "COMMAND, WE ARE IN THE CLEAR!", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
				WriteTextToBuffer(consoleBuffer, "Press 'Enter' to continue", SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 1);

				gameSequence.playAgain = true; //set play again as true because they have landed succesfully
			}

			//displays the different player sprites
			else if(!player.isMovingLeft && !player.isMovingRight)
			{
				// Draw default sprite if not moving left or right
				WriteImageToBuffer(consoleBuffer, player.CHARACTERS_DEFAULT, player.COLOURS_DEFAULT, player.HEIGHT, player.WIDTH, player.xPos, player.yPos);
			}
			else if (player.isMovingLeft)
			{
				// Draw the sprite for moving left if they are moving left
				WriteImageToBuffer(consoleBuffer, player.CHARACTERS_LEFT, player.COLOURS_LEFT, player.HEIGHT, player.WIDTH, player.xPos, player.yPos);
			}
			else if (player.isMovingRight)
			{
				// Draw the sprite for moving right if they are moving right
				WriteImageToBuffer(consoleBuffer, player.CHARACTERS_RIGHT, player.COLOURS_RIGHT, player.HEIGHT, player.WIDTH, player.xPos, player.yPos);
			}
			
			if (player.acceleration < 0.5)
			{
				// as the lander will be going down, this changes the value to be a negative in order to display that the velocity is downwards
				// the value of -0.5f is used here as it is the maximum negative velocity that can be achieved
				player.velocityY = -0.5f + player.acceleration;
			}
			else
			{
				// as the lander will be going up, the acceleration is displayed as the number minus the range in which it goes down
				// This is because in real life the lander would not move up or down if velocity is 0 so im trying to establish a point at which it is determined between positive and negative
				player.velocityY = player.acceleration - 0.5f;
			}

			// Draw UI text
			WriteTextToBuffer(consoleBuffer, "SCORE: " + std::to_string(player.currentScore), 1, 0); // Display their current score	
			WriteTextToBuffer(consoleBuffer, "TIME: " + std::to_string(gameSequence.runTime), 1, 1); // Display how long they've been playing
			WriteTextToBuffer(consoleBuffer, "Y VELOCITY: " + std::to_string(player.velocityY), 1, 2); // Display their vertical velocity
			WriteTextToBuffer(consoleBuffer, "FUEL: " + std::to_string(player.fuel), 1, 3); // Display their fuel level
			WriteTextToBuffer(consoleBuffer, "ALTITUDE: " + std::to_string(SCREEN_HEIGHT - player.yPos) + "M", SCREEN_WIDTH - 14, 0); // Display their current alitude at top right of screen
			break;
		}

		default:
		{
			break;
		}
	}
}

/// <summary>
/// This function will kick the draw in the buffer
/// </summary>
void Game::Draw()
{
	WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
}

/// <summary>
/// This function will check for a number character under the platform that the lander lands on and will multiply the base score by that number
/// </summary>
void Game::AddScore()
{
	// Get all the characters for the left of the platform
	char bottomLeftChar = background.CHARACTERS[player.xPos + SCREEN_WIDTH * (player.yPos + (player.HEIGHT))];
	char bottomLeftChar1 = background.CHARACTERS[player.xPos + 1 + SCREEN_WIDTH * (player.yPos + (player.HEIGHT))];
	char bottomLeftChar2 = background.CHARACTERS[player.xPos + 2 +SCREEN_WIDTH * (player.yPos + (player.HEIGHT))];
	// Get all the characters for the right of the platform
	char bottomRightChar = background.CHARACTERS[(player.xPos + (player.WIDTH - 1)) + SCREEN_WIDTH * (player.yPos + (player.HEIGHT))];
	char bottomRightChar1 = background.CHARACTERS[(player.xPos + (player.WIDTH - 2)) + SCREEN_WIDTH * (player.yPos + (player.HEIGHT))];
	char bottomRightChar2 = background.CHARACTERS[(player.xPos + (player.WIDTH - 3)) + SCREEN_WIDTH * (player.yPos + (player.HEIGHT))];

	// If their is a '2' under the platform then the base score will be multiplied by 2 and added to current score
	if (bottomLeftChar == '2' || bottomLeftChar1 == '2' || bottomLeftChar2 == '2' || bottomRightChar == '2' || bottomRightChar1 == '2' || bottomRightChar2 == '2')
	{
		player.currentScore += BASE_SCORE * 2;
	}
	// If their is a '4' under the platform then the base score will be multiplied by 4 and added to the current score
	else if (bottomLeftChar == '4' || bottomLeftChar1 == '4' || bottomLeftChar2 == '4' || bottomRightChar == '4' || bottomRightChar1 == '4' || bottomRightChar2 == '4')
	{
		player.currentScore += BASE_SCORE * 4;
	}
}

/// <summary>
/// This function will be called when the game is over and it will check the current score against the highscore in the file
/// it will then either replace the value and clear current score, or will just clear current score if it is not a new highscore
/// </summary>
void Game::ScoreReset()
{
	bool newHighScore = false;

	// opens and reads the highscore file
	int score;
	std::ifstream highScoreTxt("HighScore.txt", std::ios::in);
	highScoreTxt >> score;

	// Compares current score with the highscore, if it is higher then it will set the boolean of new highscore as true
	if (player.currentScore > score)
	{
		newHighScore = true;
	}
	else
	{
		newHighScore = false;
	}
	highScoreTxt.close(); // closes the file

	// If their is a new highscore then the contents of the highscore file will be replaced with the current score
	if (newHighScore)
	{
		std::ofstream highScoreTxt;
		highScoreTxt.open("HighScore.txt");
		highScoreTxt << std::to_string(player.currentScore);
		highScoreTxt.close();
	}
	
	// The current score is then reset
	player.currentScore = 0;
}

/// <summary>
/// This function generates a random number for the X position of the fuel pickup
/// </summary>
/// <returns> Returns a random number </returns>
int Game::RandIntLength()
{
	int iSecret = -1;
	srand(time(NULL)); //seed the random number
	iSecret = rand() % 99 + 0; //generate the random number
	return iSecret;
}

/// <summary>
/// This function generates a random number for the Y position of the fuel pickup
/// </summary>
/// <returns> Returns a random number </returns>
int Game::RandIntHeight()
{
	int iSecret = -1;
	srand(time(NULL)); //seed the random number
	iSecret = rand() % 39 + 0; //generate the random number
	return iSecret;
}

/// <summary>
/// When called, this function will check if the player is at same position as the fuel pickup and will pickup the fuel if they are
/// </summary>
void Game::FuelPickup()
{
	if (player.xPos == fuel.fuelX && player.yPos == fuel.fuelY)
	{
		// If the player lander is in same position of the fuel then it will add fuel to the players count and set the fuel as collected.
		player.fuel += 25.0f;
		player.fuelCollected = true; // This will make it so the fuel vanishes after collection due to a check higher up in the code.
	}
}

/// <summary>
/// This function, when called, will allow the player to move off one side and appear on the other side.
/// </summary>
void Game::LevelWrap()
{
	// if the player moves off the right hand side, then they will appear on the left
	if (player.xPos == (SCREEN_WIDTH - player.WIDTH))
	{
		player.xPos = 0;
	}
	//vice versa
	else if (player.xPos == 0)
	{
		player.xPos = SCREEN_WIDTH - player.WIDTH;
	}
}

/// <summary>
/// When called this function will play the thruster sound when called, as long as the required conditions are met
/// </summary>
void Game::PlayAudio()
{
	// Opens the sound state file which contains a value that determines if sound should be on or off
	int soundState;
	std::ifstream soundStateTxt("SoundState.txt", std::ios::in);
	soundStateTxt >> soundState;

	// The following was used to get this working
	// https://stackoverflow.com/questions/21034935/playsound-in-c

	// if the player is moving and they have sound on, then play the thruster sound effect
	if ((player.isAccelerating || player.isMovingLeft || player.isMovingRight) && soundState == 1)
	{
		PlaySound(TEXT("Thruster.wav"), NULL, SND_ASYNC);
	}
	else
	{
		PlaySound(NULL, 0, 0);
	}
}

/// <summary>
/// This will return the value of the exit game variable, this is called in main so that main can get the value
/// </summary>
/// <returns> value of exitgame boolean </returns>
bool Game::GetQuit()
{
	return (gameSequence.exitGame);
}