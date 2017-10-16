//-----------------------------------------------------------------------------
//	File:		CSinkTheFleet.h
//
//	class:	CSinkTheFleet
//-----------------------------------------------------------------------------
#ifndef CSINKTHEFLEET_H

#include "CPlayer.h"

namespace P4_CSinkFleet
{
//-----------------------------------------------------------------------------
//	Title:			CSinkTheFleet Class
//
//	Description:	This file contains the class definition for CSinkTheFleet
//
//	Programmer:		Thurman Gillespy
//   
//	Date:				3/9/16
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
//				CPlayer m_players[NUMPLAYERS] --array of NUMPLAYERS CPlayer objects
//				char m_gridSize -- the size of the game grid,
//								stored as a char 'S' or 'L' 
//
//	Methods:
//	
//		inline:
//			char getGridSize(void)
//				accessor
//				returns m_gridSize
//
//			void setGridSize(char gridSize)
//				mutator
//				sets m_gridSize
//			
//			CPlayer operator[](short index)
//				operator
//				returns the CPlayer in m_players[index]
//
//		non-inline:
//			CSinkTheFleet(char gridSize)
//			short play(void);
//			static void header(void);
//			static void endbox(short player);
//			
//--------------------------------------------------------------------------
	class CSinkTheFleet
	{
	public:
        // constructor
		CSinkTheFleet(char gridSize);
        // accessors
		char getGridSize(void) { return m_gridSize;  }
        // mutators
		void setGridSize(char gridSize) { m_gridSize = gridSize; }
        // methods
		short play(void);
		CPlayer operator[](short index) { return m_players[index]; }
		static void header(void);
		static void endbox(short player);

        // other classes
		friend class CPlayer;

	private:
		CPlayer m_players[NUMPLAYERS];
		char m_gridSize;
	};

}
#endif