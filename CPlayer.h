//----------------------------------------------------------------------------
//	File:		CPlayer.cpp
//
//	Class:		CPlayer
//----------------------------------------------------------------------------
#ifndef CPLAYER_H
#define CPLAYER_H

#include "CShip.h"
#include "CCell.h"
#include "CShipInfo.h"
#include "safeio.h"
#include "textGraphics.h"
#include <cstdio>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

namespace P4_CSinkFleet
{
	//------------------------------------------------------------------------
	//	Title:			Sink The Fleet Player Class
	//
	//	Description:	This class provides information for each Player.
	//
	//	Programmers:	Matt Schroder
	//
	//	Date:			3/5/2016
	//
	//	Version:		1.01
	//
	//	Environment		PC running Windows 10
	//					Compiled using Microsoft Visual Studio Community 2013
	//
	//	Class CPlayer:
	//
	//	Properties:
	//					unsigned short m_whichPlayer
	//						Player number
	//					short m_piecesLeft
	//						Number of total hits left
	//					CShipInfo m_Ships[6]
	//						Total number of ships
	//					char m_gridSize
	//						'S' or 'L' gridSize
	//					CShip** m_gameGrid[2]
	//						2 gameGrid's for game
	//					
	//	Methods:
	//		Inline:
	//			~CPlayer() { deleteMemory(); }
	//				Default deconstructor. Calls deleteMemory
	//				Parameters:		None
	//				Returns:		None
	//				Input:			None
	//				Output:			None
	//			unsigned short getWhichPlayer(){return m_whichPlayer;}
	//				Gets whichPlayer is being accessed.
	//				Parameters:		None
	//				Returns:		A player number.
	//				Input:			None
	//				Output:			None
	//			short getPiecesLeft() {return m_piecesLeft;}
	//				Gets the total number of piecesLeft for player.
	//				Parameters:		None
	//				Returns:		Number of game piecesLeft for player
	//				Input:			None
	//				Output:			None
	//			char getGridSize() {return m_gridSize;}
	//				Gets the gridSize of player's game.
	//				Parameters:		None
	//				Returns:		Player's gridSize
	//				Input:			None
	//				Output:			None
	//			CShipInfo getCell(short whichGrid, CCell cell) 
	//				Get location of cell for specific player.
	//				Parameters:		short whichGrid -- which player's grid 
	//									number
	//								CCell cell -- which cell to access
	//				Returns:		Cell location according to whichPlayer
	//				Input:			None
	//				Output:			None
	//			void setGridSize(char size) {m_gridSize = size;}
	//				Set size of game grid.
	//				Parameters:		char size -- 'S' or 'L' depending on
	//									gridSize input
	//				Returns:		None
	//				Input:			None
	//				Output:			None
	//			void setCell(short whichGrid, CCell cell, CShip ship)
	//				Sets gameGrid cell to corrisponding shipInfo
	//				Parameters:		short whichGrid -- which player
	//								CCell cell -- which cell to be set
	//								CShip ship -- which shipInfo to be placed
	//				Returns:		None
	//				Input:			None
	//				Output:			None
	//			Ship getHitStatus(CCell cell)
	//				Gets the hit status of a ship at a particular cell
	//				Parameters:		CCell object
	//				Returns:		gameGrid cell location
	//				Input:			None
	//				Output:			None
	//			void setHitStatus(CCell cell, Ship hit) 
	//				Sets the hit status of a particular ship at a particular
	//					cell
	//				Sets the grid location to read as a hit
	//				Parameters:		CCell cell, Ship hit
	//				Returns:		void
	//				Input:			None
	//				Output:			None
	//			Ship getShipStatus(CCell cell) 
	//				Gets the ship status of a particular cell
	//				Parameters:		CCell cell
	//				Returns:		The Ship object at a particular cell
	//				Input:			None
	//				Output:			None
	//			bool isSunk(Ship ship)
	//				Checks to see if a particular ship is sunk or not
	//				Parameters:		Ship ship
	//				Returns:		A bool value representing if a ship is
	//									sunk
	//				Input:			None
	//				Output:			None
	//			Ship getShipName(Ship ship)
	//				Gets the name of a particular ship
	//				Parameters:		Ship ship
	//				Returns:		The Ship name
	//				Input:			None
	//				Output:			None
	//			CPlayer operator--()
	//				Decrements the total number of pieces left for a CPlayer
	//				Parameters:		none
	//				Returns:		*this with a decrement in total number of
	//									pieces left
	//				Input:			None
	//				Output:			None
	//
	//		Non-inline:
	//			CPlayer(unsigned short whichPlayer = 0, char gridSize = 'S')
	//				Default constructor that initializes the parameters.
	//			CPlayer(const CPlayer& playerSource)
	//				Deep copy for CPlayer Object.
	//			CPlayer operator=(const CPlayer& copyCat)
	//				Overloaded operator for deep copy assignment of CPlayer
	//					Object.
	//			void printGrid(ostream& sout, short whichGrid)
	//				Prints gameGrid.
	//			void hitShip(CShip ship)
	//				Assigns hit to gameGrid
	//			bool isValidLocation(short whichShip)
	//				Validates ship fits into selected place
	//			void clearGrid(void)
	//				Clears grid data from memory without deleting object
	//			void setHitStatus(CCell cell, Ship hit)
	//				Sets hit status in grid
	//			bool CPlayer::getGrid(string fileName)
	//				Loads the file from a grid, returns true if loaded
	//					properly
	//			void CPlayer::saveGrid(string fileName)
	//				Saves the set up game board to a file
	//			void CPlayer::setShips()
	//				Takes care of all ship placement for the game if not
	//					loading from a file
	//			CShipInfo CPlayer::operator[](short index) const
	//				returns the ShipInfo at a particular index
	//			void CPlayer::allocateMemory()
	//				allocates memory space for the game grid
	//			void CPlayer::deleteMemory()
	//				deleted the dynamically allocated memory for the game grid
	//
	//	History log:
	//		3/5/16:		MS, TG, & JD completed version 1.0
	//		3/9/16:		JD completed version 1.01, adding in header blocks
	//
	//------------------------------------------------------------------------
	
	const short NUMPLAYERS = 2;	// number of players in game
	const short SMALLROWS = 8;	// number of rows/columns in small sea array 
	const short LARGEROWS = 10;	// number of rows/columns in large sea array
	const short SMALLCOLS = 12;	// number of rows/columns in small sea array 
	const short LARGECOLS = 24;	// number of rows/columns in large sea array

	const short BOXWIDTH = 79;	// maximum screen line length


	const int SHIP_SIZE_ARRAYSIZE = 6; // size of the shipSize array
	const short shipSize[SHIP_SIZE_ARRAYSIZE] = { 0, 2, 3, 3, 4, 5 };
	const int TOTALPIECES = 17; // total pieces in all ships


	class CPlayer
	{
	public:
		CPlayer(unsigned short whichPlayer = 0, char gridSize = 'S'); 

		CPlayer(const CPlayer& playerSource); //Copy Constructor: deep copy

		~CPlayer() { deleteMemory(); } //destructor

		CPlayer operator=(const CPlayer& copyCat); //deep copy assignment

		//Accessors
		unsigned short getWhichPlayer(){return m_whichPlayer;}
		short getPiecesLeft() {return m_piecesLeft;}
		char getGridSize() {return m_gridSize;}
		CShipInfo getCell(short whichGrid, CCell cell) 
			{ return m_gameGrid[whichGrid][cell.getRow()][cell.getCol()]; }

		//Mutators
		void setGridSize(char size) {m_gridSize = size;}
		void setCell(short whichGrid, CCell cell, CShip ship) 
			{ m_gameGrid[whichGrid][cell.getRow()][cell.getCol()] = ship; }

		void printGrid(ostream& sout, short whichGrid);
		bool getGrid(string fileName);  //gets the grid from a file
		void saveGrid(string fileName); //saves the grid to a file

		void setShips();
		void hitShip(CShip ship);  //does not check for the hit, but assigns a hit
		bool isValidLocation(short whichShip); //checks to make sure that ship
											   //placement is valid

		// TG additions
		void clearGrid(void);
		Ship getHitStatus(CCell cell)
			{ return m_gameGrid[1][cell.getRow()][cell.getCol()]; }
		void setHitStatus(CCell cell, Ship hit) 
			{ m_gameGrid[1][cell.getRow()][cell.getCol()] = hit; }
		Ship getShipStatus(CCell cell) 
			{ return m_gameGrid[0][cell.getRow()][cell.getCol()]; }
		bool isSunk(Ship ship) { return m_Ships[ship].isSunk() ; }
		Ship getShipName(Ship ship) { return m_Ships[ship].getName(); }

		// operators
		CShipInfo operator[](short index) const;
		CPlayer operator--() { m_piecesLeft -= 1; return *this; }

	private:
		//Properties
		unsigned short m_whichPlayer;
		short m_piecesLeft;
		CShipInfo m_Ships[6];
		char m_gridSize;
		CShip** m_gameGrid[2];

		//Methods
		void allocateMemory();
		void deleteMemory();
	};
}
#endif