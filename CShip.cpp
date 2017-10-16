//----------------------------------------------------------------------------
//	File:			CShip.cpp
//
//	Namespace:		P4_CSinkFleet
//	Class:			CShip
//
//	Functions:		CShip::CShip(int shipType)
//					void CShip::print(ostream & sout) const
//					void CShip::printName(ostream & sout) const
//					ostream & operator<<(ostream & sout, const CShip thisShip)
//					istream & operator>>(istream & sin, CShip & thisShip)
//----------------------------------------------------------------------------
#include "CShip.h"

namespace P4_CSinkFleet
{
	//------------------------------------------------------------------------
	//	Class:			CShip
	//
	//	Title:			CShip Class
	//
	//	Description:	This is a wrapper class for the Ship enum.  It allows
	//						insertion of a CShip object onto the game grid
	//						and allows the printing of the ship's name in
	//						game output.

	//	Programmers:	David Landry & Jason Gautama
	//
	//	Date:			3/5/2016
	//
	//	Version:		0.91
	//
	//	Environment:	PC running Windows 10
	//					Compiled using Microsoft Visual Studio Community 2013
	//
	//	Class:	CCell:
	//		Properties:
	//					Ship m_ship
	//						A ship enum
	//
	//		History Log:
	//		3/3/16:		DL & JG completed version 0.9 (everything except the
	//						printName method).	
	//		3/5/16:		DL completed version 0.91, adding in header blocks
	//						and standardizing the include directives.
	//------------------------------------------------------------------------
	const char* CShip::shipNames[6] = { "No Ship", "Mine Sweeper",
		"Submarine", "Frigate", "Battleship", "Aircraft Carrier" };
	//------------------------------------------------------------------------
	//	Class:			CShip
	//	Method:			
	//	Description:	
	//	Input:			
	//	Output:			
	//	Calls:			
	//	Called by:		
	//	Parameters:		
	//	Returns:		
	//	History Log:	3/3/16: DL &  JG completed version 1.0
	//					3/5/16: DL completed version 1.01, adding header 
	//								blocks and comments.
	//------------------------------------------------------------------------
	CShip::CShip(int shipType)
	{
		if (shipType >= 0 && shipType <= 7)
			m_ship = Ship(shipType);
		else
			throw domain_error("That number is an invalid ship type.");
	}
	void CShip::print(ostream & sout) const
	{
		sout << ' ';
		switch (m_ship)
		{
		case NOSHIP: sout << ' ';
			break;
		case MINESWEEPER: sout << 'M';
			break;
		case SUB: sout << 'S';
			break;
		case FRIGATE: sout << 'F';
			break;
		case BATTLESHIP: sout << 'B';
			break;
		case CARRIER: sout << 'C';
			break;
		case HIT: sout << 'H';
			break;
		case MISSED: sout << MISS;
			break;
		default: sout << 'X';
		}
		//sout << VERT;
	}

	// -----------------------------------------------------------------------
	//	Function:		ostream& operator<<(ostream& sout,
	//						const CCell & thisCell)
	//	description:    prints out the CShip object to the stream
	//	Input:          None
	//	Output:         Letter grid-ready representation of the ship.
	//	Calls:          None
	//	Called By:      n/a
	//	Parameters:     ostream & sout  -- the stream used for output
	//	                const CShip & thisShip -- the object to print
	//	Returns:        a reference to sout 
	//	History Log:	3/3/16: DL & JG completed version 1.0.
	//					3/5/16: DL completed version 1.0, adding this
	//								comment block and adjusting the
	//								parameters.
	// -----------------------------------------------------------------------
	ostream & operator<<(ostream & sout, const CShip thisShip)
	{
		thisShip.print(sout);
		return sout;
	}

	// -----------------------------------------------------------------------
	//	Function:		istream& operator>>(istream& sin, CShip & thisShip)
	//	description:	Takes in a number or name to convert to a ship object.
	//	Input:          A name or number.
	//	Output:         Error message if out of range.
	//	Calls:          None
	//	Called By:      n/a
	//	Parameters:     istream & sin  -- the stream used for input
	//	                const CShip & thisShip -- the object to assign input
	//						to.
	//	Returns:        a reference to sin. 
	//	History Log:	3/3/16: DL & JG completed version 1.0.
	//					3/5/16: DL completed version 1.01, adding this
	//								comment block.
	// -----------------------------------------------------------------------
	istream & operator>>(istream & sin, CShip & thisShip)
	{
		char shipName[12] = "";	// User input if the user enters a nonnumeric.
		string RealShipName;	// It's easier for me to work with strings.
		Ship currentShip;
		int shipNumber = 0;
		// The >> operator allows for input by number or by ship name.  If
		//	the input is not numeric, we assume that a ship name is being
		//	entered.
		if (!(isdigit(sin.peek())))
		{
			sin >> shipName;
			for (short i = 0; i < 12; i++)
				shipName[i] = toupper(shipName[i]);
			RealShipName = shipName;
			if (RealShipName == "NOSHIP" || RealShipName == "NO SHIP" ||
				RealShipName == "NONE" || RealShipName == "N")
				currentShip = NOSHIP;
			else if (RealShipName == "MINESWEEPER" || RealShipName == "M")
				currentShip = MINESWEEPER;
			else if (RealShipName == "SUB" || RealShipName == "SUBMARINE" ||
				RealShipName == "S")
				currentShip = SUB;
			else if (RealShipName == "FRIGATE" || RealShipName == "F")
				currentShip = FRIGATE;
			else if (RealShipName == "BATTLESHIP" || RealShipName == "B")
				currentShip = BATTLESHIP;
			else if (RealShipName == "CARRIER" || RealShipName == "C")
				currentShip = CARRIER;
			else if (RealShipName == "HIT" || RealShipName == "H")
				currentShip = HIT;
			else if (RealShipName == "MISS" || RealShipName == "M" ||
				RealShipName == "MISSED")
				currentShip = MISSED;
			else
				throw domain_error("Invalid value!");
			thisShip = int(currentShip);
		}
		else
		{
			// If a number is entered, interpret it as a ship enum number.
			//	The constructor checks for proper numeric range.
			sin >> shipNumber;
			thisShip = shipNumber;
		}
		return sin;
	}
}