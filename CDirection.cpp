//----------------------------------------------------------------------------
//	File:			CDirection.cpp
//
//	Namespace:		P4_CSinkFleet
//	Class:			CDirection
//
//	Functions:		CDirection::CDirection(int ship)
//					void CDirection::printShip(ostream & sout) const
//					istream & operator>>(istream & sin, CDirection & ship)
//					ostream & operator<<(ostream & sout, 
//					const CDirection & ship)
//----------------------------------------------------------------------------

#include "CDirection.h"

namespace P4_CSinkFleet
{
	//------------------------------------------------------------------------
	//	Class:			CDirection
	//
	//	Title:			Cell Direction Class for Sink The Ship
	//
	//	Description:	This class allows proper input of ship orientation
	//
	//	Programmers:	David Landry & Jason Gautama
	//
	//	Date:			3/7/2016
	//
	//	Version:		1.01
	//
	//	Environment:	Hardware: i5
	//					Software: OS: Windows 10; 
	//					Compiles under Microsoft Visual C++ 2013
	//
	//	Class:			CDirection
	//	Properties:
	//					Direction m_direction, -- 0 if vertical and 
	//						1 if horizontal
	//
	//		History Log:
	//		3/3/16:		DL & JG completed version 1.0.	
	//		3/5/16:		JM completed version 1.01, adding in header blocks
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	//	Class:			CDirection
	//	Method:			CDirection::CDirection(int ship)
	//	Description:	a constructor that sets a valid value to m_direction
	//					if the passed in value are valid. 
	//	Input:			N/A
	//	Output:			N/A
	//	Calls:			None
	//	Called by:		N/A
	//	Parameters:		int ship -- number that correspond to the orientation
	//	Returns:		None
	//	History Log:	3/3/16: DL and JG completed version 1.0
	//					3/5/16: JM completed version 1.01, adding header 
	//								blocks
	//------------------------------------------------------------------------
	CDirection::CDirection(int ship)
	{
		if (ship == 0)
			m_direction = Direction(ship);
		else if (ship == 1)
			m_direction = Direction(ship);
		else
			throw domain_error("Invalid Direction!");
	}

	//------------------------------------------------------------------------
	//	Class:			CDirection
	//	Method:			void CDirection::printShip(ostream & sout) const
	//	Description:	a function that sets the character of the ship
	//					orientation
	//	Input:			N/A
	//	Output:			N/A
	//	Calls:			None
	//	Called by:		operator<<()
	//	Parameters:		ostream & sout -- an output stream.
	//	Returns:		None
	//	History Log:	3/3/16: DL and JG completed version 1.0
	//					3/5/16: JM completed version 1.01, adding header 
	//							blocks
	//------------------------------------------------------------------------
	void CDirection::printShip(ostream & sout) const
	{
		switch (m_direction)
		{
		case 0: sout << 'H';
			break;
		case 1: sout << 'V';
			break;
		}
	}

	//------------------------------------------------------------------------
	//	Class:			CDirection
	//	Method:			istream & operator>>(istream & sin, CDirection & ship)
	//	Description:	an input stream function that checks for proper input
	//					that relates to horizontal or vertical orientation. 
	//	Input:			Ship orientation
	//	Output:			N/A
	//	Calls:			None
	//	Called by:		None
	//	Parameters:		ostream & sout -- an output stream.
	//	Returns:		a referance to sout
	//	History Log:	3/3/16: DL and JG completed version 1.0
	//					3/5/16: JM completed version 1.01, adding header 
	//							blocks
	//					3/7/16 JM fixes header block information
	//------------------------------------------------------------------------
	istream & operator>>(istream & sin, CDirection & ship)
	{
		Direction currentDirection;
		char direction[12];
		string shipDirection;
		int numDirection = -1;

		if (!(isdigit(sin.peek())))
		{
			sin >> direction;
			for (int i = 0; i < 10; ++i)
				direction[i] = toupper(direction[i]);
			shipDirection = direction;
			if (shipDirection == "HORIZONTAL" || shipDirection == "H")
			{
				currentDirection = HORIZONTAL;
				ship = int(currentDirection);
			}
				
			else if (shipDirection == "VERTICAL" || shipDirection == "V")
			{
				currentDirection = VERTICAL;
				ship = int(currentDirection);
			}
				
			else
				throw domain_error("Invalid Direction!");
		}
		else
		{
			sin >> numDirection;
			ship = int(numDirection);
		}
		return sin;
	}

	ostream & operator<<(ostream & sout, const CDirection & ship)
	{
		ship.printShip(sout);
		return sout;
	}
};

