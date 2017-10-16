//-----------------------------------------------------------------------------
// File: CSinkFleetMain.cpp
//
// Function: main()
//-----------------------------------------------------------------------------

#include <iostream>
#include <cstddef>
#include "safeio.h"
#include "CSinkTheFleet.h"

const int NO_WINNER = -9999;

using namespace std;

//-----------------------------------------------------------------------------
// Function:		main()
// Title:			Play SinkTheFleet!
// Description:	Runs the Sink the Fleet Game
//						
// Programmer:		Thurman Gillespy
// 
// Date:				3/9/16
//
// Version:			1.0
// 
// Environment:	Hardware: i3 
//						Software: OS: Windows 7; 
//						Compiles under Microsoft Visual C++ 2013
//
// Input:		accepts user input from console for game parameters
//
// Output:		game grid and text info displayed on console
//
// Calls:		CSinkTheFleet class
//						constructor
//						play() method
//						heaker() method
//						endbox() method
//					safeChoice
//
// Called By:	n/a
//
// Parameters:	void
// 
// Returns:		int -- EXIT_SUCCESS upon successful completion
//
// History Log: 
//				1/9/16 TG version 1.0
//   
//-----------------------------------------------------------------------------
int main(void)
{
	using namespace P4_CSinkFleet;

	char gridSize = 0;
	char again = 'N';

	do
	{
		gridSize = safeChoice("Which size grid to you want to use?", 'S', 'L');

		short winner = NO_WINNER;
		while (winner == NO_WINNER)
		{
			CSinkTheFleet game(gridSize);
			// show header
			game.header();
			// play game until a winner
			winner = game.play();
			// announce winner
			game.endbox(winner);
			getchar();
		}
		// game falls out of scope, calling destructor
		system("cls");
		again = safeChoice("Play again?", 'Y', 'N');
		system("cls");

	} while (again == 'Y');
    
    return EXIT_SUCCESS;
}