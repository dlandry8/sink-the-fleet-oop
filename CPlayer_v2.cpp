//-----------------------------------------------------------------------------
// File: CPlayer.cpp
//
//-----------------------------------------------------------------------------
#include "CPlayer_v2.h"

using namespace std;
namespace P4_CSinkFleet
{

	CPlayer::CPlayer(unsigned short whichPlayer, char gridSize)
	{
		allocateMemory();
		m_whichPlayer = whichPlayer;
		m_gridSize = gridSize;
		m_piecesLeft = TOTALPIECES;
		CCell starterCell(0, 0);
		for (short i = 0; i < SHIP_SIZE_ARRAYSIZE; i++)
		{
			m_Ships[i] = CShipInfo(i, 0, starterCell, shipSize[i]);
		}

	}


	//double check parameter for deep copy constructor
	CPlayer::CPlayer(const CPlayer& playerSource) //Copy Constructor //need the const???  //incomplete
	{
		short numberOfRows = (toupper(playerSource.m_gridSize) == 'L') ? LARGEROWS : SMALLROWS;
		short numberOfCols = (toupper(playerSource.m_gridSize) == 'L') ? LARGECOLS : SMALLCOLS;

		m_whichPlayer = playerSource.m_whichPlayer;
		m_piecesLeft = playerSource.m_piecesLeft;
		m_gridSize = playerSource.m_gridSize;
		for (short i = 0; i < 6; i++)
			m_Ships[i] = playerSource.m_Ships[i];

		allocateMemory();
		for (short j = 0; j < numberOfRows; ++j)
		{
			for (short k = 0; k < numberOfCols; ++k)
			{
				m_gameGrid[0][j][k] = playerSource.m_gameGrid[0][j][k];
				m_gameGrid[1][j][k] = playerSource.m_gameGrid[1][j][k];
			} // end for k
		} // end for j
	}

	CPlayer::~CPlayer(void) //destructor
	{
		deleteMemory(this, m_whichPlayer); //is this all?  if so, make it inline in the .h
	}

	//double check the paramters for deep copy
	//needs a lot of testing -- might need to switch to the original way I wrote it below
	CPlayer CPlayer::operator=(const CPlayer& copySource) //deep copy assignment
	{

		if (this == &copySource)
			return *this;

		short numberOfRows = (toupper(copySource.m_gridSize) == 'L') ? LARGEROWS : SMALLROWS;
		short numberOfCols = (toupper(copySource.m_gridSize) == 'L') ? LARGECOLS : SMALLCOLS;

		CPlayer temp(copySource);
		deleteMemory(this, m_whichPlayer);
		allocateMemory();

		for (short j = 0; j < numberOfRows; ++j)
		{
			for (short k = 0; k < numberOfCols; ++k)
			{
				std::swap(m_gameGrid[0][j][k], temp.m_gameGrid[0][j][k]);
				std::swap(m_gameGrid[1][j][k], temp.m_gameGrid[1][j][k]);
			} // end for k
		} // end for j

		std::swap(m_gridSize, temp.m_gridSize);

		std::swap(m_piecesLeft, temp.m_piecesLeft);

		for (short i = 0; i < SHIP_SIZE_ARRAYSIZE; i++)
		{
			std::swap(m_Ships[i], temp.m_Ships[i]);
		}

		std::swap(m_whichPlayer, temp.m_whichPlayer);



		//std::swap(m_gameGrid, temp.m_gameGrid);
		//std::swap(m_gridSize, temp.m_gridSize);
		//std::swap(m_piecesLeft, temp.m_piecesLeft);
		//std::swap(m_Ships, temp.m_Ships);
		//std::swap(m_whichPlayer, temp.m_whichPlayer);

		//*this = copySource; //seems like it shouldn't be this simple, though it may make sense since the copy algorithm is in the copy constructor  if it is this, re-write in an inline
		//original way I wrote for doing this:
		//all of this seems like there should be an easier way to do it, but this is thorough
		//need substantial testing -- some of the assignments are accessing what are private properties
		//if (this != &copySource)
		//{
		//deleteMemory(); //needed?
		//allocateMemory(); //needed?
		//m_whichPlayer = copySource.m_whichPlayer;
		//m_gameGrid[0] = copySource.m_gameGrid[0];
		//m_gameGrid[1] = copySource.m_gameGrid[1];
		//m_piecesLeft = copySource.m_piecesLeft;
		//m_gridSize =  copySource.m_gridSize;
		//for (short i = 0; i < 6; i++)
		//	m_Ships[i] = copySource.m_Ships[i];
		//}

		return *this;
	}


	//Accessors
	CShipInfo CPlayer::getCell(short whichGrid, CCell cell) // double check return object
	{
		int row = cell.getRow();
		int col = cell.getCol();
		return m_gameGrid[whichGrid][row][col]; //can all be re-written as one inline fumction
	}


	//Mutators
	void CPlayer::setCell(short whichGrid, CCell cell, CShip ship)
	{
		int row = cell.getRow();
		int col = cell.getCol();
		m_gameGrid[whichGrid][row][col] = ship; //can all be written as one inline function
	}


	//re=write using the CCell print
	void CPlayer::printGrid(ostream& sout, short whichGrid)
	{

		//need to double check the ship printing pieces
		short numberOfRows = (toupper(m_gridSize) == 'L') ? LARGEROWS : SMALLROWS;
		short numberOfCols = (toupper(m_gridSize) == 'L') ? LARGECOLS : SMALLCOLS;

		// clear the deck!
		system("cls");

		// Put P1 or P2 to signify which player is playing
		sout << "P" << m_whichPlayer + 1 << VERT;
		// column header
		for (short j = 1; j <= numberOfCols; ++j)
		{
			sout << setw(2) << j << VERT;
		}
		sout << endl;
		// row of underscores
		sout << HORIZ << HORIZ << CROSS;
		for (int j = 0; j < numberOfCols; j++)
		{
			if (j == numberOfCols - 1)
				sout << HORIZ << HORIZ << CL;
			else
				sout << HORIZ << HORIZ << CROSS;
		}
		sout << endl;

		// use printShip for each element in the grid
		int rowLetter = 'A';
		int i = 0;
		for (i = 0; i < numberOfRows - 1; i++)
		{
			sout << ' ' << (char)rowLetter++ << VERT;
			for (int j = 0; j < numberOfCols; j++)
			{
				m_gameGrid[whichGrid][i][j].print(sout);  // double check this was originally: printShip(sout, grid[i][j]);
				sout << VERT;
			}
			sout << endl;
			// row of underscores
			sout << HORIZ << HORIZ << CROSS;
			for (int j = 0; j < numberOfCols; j++)
			{
				if (j == numberOfCols - 1) // handle last column separately
					sout << HORIZ << HORIZ << CL;
				else
					sout << HORIZ << HORIZ << CROSS;
			}
			sout << endl;
		}
		// last row handled separately
		sout << ' ' << (char)rowLetter++ << VERT;
		for (int j = 0; j < numberOfCols; j++)
		{
			m_gameGrid[whichGrid][i][j].print(sout); //originally: printShip(sout, grid[i][j]);
			sout << VERT;
		}
		sout << endl;
		// row of underscores
		sout << HORIZ << HORIZ << CU;
		for (int j = 0; j < numberOfCols; j++)
		{
			if (j == numberOfCols - 1)
				sout << HORIZ << HORIZ << LR;
			else
				sout << HORIZ << HORIZ << CU;
		}
		sout << endl;
	}



	bool CPlayer::getGrid(string fileName)
	{
		string line;
		ifstream ifs;
		//CShip ship = NOSHIP;
		CShip ship;
		char shipLetter;
		short shipCount[SHIP_SIZE_ARRAYSIZE] = { 0 };
		char cell = ' ';
		char fsize = 'S';
		short numberOfRows = (toupper(m_gridSize) == 'L') ? LARGEROWS : SMALLROWS;
		short numberOfCols = (toupper(m_gridSize) == 'L') ? LARGECOLS : SMALLCOLS;
		int gridShip = 1, gridRow, gridCol; // grid ship &index of grid location to load
		int totalGamePieces = 0;      // total # of game pieces read in from file

		// Catch any errors when opening the input file
		try
		{
			ifs.open(fileName.c_str());
			if (!ifs)
			{
				cout << "could not open file " << fileName << endl
					<< " press <enter> to continue" << endl;
				std::cin.ignore(BUFFER_SIZE, '\n');			//note: My older VS2010 is giving me intellisense errors with having just cin without the std::
				getchar();
				return false;
			}
		}
		catch (exception e)
		{
			cout << "could not open file " << fileName << endl
				<< " press <enter> to continue" << endl;
			std::cin.ignore(BUFFER_SIZE, '\n');
			getchar();
			return false;
		}

		// Initialize grid to no ships before loading game ..
		for (short j = 0; j < numberOfRows; ++j)
		{
			for (short k = 0; k < numberOfCols; ++k)
			{
				m_gameGrid[0][j][k] = NOSHIP;
			} // end for k
		} // end for j

		ifs.get(fsize);  // read in size of playing grid from file 

		cout << "fsize = " << fsize << endl;   // load game matches game play type?
		if (fsize != m_gridSize) {
			cout << "File: " << fileName << " --- ERROR: ";
			cout << "File game size does not match current game size";
			cout << " --- exiting getGrid() with FAILURE !!!" << endl;
			cout << " press <enter> to continue" << endl;
			std::cin.ignore(BUFFER_SIZE, '\n');
			getchar();
			return false; // grid type mismatch
		}

		totalGamePieces = 0;
		while (!ifs.eof())    // read in ship type, row, col
		{
			ifs >> shipLetter;
			switch (shipLetter)
			{
			case 'N':
				ship = NOSHIP;
				gridShip = 0;
				break;
			case 'M':
				ship = MINESWEEPER;
				gridShip = 1;
				break;
			case 'S':
				ship = SUB;
				gridShip = 2;
				break;
			case 'F':
				ship = FRIGATE;
				gridShip = 3;
				break;
			case 'B':
				ship = BATTLESHIP;
				gridShip = 4;
				break;
			case 'C':
				ship = CARRIER;
				gridShip = 5;
				break;
			default:
				cout << "Could not identify the ship type";
				gridShip = -1;
			}
			ifs >> gridRow;  // read in row position of ship
			ifs >> gridCol;  // read in col position of ship

			// Check the validity of the data before saving in the grid

			if ((gridShip < 0) || (gridShip >= SHIP_SIZE_ARRAYSIZE) ||
				(gridRow  < 0) || (gridRow  > numberOfRows) ||
				(gridCol  < 0) || (gridCol  > numberOfCols))
			{
				cout << "File: " << fileName << " ... ERROR: ";
				if (gridShip < 0)  cout << "gridShip < 0";
				if (gridShip >=
					SHIP_SIZE_ARRAYSIZE) cout << "gridShip > "
					<< "SHIP_SIZE_ARRAYSIZE";
				if (gridRow < 0)  cout << "gridRow < 0";
				if (gridRow > numberOfRows) cout << "gridRow > numberOfRows";
				if (gridCol < 0)  cout << "gridCol < 0";
				if (gridCol > numberOfRows) cout << "gridCol > numberOfCols";
				cout << " --- exiting getGrid() with FAILURE !!!" << endl;
				cout << " press <enter> to continue" << endl;
				std::cin.ignore(BUFFER_SIZE, '\n');
				getchar();

				return false; // bad ship type or grid index out-of-bound
			}
			m_gameGrid[0][gridRow][gridCol]
				= (Ship)gridShip;  // convert ship (saved as an int) to Ship enum

			if (ifs.eof()) break;
			totalGamePieces++; // update total # of game pieces found
		}

		cout << totalGamePieces << " game pieces read in from file ";
		cout << fileName << endl;
		ifs.close(); // close input file 

		if (totalGamePieces != TOTALPIECES)  // check if expected # of pieces read 
		{
			cout << " File: " << fileName << " --- ERROR: ";
			cout << " total game   pieces read in file = " << totalGamePieces << endl;
			cout << " total expected pieces in file = " << TOTALPIECES << endl;
			cout << " aborting with potential problem found in getGrid()!!!" << endl;
			cout << " press <enter> to continue" << endl;
			std::cin.ignore(BUFFER_SIZE, '\n');
			getchar();

			return false; // illegal # of totalpieces encountered
		}

		cout << "New game successfully loaded.\n\n";
		cout << " press <enter> to continue" << endl;
		std::cin.ignore(BUFFER_SIZE, '\n');
		getchar();

		return true;
	}



	void CPlayer::saveGrid(string fileName)
	{
		short numberOfRows = (toupper(m_gridSize) == 'L') ? LARGEROWS : SMALLROWS;
		short numberOfCols = (toupper(m_gridSize) == 'L') ? LARGECOLS : SMALLCOLS;

		int gridShip, gridRow, gridCol; // grid ship & grid location to be written
		int totalGamePieces = 0;        // total # of game pieces saved to file

		// create output stream object for new file and call it ofs
		ofstream ofs(fileName.c_str(), ios::out);

		ofs << m_gridSize << endl;   // Save size of grid to output file

		// traverse every grid element and save ship type enum, row and col
		// for every location containing a ship.  Validate each field before
		// before writing output to the file so that no errors can occur
		// when the file is read back in again (for a new game)

		totalGamePieces = 0;  // keep count of # of game pieces saved to file
		for (short j = 0; j < numberOfRows; j++)
		{
			for (short k = 0; k < numberOfCols; k++)
			{
				if (m_gameGrid[0][j][k] != NOSHIP)
				{
					// Grid cell contains ship.  Write it to the file.
					gridShip = m_gameGrid[0][j][k];
					gridRow = j;
					gridCol = k;

					// Check ecah value prior to saving data to output data 

					if ((gridShip < 0) || (gridShip > SHIP_SIZE_ARRAYSIZE) ||
						(gridRow  < 0) || (gridRow  > numberOfRows) ||
						(gridCol  < 0) || (gridCol  > numberOfCols))
					{
						cout << "File: " << fileName << " --- ERROR: ";
						if (gridShip < 0) cout << "gridShip < 0";
						if (gridShip >
							SHIP_SIZE_ARRAYSIZE) cout << "gridShip > "
							<< "SHIP_SIZE_ARRAYSIZE";
						if (gridRow < 0) cout << "gridRow < 0";
						if (gridRow >
							numberOfRows) cout << "gridRow > numberOfRows";
						if (gridCol < 0) cout << "gridCol < 0";
						if (gridCol >
							numberOfRows) cout << "gridCol > numberOfCols";
						cout << " --- potential problem found in saveGrid()!!!";
						cout << endl << "Press <enter>";
						getchar();
					}
					m_gameGrid[0][j][k].print(ofs);
					ofs << " " << j << " " << k << endl; // Save ship grid location
					totalGamePieces++;
				}
			} // end for k
		} // end for j
		// Check totalPieces=TOTALPIECES to verify correct # of ship pieces were saved
		cout << totalGamePieces << " game pieces written to file ";
		cout << fileName << endl;
		ofs.close();           // close file

		if (totalGamePieces != TOTALPIECES) // Confirm correct # of ship pieces saved
		{
			cout << " File: " << fileName << " --- ERROR: ";
			cout << " total game pieces read in file = " << totalGamePieces << endl;
			cout << " total expected pieces in file = " << TOTALPIECES << endl;
			cout << " --- potential problem found in saveGrid()!!!" << endl;
			cout << " press <enter> to continue" << endl;
			cin.ignore(BUFFER_SIZE, '\n');
			getchar();
		};
		m_piecesLeft = totalGamePieces;
		cout << "Current game successfully saved.\n\n";
		cout << " press <enter> to continue" << endl;
		cin.ignore(BUFFER_SIZE, '\n');
		getchar();
		return;
	}




	void CPlayer::setShips()
	{
		char input = 'V';
		char ok = 'Y';
		char save = 'N';
		ostringstream outSStream;
		CCell location(0, 0);
		CShipInfo errorCheckShip;

		for (short j = 1; j < SHIP_SIZE_ARRAYSIZE; j++)
		{
			system("cls");
			printGrid(cout, 0);
			outSStream.str("");
			//outSStream << "Player " << m_whichPlayer + 1 << ", enter " << m_Ships[j] << "'s orientation";            //<< m_Ships[j].getName() << " orientation";
			cout << "Player " << m_whichPlayer + 1 << ", enter " << m_Ships[j] << "'s orientation";
			input = safeChoice(outSStream.str(), 'V', 'H');
			if (input == 'V')
				m_Ships[j].setOrientation(VERTICAL);
			else
				m_Ships[j].setOrientation(HORIZONTAL);

			//need to set the bow coordinates
			//this will use the CCell input Coordinates which is a void return and also handles all
			//		prompt text and input verification
			//		the CCell inputCoordinates may need to be modified
			location.inputCoordinates();
			m_Ships[j].setBowLocation(location);
			if (!(isValidLocation(j)))
			{
				cout << "invalid location. Press <enter>";
				cin.get();
				j--; // redo
				continue;
			}

			// Proposed location is valid with no overlaps with other ships.Add ship.
			CCell tempCell;
			int rowNum = 0; // row # of bow location of ship to be placed   
			int colNum = 0; // col # of bow location of ship to be placed   

			tempCell = m_Ships[j].getBowLocation();
			rowNum = tempCell.getRow(); // Add row
			colNum = tempCell.getCol(); // Add col

			// Update grid with full length of ship either vertically or horizontal

			for (short offset = 0; offset < shipSize[j]; offset++)
			{
				if (m_Ships[j].getOrientation() == VERTICAL)
					m_gameGrid[0][rowNum + offset][colNum]
					= (Ship)j;
				else
					m_gameGrid[0][rowNum][colNum + offset]
					= (Ship)j;
			}

		} // end for j

		// display grid for last ship entry & ask if game should be saved

		printGrid(cout, 0);

		save = safeChoice("\nSave starting grid?", 'Y', 'N');
		if (save == 'Y')
		{
			string fileName;
			cout << "Enter name of new file in which to save game: ";
			cin >> fileName;
			fileName = fileName + ".shp";  // Add .shp default extension to base name
			saveGrid(fileName);
		}
		return;
	}




	void CPlayer::hitShip(CShip ship)
	{
		m_piecesLeft -= 1;
		for (short i = 0; i < 6; i++)
		{
			if (m_Ships[i].getName() == ship)
			{
				m_Ships[i].setPiecesLeft(m_Ships[i].getPiecesLeft() - 1);  //see how many pieces are left, then set the number of pieces left to -= 1
				break;
			}
		}
	}


	bool CPlayer::isValidLocation(short whichShip)
	{
		short numberOfRows = (toupper(m_gridSize) == 'L') ? LARGEROWS : SMALLROWS;
		short numberOfCols = (toupper(m_gridSize) == 'L') ? LARGECOLS : SMALLCOLS;

		int j = whichShip;   // ship type
		CCell shipLocation;
		shipLocation = m_Ships[j].getBowLocation();
		CDirection orientation;
		orientation = m_Ships[j].getOrientation();

		int rowNum = shipLocation.getRow();  // bow grid location
		int colNum = shipLocation.getCol();  // bow grid location

		// Check if proposed entire ship placement is entirely on the playing grid
		// trying into account the ship bow location, length of the ship and its
		// orientation.

		if (rowNum < 0) return false;
		if (colNum < 0) return false;
		if (((rowNum + (shipSize[j] - 1)) >= numberOfRows) &&
			(orientation == VERTICAL))   return false;
		if (((colNum + (shipSize[j] - 1)) >= numberOfCols) &&
			(orientation == HORIZONTAL)) return false;

		// Now heck if proposed placement collides with any existing ships

		for (short offset = 0; offset < shipSize[j]; offset++)
		{
			if (orientation == VERTICAL)
			{
				if (m_gameGrid[0][rowNum + offset][colNum] != NOSHIP)
					return false;  // vertical ship overlap found
			}
			else
			{
				if (m_gameGrid[0][rowNum][colNum + offset] != NOSHIP)
					return false;  // horizontal ship overlap found
			}
		}
		return true;  // no placement error found.  Loaction is valid.
	}


	CShipInfo CPlayer::operator[](short index) const
	{
		if (index >= 0 && index <= 6)
			return m_Ships[index];
		else //else the index is out of range  //need to fix this error handling
		{
			cout << "Index is out of range!" << endl;
			return 0;
		}
	}



	CPlayer CPlayer::operator--()
	{
		m_piecesLeft -= 1;
		return *this;
	}




	//DOUBLE CHECK THIS!!! I got rid of the player loop
	void CPlayer::allocateMemory()
	{
		short numberOfRows = (getGridSize() == 'L') ? LARGEROWS : SMALLROWS;
		short numberOfCols = (getGridSize() == 'L') ? LARGECOLS : SMALLCOLS;

		try
		{
			// Allocate memory for each grid row
			m_gameGrid[0] = nullptr;
			m_gameGrid[0] = new CShip*[numberOfRows];
			m_gameGrid[1] = nullptr;
			m_gameGrid[1] = new CShip*[numberOfRows];
			for (short j = 0; j < numberOfRows; ++j)
			{
				// Allocate memory for each grid column
				m_gameGrid[0][j] = nullptr;
				m_gameGrid[0][j] = new CShip[numberOfCols];
				m_gameGrid[1][j] = nullptr;
				m_gameGrid[1][j] = new CShip[numberOfCols];

				// Initialize every grid position to contain no ship
				for (short k = 0; k < numberOfCols; ++k)
				{
					m_gameGrid[0][j][k] = NOSHIP;
					m_gameGrid[1][j][k] = NOSHIP;
				} // end for k
			} // end for j
		}
		catch (exception e)  // catch any memory allocation errors that may occur 
		{
			deleteMemory(this, m_whichPlayer);
			cerr << "exception: " << e.what() << endl;
			cout << "shutting down" << endl;
			cin.ignore(BUFFER_SIZE, '\n');
			exit(EXIT_FAILURE);
		}
	}




	//DOUBLE CHECK THIS!!! I got rid of the player loops and have the function access the class properties directly
	void CPlayer::deleteMemory(CPlayer player[], short whichPlayer)
	{
		short numberOfRows = (getGridSize() == 'L') ? LARGEROWS : SMALLROWS;
		short numberOfCols = (getGridSize() == 'L') ? LARGECOLS : SMALLCOLS;

		try
		{
			for (short iGrid = 0; iGrid < 2; ++iGrid)
			{
				if (player[whichPlayer].m_gameGrid[iGrid] == nullptr) continue;
				for (short j = 0; j < numberOfRows; ++j)
				{
					if (player[whichPlayer].m_gameGrid[iGrid][j] == nullptr) continue;
					delete[] player[whichPlayer].m_gameGrid[iGrid][j];
				} // end for j
				delete[] player[whichPlayer].m_gameGrid[iGrid];
			} // end for iGrid
		}

		catch (bad_alloc e)
		{
			cerr << "exception in deleteMem: " << e.what() << endl;
			cout << "shutting down" << endl;
			cin.ignore(BUFFER_SIZE, '\n');
			exit(EXIT_FAILURE);
		}
		catch (exception e)
		{
			cerr << "Unforseen error:" << e.what() << endl;
			cout << "shutting down" << endl;
			cin.ignore(BUFFER_SIZE, '\n');
			exit(EXIT_FAILURE);

		}

	}

}