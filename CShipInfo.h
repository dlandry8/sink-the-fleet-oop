//----------------------------------------------------------------------------
//	File:		CShipInfo.cpp
//
//	Class:		CShipInfo
//----------------------------------------------------------------------------
#ifndef C_SHIPINFO_H
#define C_SHIPINFO_H

#include "CShip.h"
#include "CDirection.h"
#include "CCell.h"
#include <iostream>

namespace P4_CSinkFleet
{
//------------------------------------------------------------------------
//	Title:			Sink The Fleet Ship Info
//
//	Description:	This class provides information for each ship.
//
//	Programmers:	David Landry, Jason Gautama
//
//	Date:			3/5/2016
//
//	Version:		0.2
//
//	Environment		PC running Windows 10
//					Compiled using Microsoft Visual Studio Community 2013
//
//	Class CCell:
//
//	Properties:
//					CShip m_name
//						CShip object of the ship.
//					CDirection m_orientation
//						Tells the direction the ship is facing.
//					CCell m_bowLocation
//						The coordinates of the bow (the rest of the ship
//						goes down if vertical or to the right if horizontal).
//					short m_piecesLeft
//						A short integer telling how many pieces of the ship
//						have not been mercilessly blown up.
//					static const int shipArraySize
//						Size of the shipSize array
//					static const short shipSize[6]
//						Number of elements in each ship.
//						(ignore 0)
//	Methods:
//			void print(ostream & sout = cout) const
//				Prints something.
//		Inline:
//			CShipInfo()
//				Default constructor that initializes the parameters.
//				Parameters:		None
//				Returns:		None
//				Input:			None
//				Output:			None
//			CShip getName() const
//				Gets the ship's name.
//				Parameters:		None
//				Returns:		A CShip, a ship name (enum) object.
//				Input:			None
//				Output:			None
//			CDirection getOrientation() const
//				Gets the ship's orientation.
//				Parameters:		None
//				Returns:		A CDirection, a ship's orientation object.
//				Input:			None
//				Output:			None
//			CCell getBowLocation() const
//				Gets the ship's bow location.
//				Parameters:		None
//				Returns:		A CCell, a ship's bow location.
//				Input:			None
//				Output:			None
//			short getPiecesLeft() const
//				Gets the ship's number of pieces left.
//				Parameters:		None
//				Returns:		A short representing the number of pieces left
//				Input:			None
//				Output:			None
//			void setName()
//				Sets the ship's name.
//				Parameters:		None
//				Returns:		None
//				Input:			None
//				Output:			None
//			void setOrientation()
//				Sets the ship's direction.
//				Parameters:		None
//				Returns:		None
//				Input:			None
//				Output:			None
//			void setBowLocation()
//				Sets the ship's bow location.
//				Parameters:		None
//				Returns:		None
//				Input:			None
//				Output:			None
//			CShipInfo operator--()
//				Prefix decrementer that decreases the number of pieces left
//				for the current ship by 1.


//		Non-inline:

//			void setPiecesLeft()
//				Sets the number of ship pieces left.
//			bool isSunk()
//				Returns true if there are no pieces of this ship left.
//				Abandon ship!  All hands abandon ship!

//
//	History log:
//		3/5/16:		DL & JG completed version 0.2
//		3/4/16:		DL completed version 1.01, adding in header blocks
//						and standardizing the include directives.
//------------------------------------------------------------------------

	using namespace std;
	class CShipInfo
	{
	public:
		
		CShipInfo(CShip shipType = 0, CDirection orientation = 0, CCell bowLocation = CCell(0, 0), short piecesLeft = 0) : m_name(shipType), m_orientation(orientation), m_bowLocation(bowLocation), m_piecesLeft(piecesLeft) {;}	
		CShip getName(){ return m_name; }
		CDirection getOrientation(){ return m_orientation; }
		CCell getBowLocation(){ return m_bowLocation; }
		short getPiecesLeft(){ return m_piecesLeft; }
		void setName(CShip shipID){ m_name = shipID; }
		void setOrientation(CDirection shipDirection)
		{m_orientation = shipDirection;}
		void setBowLocation(CCell shipBow){ m_bowLocation = shipBow; }
		void setPiecesLeft(short shipPieces);
		CShipInfo operator--() { m_piecesLeft -= 1; return *this; }
		bool isSunk() const;
		void print(ostream & sout = cout) const { m_name.printName(); }
		// Static constant public property:
		static const short shipSize[6];
	private:
		CShip m_name;
		CDirection m_orientation;
		CCell m_bowLocation;
		short m_piecesLeft;
	};

	ostream & operator<<(ostream & sout, const CShipInfo & thisShipInfo);
	
}

#endif