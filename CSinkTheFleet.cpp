//-----------------------------------------------------------------------------
// File: CSinkTheFleet.cpp
//
//	functions:
//			CSinkTheFleet::CSinkTheFleet(char gridSize)
//			void CSinkTheFleet::header(void)
//			void CSinkTheFleet::endbox(short player)
//			short CSinkTheFleet::play(void)
//			
//-----------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "CSinkTheFleet.h"

using namespace std;

namespace P4_CSinkFleet
{
//-----------------------------------------------------------------------------
//	Title:         CSinkTheFleet Class
//
//	Description:   Definitions for CSinkTHeFleet methods
//
//	Programmer:    Thurman Gillespy
//   
//	Date:          3/9/16
// 
//	Version:			1.0
//   
//	Environment:	PC 
//						Software:   MS Windows 7
//						Compiles under Microsoft Visual C++.Net 2013
//
//	class CSinkTheFleet:
//
//	Properties:
//				CPlayer m_players[NUMPLAYERS] -- array of NUMPLAYERS CPlayer objects
//				char m_gridSize -- the size of the game grid,
//								stored as a char 'S' or 'L' //
//	History log:
//			3/9/2016 - tg3 completed v 1.0
//
//-----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
//	Class:         CSinkTheFleet
//	method:        CSinkTheFleet::CSinkTheFleet(char gridSize)
//	description:   constructor
//							sets m_gridSize and m_players[]
//	Parameters:		char gridSize -- game grid 'S' for samll, 'L' for large
// Called by:		main()
//	History Log:
//	               3/9/2016 tg3  completed version 1.0
//-----------------------------------------------------------------------------
	CSinkTheFleet::CSinkTheFleet(char gridSize)
	{
		m_gridSize = gridSize;
		
		m_players[0] = CPlayer(0, gridSize);
		m_players[1] = CPlayer(1, gridSize);
	}

// ----------------------------------------------------------------------------
//	Class:         CSinkTheFleet
//	method:        void CSinkTheFleet::header(void)
//	description:   displays game splash screen
//	Parameters:		none
// Called by:		main()
// Output:			displays box with game title and programmer information
//	History Log:
//	               3/9/2016 tg3  completed version 1.0
//-----------------------------------------------------------------------------
	void CSinkTheFleet::header(void)
	{
		const string empty;
		const string sink("SINK THE FLEET!");
		const string better("Now with OOP!");
		const string name1("Thurman Gillespy, Jason Duncan, Jason Guatama");
		const string name2("David Landry and Matt Schroder");
		const string by("Edmonds Community College CS 132");
		boxTop(cout, BOXWIDTH);
		boxLine(cout, empty, BOXWIDTH);
		boxLine(cout, sink, BOXWIDTH, 'C');
		boxLine(cout, better, BOXWIDTH, 'C');
		boxLine(cout, empty, BOXWIDTH);
		boxLine(cout, by, BOXWIDTH, 'C');
		boxLine(cout, empty, BOXWIDTH);
		boxLine(cout, name1, BOXWIDTH, 'C');
		boxLine(cout, name2, BOXWIDTH, 'C');
		boxLine(cout, empty, BOXWIDTH);
		boxBottom(cout, BOXWIDTH);
	}

// ----------------------------------------------------------------------------
//	Class:         CSinkTheFleet
//	method:        void CSinkTheFleet::endbox(short player)
//	description:   displays game winner
//	Parameters:		short player -- who won the game
// Called by:		main()
// Output:			displays box with winner informaation on the console
//	History Log:
//	               3/9/2016 tg3  completed version 1.0
//-----------------------------------------------------------------------------
	void CSinkTheFleet::endbox(short player)
	{
		const string empty;
		ostringstream msg;
		msg << "Congratulations player " << player + 1 << "!";
		boxTop(cout, BOXWIDTH);
		boxLine(cout, empty, BOXWIDTH);
		boxLine(cout, msg.str(), BOXWIDTH, 'C');
		boxLine(cout, empty, BOXWIDTH);
		boxBottom(cout, BOXWIDTH);
	}

// ----------------------------------------------------------------------------
//	Class:         CSinkTheFleet
//	method:        short CSinkTheFleet::play(void)
//	description:   plays the SinkTheFleet game
//	Parameters:		none
// Called by:		main()
// Returns:			short -- the winning player
// Output:			game grid and text for game to console
//	History Log:
//	               3/9/2016 tg3  completed version 1.0
//-----------------------------------------------------------------------------
	short CSinkTheFleet::play(void)
	{
		char choice = 0;
		string filename;
		short whichPlayer = -1;
		bool reshoot = false;
		bool gameOver = false;
		bool fileLoaded = false;
		char gridSize = m_gridSize;
		Ship shotStatus = NOSHIP;
		CPlayer *curPlayer = nullptr;
		CPlayer *curTarget = nullptr;

		// start play - ask each player how to set up game
		for (whichPlayer = 0; whichPlayer < NUMPLAYERS; whichPlayer++)
		{
			curPlayer = &m_players[whichPlayer];
			do {
				cout << "Player " << whichPlayer + 1 << ". ";
				choice = safeChoice(
					"Would you like to read starting grid from a file?", 'Y', 'N');
				if (choice == 'Y')
				{
					cout << "Enter file name: ";
					cin >> filename;
					// load the file. If failure, repeat the loop
					if (curPlayer->getGrid(filename + ".shp") == false)
					{
						choice = 'N';
						continue;
					}
				}
				else
				{
					// let the user enter the coordinates
					curPlayer->setShips(); 
				}
				// print grid, ask user if ok
				curPlayer->printGrid(cout, 0);
				choice = safeChoice("OK?", 'Y', 'N');
				if (choice == 'N')
				{
					// need to clear gameGrid[0] before reentering ship coordinates
					curPlayer->clearGrid(); 
				}
				system("cls");
			} while (choice == 'N');
		} // end for

		system("cls");
		header();
		cout << "Press <Enter> to continue the battle!" << endl;
		cin.ignore(BUFFER_SIZE, '\n');

		// games are set - time to shart shooting
		while (!gameOver)
		{
			// give each player a turn
			for (whichPlayer = 0; whichPlayer < NUMPLAYERS && gameOver == false;
					whichPlayer++)
			{
				curPlayer = &m_players[whichPlayer];
				curTarget = &m_players[whichPlayer == 0 ? 1: 0]; // the other guy
				// but keep giving the same player a turn if gets a HIT
				do // while reShoot == true
				{
					curPlayer->printGrid(cout, 1); 

					if (reshoot == true)
						cout << "Player " << whichPlayer + 1 <<
						" shoots again! Enter coordinates for firing:" << endl;
					else
						cout << "Player " << whichPlayer + 1 <<
						". Enter coordinates for firing:" << endl;

					// get shot coordinates, and check for a HIT
					CCell cell;
					cell.inputCoordinates(cin, gridSize);
					// check if user already fired a shot at these coord
					shotStatus = curPlayer->getHitStatus(cell);
					if (shotStatus == HIT || shotStatus == MISSED)
					{
						cout << "You have already fired a shot "
							"at those coordinates.";
						cout << endl << "Press <Enter>";
						reshoot = true;
						cin.ignore(BUFFER_SIZE, '\n');
						continue;
					}
					// which ship was hit?
					CShip shipHit = curTarget->getShipStatus(cell);
					// now mark the grid
					if (shipHit == NOSHIP)
					{
						// record a MISSED
						curPlayer->setHitStatus(cell, MISSED);
						curPlayer->printGrid(cout, 1);
						reshoot = false;
						cout << "MISSED!" << endl << "Press <Enter>";
						cin.ignore(BUFFER_SIZE, '\n');
					}
					else
					{
						// record a HIT 
						curPlayer->setHitStatus(cell, HIT);
						// decrement pieces of ship and total pieces
						curTarget->hitShip(shipHit); 			

						curPlayer->printGrid(cout, 1);
						reshoot = true;
						cout << "HIT!" << endl;

						// check to see if that ship has been sunk
						if ( curTarget->isSunk(shipHit) ) 
						{
							CShip hitShip;
							cout << "You sank the ";
							shipHit.printName(); 
							cout << "!" << endl;
						}
						cout << "Press <Enter>";
						cin.ignore(BUFFER_SIZE, '\n');
					} // end if

					// if total pieces left == 0, we have a winner
					// set flags and return winner
					if (curTarget->getPiecesLeft() <= 0)
					{
						gameOver = true;
						reshoot = false;
					}
				} while (reshoot == true);
			} // end for whichPlayer
		} // end while !gameOver

		return whichPlayer - 1;

	} // CSinkFleet::play

} // namespace


