
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

	//clean up this block-------------------------------------------------
	const short NUMPLAYERS = 2;	// number of players in game
	const short SMALLROWS = 8;		// number of rows/columns in small sea array 
	const short LARGEROWS = 10;	// number of rows/columns in large sea array
	const short SMALLCOLS = 12;	// number of rows/columns in small sea array 
	const short LARGECOLS = 24;	// number of rows/columns in large sea array

	const short BOXWIDTH = 79;		// maximum screen line length


	const int SHIP_SIZE_ARRAYSIZE = 6; // size of the shipSize array
	const short shipSize[SHIP_SIZE_ARRAYSIZE] = { 0, 2, 3, 3, 4, 5 };
	const int TOTALPIECES = 17; // total pieces in all ships
	//-------------------------------------------------------------------



	//-----------------------------------------------------------------------------
	// File: CPlayer.h
	//
	//-----------------------------------------------------------------------------

	class CPlayer
	{
	public:
		CPlayer(unsigned short whichPlayer = 0, char gridSize = 'S'); //default constructor

		//double check parameter for deep copy constructor
		CPlayer(const CPlayer& playerSource); //Copy Constructor  //?? need const?

		~CPlayer(); //destructor

		//double check the paramters for deep copy
		CPlayer operator=(const CPlayer& copyCat); //deep copy assignment

		//Accessors
		unsigned short getWhichPlayer(){return m_whichPlayer;}
		short getPiecesLeft() {return m_piecesLeft;}
		char getGridSize() {return m_gridSize;}
		CShipInfo getCell(short whichGrid, CCell cell); // double check return object

		//Mutators
		void setGridSize(char size) {m_gridSize = size;}
		void setCell(short whichGrid, CCell cell, CShip ship);

		void printGrid(ostream& sout, short whichGrid);
		bool getGrid(string fileName);  //gets the grid from a file
		void saveGrid(string fileName); //saves the grid to a file

		void setShips(); //maybe need player number for parameter??
		void hitShip(CShip ship);  //does not check for the hit, but assigns a hit
		bool isValidLocation(short whichShip); //checks to make sure that ship placement is valid

		// TG additions
		void clearGrid(void) { ; } // QHICK HACK 
		Ship getHitStatus(CCell cell)
			{ return m_gameGrid[1][cell.getRow()][cell.getCol()]; }
		void setHitStatus(CCell cell, Ship hit) //this is not needed -- hitShip takes care of setting hit status. It will look up the cell based on which ship it is
			{ m_gameGrid[1][cell.getRow()][cell.getCol()] = hit; }
		Ship getShipStatus(CCell cell) 
			{ return m_gameGrid[0][cell.getRow()][cell.getCol()]; }
		bool isSunk(Ship ship) { return m_Ships[ship].isSunk() ; }
		//Ship getShipName(Ship ship) { return m_Ships[ship].getName(); }
		CShip getShipName(Ship ship) { return m_Ships[ship].getName(); }

		CShipInfo operator[](short index) const;
		CPlayer operator--();

	private:
		//Properties
		unsigned short m_whichPlayer;
		short m_piecesLeft;
		CShipInfo m_Ships[6];
		char m_gridSize;
		CShip** m_gameGrid[2];

		//Methods
		void allocateMemory();
		void deleteMemory(CPlayer player[], short whichPlayer);
	};
}
#endif