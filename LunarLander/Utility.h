/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File: Utility.h
// Author: Joshua L Riches
// Date Created: December 18th (rough estimate based on first push to github)
// Brief: This contains the utility function for the lunar lander game, the functions that are used frequently
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef UTILITY_H
#define UTILITY_H

#include <Windows.h>
#include <string>
#include "Constants.h"

/// <summary>
/// This will prevent a integer value from going above or below a specified limit
/// </summary>
/// <param name="intToClamp"> Integer to clamp </param>
/// <param name="lowerLimit"> Lowest value it can become </param>
/// <param name="upperLimit"> Highest value it can become </param>
/// <returns></returns>
static int ClampInt(int intToClamp, int lowerLimit, int upperLimit)
{
	if (intToClamp <= lowerLimit)
	{
		return lowerLimit;
	}
	else if (intToClamp >= upperLimit)
	{
		return upperLimit;
	}
	else
	{
		return intToClamp;
	}
}

/// <summary>
/// This will prevent a float value from going above or below a specified limit
/// </summary>
/// <param name="floatToClamp"> The value you want to clamp </param>
/// <param name="lowerLimit"> Lowest value it can become </param>
/// <param name="upperLimit"> Highest value it can become </param>
/// <returns></returns>
static float ClampFloat(float floatToClamp, float lowerLimit, float upperLimit)
{
	return floatToClamp <= lowerLimit ? lowerLimit : floatToClamp >= upperLimit ? upperLimit : floatToClamp;
}

/// <summary>
/// This will display an image made up of ascii characters to the buffer for the program
/// </summary>
/// <param name="consoleBuffer"> The buffer for the program </param>
/// <param name="charsToPrint"> This is the ascii 'sprite' that is to be displayed </param>
/// <param name="coloursToPrint"> This is the colours for the ascii characters in the 'sprite' </param>
/// <param name="ImageHeight"> Height of the 'sprite' </param>
/// <param name="imageWidth"> Width of the 'sprite' </param>
/// <param name="imageXPos"> Position on the x axis at which the 'sprite' will be displayed </param>
/// <param name="imageYPos"> Position on the x axis at which the 'sprite' will be displayed </param>
static void WriteImageToBuffer(CHAR_INFO* consoleBuffer, const char* charsToPrint, const int coloursToPrint[], const int ImageHeight, const int imageWidth, int imageXPos, int imageYPos)
{
	for (int y = 0; y < ImageHeight; y++)
	{
		for (int x = 0; x < imageWidth; x++)
		{
			// Prints the characters of the 'sprite'
			consoleBuffer[(imageXPos + x) + SCREEN_WIDTH * (imageYPos + y)].Char.AsciiChar = charsToPrint[x + imageWidth * y];

			if (coloursToPrint)
			{
				// Sets the colours of the characters
				consoleBuffer[(imageXPos + x) + SCREEN_WIDTH * (imageYPos + y)].Attributes = coloursToPrint[x + imageWidth * y];
			}
			else
			{
				// Defaults to colour of white if no colour was specified as a parameter
				consoleBuffer[(imageXPos + x) + SCREEN_WIDTH * (imageYPos + y)].Attributes = 7;
			}
		}
	}
}

/// <summary>
/// This function will remove any characters displayed on the screen so that previous frames are not getting shown as 'echoes'
/// </summary>
/// <param name="consoleBuffer"> Takes the buffer for the screen as a parameter </param>
static void ClearScreen(CHAR_INFO* consoleBuffer)
{
	for (int i = 0; i < (SCREEN_WIDTH * SCREEN_HEIGHT); i++)
	{
		// Sets all the characters as being nothing
		consoleBuffer[i].Char.AsciiChar = 0;
		consoleBuffer[i].Attributes = 0;
	}
}

/// <summary>
/// This will print a string of text to a specified location within the buffer on the screen
/// </summary>
/// <param name="consoleBuffer"> The buffer for the running program </param>
/// <param name="stringToPrint"> The contents of what is to be displayed </param>
/// <param name="textXPos"> Position on the x axis that the text will display </param>
/// <param name="textYPos"> Position on the y axis that the text will display </param>
static void WriteTextToBuffer(CHAR_INFO* consoleBuffer, std::string stringToPrint, int textXPos, int textYPos)
{
	for (int x = 0; x < stringToPrint.length(); x++)
	{
		consoleBuffer[(textXPos + x) + SCREEN_WIDTH * textYPos].Char.AsciiChar = stringToPrint[x]; // Prints the string
		consoleBuffer[(textXPos + x) + SCREEN_WIDTH * textYPos].Attributes = 0xF; // Sets the colour as white
	}
}


#endif // !UTILITY_H

