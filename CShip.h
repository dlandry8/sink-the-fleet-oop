//----------------------------------------------------------------------------
//	File:			CShip.h
//
//	Class:			CShip
//----------------------------------------------------------------------------
#ifndef C_SHIP_H
#define C_SHIP_H


#include "safeio.h"
#include "textGraphics.h"
#include <iostream>

namespace P4_CSinkFleet
{
	using namespace std;

	enum Ship
	{
		NOSHIP,			// 0
		//----------------------------------------------------
		MINESWEEPER,	// 1 (1-5) -- used only for owner
		SUB,			// 2
		FRIGATE,		// 3
		BATTLESHIP,		// 4
		CARRIER,		// 5
		//----------------------------------------------------
		HIT,			// 6 (6-7) -- used only for other side
		MISSED			// 7
	};

	//------------------------------------------------------------------------
	//	Title:			CShip Class
	//
	//	Description:	This is a wrapper class for the Ship enum.  It allows
	//						insertion of a CShip object onto the game grid
	//						and allows the printing of the ship's name in
	//						game output.
	//
	//	Programmers:	David Landry, Jason Gautama
	//
	//	Date:			3/5/2016
	//
	//	Version:		0.91
	//
	//	Environment:	PC running Windows 10
	//					Compiled using Microsoft Visual Studio Community 2013
	//
	//	Class CShip:
	//
	//	Properties:
	//					Ship m_ship
	//						A ship enum.
	//
	//	Methods:
	//		Inline:
	//			operator Ship() const
	//				Ship type cast operator.
	//				Grants access to the Ship enum this class wraps around.
	//				Parameters:		None
	//				Returns:		A ship enum of the CShip object.
	//
	//			void printName(ostream & sout = cout) const
	//				This method prints the name for the ship (e.g.,
	//					"Minesweeper", "Hit", etc.)
	//				Parameters:		ostream & sout, a reference to the
	//					output stream.
	//				Returns:		None
	//
	//		Non-inline:
	//			CShip(int shipType = 0)
	//				This is the default constructor for the CShip class.
	//			void print(ostream & sout = cout) const
	//				This method prints the symbol for the ship (e.g., F for
	//				frigate, H for hit, thingey for miss).
	//------------------------------------------------------------------------
	class CShip
	{
	public:
		CShip(int shipType = 0);
		CShip(Ship shipEnum) :m_ship(shipEnum){}
		operator Ship() const { return m_ship; }
		void print(ostream & sout = cout) const;
		void printName(ostream & sout = cout) const
		{
			sout << shipNames[int(m_ship)];
		}

	private:
		Ship m_ship;
		static const char* shipNames[6];

	};

	ostream & operator<<(ostream & sout, const CShip thisShip);
	istream & operator>>(istream & sin, CShip & thisShip);
}
#endif