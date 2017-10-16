//----------------------------------------------------------------------------
//	File:			CShipInfo.cpp
//
//	Namespace:		P4_CSinkFleet
//	Class:			CShipInfo
//
//	Functions:		void CShipInfo::setPiecesLeft(short shipPieces)
//					bool CShipInfo::isSunk() const
//----------------------------------------------------------------------------

#include "CShipInfo.h"

namespace P4_CSinkFleet
{
	//------------------------------------------------------------------------
	//	Class:			CShipInfo
	//
	//	Title:			Ship Information Class for Sink The Fleet
	//
	//	Description:	Gathers the ship enum, bow direction, orientation,
	//						and pieces left into one handy class.
	//
	//	Programmers:	David Landry & Jason Gautama
	//
	//	Date:			3/5/2016
	//
	//	Version:		0.8
	//
	//	Environment:	PC running Windows 10
	//					Compiled using Microsoft Visual Studio Community 2013
	//
	//	Class:	CShipInfo:
	//		Properties:
	//					CShip m_name:				The name (enum #) of the
	//													ship.
	//					CDirection m_orientation:	The direction the ship is
	//													facing.
	//					CCell m_bowLocation:		The grid location of the
	//													ship's bow.
	//					short m_piecesLeft:			The number of pieces not
	//													blown to smithereens.
	//
	//		History Log:
	//		3/5/16:		DL & JG completed version 0.8, containing all but the
	//						print methods.
	//------------------------------------------------------------------------

	const short CShipInfo::shipSize[6] = { 0, 2, 3, 3, 4, 5 };

	//------------------------------------------------------------------------
	//	Class:			CShipInfo
	//	Method:			void CShipInfo::setPiecesLeft(short shipPieces)
	//	Description:	sets the pieces left 
	//	Input:			None
	//	Output:			None
	//	Calls:			None
	//	Called by:		None
	//	Parameters:		short shipPieces
	//	Returns:		None
	//	History Log:	3/5/16: DL & JG completed version 1.0
	//------------------------------------------------------------------------
	void CShipInfo::setPiecesLeft(short shipPieces)
	{
		if (shipPieces < 0 || shipPieces > shipSize[int(m_name)])
			throw domain_error("The ship cannot have that many pieces left.");
		else
			m_piecesLeft = shipPieces;
	}

	//------------------------------------------------------------------------
	//	Class:			CShipInfo
	//	Method:			bool CShipInfo::isSunk() const
	//	Description:	test whether there are no pieces left.
	//	Input:			None
	//	Output:			None
	//	Calls:			None
	//	Called by:		None
	//	Parameters:		None
	//	Returns:		returns true, if pieces still present
	//					returns false, if there are no pieces left
	//	History Log:	3/5/16: DL & JG completed version 1.0
	//------------------------------------------------------------------------
	bool CShipInfo::isSunk() const
	{
		if (m_piecesLeft <= 0)
			return true;
		else
			return false;
	}

	//------------------------------------------------------------------------
	//	Function:		ostream & operator<<(ostream & sout, const CShip &
	//						thisShipInfo)
	//	Description:	Outputs the name of the ship.
	//	Input:			None
	//	Output:			The ship's name.
	//	Calls:			None
	//	Called by:		None
	//	Parameters:		ostream & sout, the output stream;
	//					const CShipInfo & thisShipInfo, a const reference
	//						to a CShipInfo object
	//	Returns:		the output stream
	//	History Log:	3/8/2016: DL & JG completed version 1.0
	//------------------------------------------------------------------------
	ostream & operator<<(ostream & sout, const CShipInfo & thisShipInfo)
	{
		thisShipInfo.print(sout);
		return sout;
	}

}

