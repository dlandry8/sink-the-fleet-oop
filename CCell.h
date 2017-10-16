//----------------------------------------------------------------------------
//	File:			CCell.h
//
//	Class:			CCell
//----------------------------------------------------------------------------
#ifndef C_CELL_H
#define C_CELL_H

#include <iostream>
#include "safeio.h"
namespace P4_CSinkFleet
{
	using namespace std;
	//------------------------------------------------------------------------
	//	Title:			Cell Coordinates Class
	//
	//	Description:	This class allows the proper input of coordinates.
	//
	//	Programmers:	David Landry, Jason Gautama
	//
	//	Date:			3/3/2016
	//
	//	Version:		1.01
	//
	//	Environment		PC running Windows 10
	//					Compiled using Microsoft Visual Studio Community 2013
	//
	//	Class CCell:
	//
	//	Properties:
	//					unsigned short m_row
	//						The row number from 0 to max row size - 1.
	//					unsigned short m_col
	//						The column number from 0 to max column size - 1.
	//
	//	Methods:
	//		Inline:
	//			CCell(unsigned short row = 0, unsigned short col = 0)
	//				Default constructor
	//				Initializes m_row & m_col.
	//				Parameters:
	//					unsigned short row, a row number from 0 to max row
	//						size - 1.
	//					unsigned short col, a column number from 0 to max
	//						column size - 1.
	//
	//			unsigned short getRow()
	//				Gets the value of m_row.
	//				Returns:
	//					An unsigned short that holds the value of m_row.
	//
	//			unsigned short getCol()
	//				Gets the value of m_col.
	//				Returns:
	//					An unsigned short that holds the value of m_col.
	//
	//		Non-inline:
	//			void print(ostream & sout = cout) const
	//				Prints the coordinates in the form of A - max row and
	//					1 to max column (e.g., "A1", "F5", etc.).
	//			void inputCoordinates(istream & sin = cin, char size = 'S')
	//				Input method that gathers coordinates entered in by the
	//					user and makes sure they're in-bounds.
	//
	//	History log:
	//		3/3/16:		DL & JG completed version 1.0
	//		3/4/16:		DL completed version 1.01, adding in header blocks
	//						and standardizing the include directives.
	//------------------------------------------------------------------------
	class CCell
	{
	public:
		CCell(unsigned short row = 0, unsigned short col = 0) : 
			m_row(row), m_col(col){}
		unsigned short getRow() { return m_row; }
		unsigned short getCol() { return m_col; }
		void print(ostream & sout = cout) const;
		void inputCoordinates(istream & sin = cin, char size = 'S');
	private:
		unsigned short m_row;
		unsigned short m_col;
	}; 
	ostream & operator<<(ostream & sout, const CCell & thisCell);
}
#endif