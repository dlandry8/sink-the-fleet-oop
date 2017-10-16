//----------------------------------------------------------------------------
//	File:			CCell.cpp
//
//	Namespace:		P4_CSinkFleet
//	Class:			CCell
//
//	Functions:		void CCell::inputCoordinates(istream & sin, char size)
//					void CCell::print(ostream & sout) const
//					ostream & operator<<(ostream & sout, CCell thisCell)
//----------------------------------------------------------------------------
#include "CCell.h"
#include <cstring>
#include <sstream>
#include <iomanip>

#define BUFFER_SIZE 255

namespace P4_CSinkFleet
{
	const short SMALLROWS = 8;
	const short LARGEROWS = 10;
	const short SMALLCOLS = 12;
	const short LARGECOLS = 24;

	//------------------------------------------------------------------------
	//	Class:			CCell
	//
	//	Title:			Cell Coordinate Class for Sink The Ship
	//
	//	Description:	Sets, validates, and prints coordinates for the
	//						Sink the Ship game.
	//
	//	Programmers:	David Landry & Jason Gautama
	//
	//	Date:			3/4/2016
	//
	//	Version:		1.01
	//
	//	Environment:	PC running Windows 10
	//					Compiled using Microsoft Visual Studio Community 2013
	//
	//	Class:	CCell:
	//		Properties:
	//					unsigned short m_row
	//						The row number from 0 to max row size - 1.
	//					unsigned short m_col
	//						The column number from 0 to max column size - 1.
	//
	//		History Log:
	//		3/3/16:		DL & JG completed version 1.0.	
	//		3/4/16:		DL completed version 1.01, adding in header blocks
	//						and standardizing the include directives.
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	//	Class:			CCell
	//	Method:			void CCell::inputCoordinates(istream & sin, char size)
	//	Description:	Input method for the CCell class.  It validates the
	//						input of coordinates against the size of the
	//						board.
	//	Input:			Row letter & column number
	//	Output:			Instructions for the player.
	//	Calls:			None
	//	Called by:		Explicit method call
	//	Parameters:		istream & sin, an input stream;
	//					char size, L or S for the size of the game grid.
	//	Returns:		None: this is a mutator for the CCell class.
	//	History Log:	3/3/16: DL, JG, & TG completed version 1.0
	//					3/4/16: DL completed version 1.01, adding header 
	//								blocks and comments.
	//------------------------------------------------------------------------
	void CCell::inputCoordinates(istream & sin, char size)
	{
		short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
		short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;
		char highChar = static_cast<char>(numberOfRows - 1) + 'A';
		char row = 'A';
		short col = 0;
		cout << "Row must be a letter from A to " << highChar
			<< " and column must be from 1 to " << numberOfCols << ": ";
		// If the character isn't in the range of A to highChar, enter the
		// below while loop.
		while ((row = toupper(sin.get())) < 'A' || row > highChar)
		{
			sin.ignore(BUFFER_SIZE, '\n');
			cout << "Row must be a letter from A to " << highChar
				<< " and column must be from 1 to " << numberOfCols
				<< ": ";
		}
		// Generate a prompt for the safeRead function.
		string prompt;
		stringstream strout;
		strout << "Column must be an integer from 1 to " << numberOfCols <<
			".  Please re-enter the column number: ";
		prompt = strout.str();
		const char * cprompt = prompt.c_str();
		// Use safeRead to read in the column part.
		safeRead(sin, col, cprompt);
		// If the entered column number is out of range, enter the below
		// loop until the player enters a column value within range.
		while (col < 1 || col > numberOfCols)
		{
			cout << "Column must be from 1 to " << numberOfCols <<
				".  Please re-enter the column number: ";
			safeRead(sin, col, cprompt);
		}
		m_col = col - 1;
		m_row = static_cast<short>(row - 'A');
	}

	//------------------------------------------------------------------------
	//	Class:			CCell
	//	Method:			void CCell::print(ostream & sout) const
	//	Description:	Print method for the CCell class.  It prints the
	//						a pair of coordinates.
	//	Input:			None.
	//	Output:			Row letter and column number ("A1", for example).
	//	Calls:			None
	//	Called by:		operator<<()
	//	Parameters:		ostream & sout, an output stream.
	//	Returns:		None.
	//	History Log:	3/3/16: DL & JG completed version 1.0
	//					3/4/16: DL completed version 1.01, adding header 
	//								blocks and comments.
	//------------------------------------------------------------------------
	void CCell::print(ostream & sout) const
	{
		// Assign the m_row parameter to a ready-to-print character, row.
		char row = 'A' + static_cast<char>(m_row);
		// Assigns to col the printable column number.
		unsigned short col = m_col + 1;
		// Print the coordinates.
		sout << row << col;
	}

	// -----------------------------------------------------------------------
	//	Function:		ostream& operator<<(ostream& sout,
	//						const CCell & thisCell)
	//	description:    prints out the CCell object to the stream
	//	Input:          None
	//	Output:         Screen display of coordinates.
	//	Calls:          None
	//	Called By:      n/a
	//	Parameters:     ostream & sout  -- the stream used for output
	//	                const CCell & thisCell -- the object to print
	//	Returns:        a reference to sout 
	//	History Log:	3/3/16: DL & JG completed version 0.8.
	//					3/4/16: DL completed version 1.0, adding this
	//								comment block and adjusting the
	//								parameters.
	// -----------------------------------------------------------------------
	ostream & operator<<(ostream & sout, const CCell & thisCell)
	{
		thisCell.print(sout);
		return sout;
	}

}