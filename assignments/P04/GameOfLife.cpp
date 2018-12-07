/**
*  Course: CMPS 2143 - OOP
*
*  Purpose: Program based on John Conway's Game of Life
*
*  @author Tyler Roop
*  @version 1.1 10/15/18
*  @github repo: https://github.com/tarrox1992/2143-OOP-Roop/tree/master/assignments/P04
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

/**
* GOLCell : A single instance of a cell in a Game of Life array
* @Data-Elements:
* 	bool alive		// is cell alive or not
*	int Neighbors	// how many neighbors cell has
* @Methods:
* 	GOLCell() initializes cell to dead with no neighbors
*/
struct GOLCell
{	bool alive;
	int Neighbors;
	GOLCell()
	{
		alive = false;
		Neighbors = 0;
	}
};

/**
* gameOfLife : A single instance of board of Game of Life
* @Data-Elements:
* 	GOLCell** World		// 2d array of GOLCell
*	int Rows			// how many rows in array
*	int Cols			// how many columns in array
* @Methods:
* 	gameOfLife() initializes game with no rows or columns
*	gameOfLife(int C, int R) initializes game of life with R rows and C columns
*	void populateCell(int i, int j, int k) sets cell to alive or dead
*	void countNeighbors() counts cell's live neighbors and sets Neighbor variable of cell
* 	void ApplyRules()	Applies the rules of the game of life to the world
*	void Print(std::string First, std::string Last, std::string OFile, int C, int R)
*		Prints final board to outfile
*/
class gameOfLife
{
private:

	GOLCell** World;
	int Rows;
	int Cols;

public:

	gameOfLife()
	{
		Rows = 0;
		Cols = 0;
	}

	gameOfLife(int C, int R)
	{
		Rows = R;
		Cols = C;
		World = new GOLCell *[Rows];

		for (int i = 0; i < Rows; i++) {
			World[i] = new GOLCell[Cols];
		}
	}

	/**
	* Function: Populate cell
	* 		sets cell to alive or dead
	* @param:
	*		int i row of cell
	*		int j column of cell
	*		int k whether cell is alive or dead
	* @returns:
	*       None
	*/
	void PopulateCell(int i, int j, int k)
	{
		World[i][j].alive = k;
	}

	/**
	* Function: countNeighbors
	* 		Counts the adjacent number of live cells
	* @param:
	*		none
	* @returns:
	*       None
	*/
	void countNeighbors()
	{
		for (int i = 0; i < Rows; i++)
		{
			for (int j = 0; j < Cols; j++)
			{
				World[i][j].Neighbors = 0;
				// Finds neighbors of cells that are not on edge
				if (i != 0 && j != 0 && i != Rows - 1 && j != Cols - 1)
				{
					World[i][j].Neighbors += World[i - 1][j - 1].alive;
					World[i][j].Neighbors += World[i - 1][j].alive;
					World[i][j].Neighbors += World[i - 1][j + 1].alive;
					World[i][j].Neighbors += World[i][j - 1].alive;
					World[i][j].Neighbors += World[i][j + 1].alive;
					World[i][j].Neighbors += World[i + 1][j - 1].alive;
					World[i][j].Neighbors += World[i + 1][j].alive;
					World[i][j].Neighbors += World[i + 1][j + 1].alive;
				}
				// Finds neighbors of cells that are not corners on top edge
				else if (i == 0 && j != 0 && j != Cols - 1)
				{
					World[i][j].Neighbors += World[i][j - 1].alive;
					World[i][j].Neighbors += World[i][j + 1].alive;
					World[i][j].Neighbors += World[i + 1][j - 1].alive;
					World[i][j].Neighbors += World[i + 1][j].alive;
					World[i][j].Neighbors += World[i + 1][j + 1].alive;
				}
				// Finds neighbors of cells that are not corners on left edge
				else if (i != 0 && j == 0 && i != Rows - 1)
				{
					World[i][j].Neighbors += World[i - 1][j].alive;
					World[i][j].Neighbors += World[i - 1][j + 1].alive;
					World[i][j].Neighbors += World[i][j + 1].alive;
					World[i][j].Neighbors += World[i + 1][j].alive;
					World[i][j].Neighbors += World[i + 1][j + 1].alive;
				}
				// Finds neighbors of cells that are not corners on bottom edge
				else if (j != 0 && i == Rows - 1 && j != Cols - 1)
				{
					World[i][j].Neighbors += World[i - 1][j - 1].alive;
					World[i][j].Neighbors += World[i - 1][j].alive;
					World[i][j].Neighbors += World[i - 1][j + 1].alive;
					World[i][j].Neighbors += World[i][j - 1].alive;
					World[i][j].Neighbors += World[i][j + 1].alive;
				}
				// Finds neighbors of cells that are not corners on right edge
				else if (i != 0 && i != Rows - 1 && j == Cols - 1)
				{
					World[i][j].Neighbors += World[i - 1][j - 1].alive;
					World[i][j].Neighbors += World[i - 1][j].alive;
					World[i][j].Neighbors += World[i][j - 1].alive;
					World[i][j].Neighbors += World[i + 1][j - 1].alive;
					World[i][j].Neighbors += World[i + 1][j].alive;
				}
				// Finds neighbors of top right cell
				else if (i == 0 && j == Cols - 1)
				{
					World[i][j].Neighbors += World[i][j - 1].alive;
					World[i][j].Neighbors += World[i + 1][j - 1].alive;
					World[i][j].Neighbors += World[i + 1][j].alive;
				}
				// Finds neighbors of bottom left cell
				else if (j == 0 && i == Rows - 1)
				{
					World[i][j].Neighbors += World[i - 1][j].alive;
					World[i][j].Neighbors += World[i - 1][j + 1].alive;
					World[i][j].Neighbors += World[i][j + 1].alive;
				}
				// Finds neighbors of bottom right cell
				else if (i == Rows - 1 && j == Cols - 1)
				{
					World[i][j].Neighbors += World[i - 1][j - 1].alive;
					World[i][j].Neighbors += World[i - 1][j].alive;
					World[i][j].Neighbors += World[i][j - 1].alive;
				}
				// Finds neighbors of top left cell
				else if (i == 0 && j == 0)
				{
					World[i][j].Neighbors += World[i][j + 1].alive;
					World[i][j].Neighbors += World[i + 1][j].alive;
					World[i][j].Neighbors += World[i + 1][j + 1].alive;
				}
			}
		}
	}

	/**
	* Function: ApplyRules
	* 		Applies the rules of the game of life to the world
	* @param:
	*		none
	* @returns:
	*       None
	*/
	void ApplyRules()
	{
		for (int i = 0; i < Rows; i++)
		{
			for (int j = 0; j < Cols; j++)
			{
				// if a cell has less than 2 neighbors it dies or stays dead
				if (World[i][j].Neighbors < 2)
					World[i][j].alive = false;
				// if a cell has more than 3 neighbors it dies or stays dead
				else if (World[i][j].Neighbors > 3)
					World[i][j].alive = false;
				// if a cell has exactly 3 neighbors it comes to life or stays alive
				else if (World[i][j].Neighbors == 3)
					World[i][j].alive = true;
				// if a cell has exactly 2 neighbors it either stays alive or stays dead
			}
		}
	}

	/**
	* Function: Print
	* 		Prints final board to outfile
	* @param:
	*		string First	First word in input file
	*		string Last		second word in input file
	*		string OFile	name of output file
	*		int C			number of columns in game board
	*		int R			number of rows in game board
	* @returns:
	*       None
	*/
	void Print(std::string First, std::string Last, std::string OFile, int C, int R)
	{
		int i, j;
		std::ofstream outfile;
		outfile.open(OFile);
		outfile << First << ' ' << Last << "\n\n";
		for (i = 0; i < Rows; i++) {
			for (j = 0; j < Cols; j++) {
				outfile << World[i][j].alive << ' ';
			}
			outfile << '\n';
		}
	}
};

/**
* Function: printUsage
* 		Prints error when command line parameters are incorrect
* @param:
*		None
* @returns:
*       None
*/
void printUsage() {
	std::cout << "Error: wrong param count.\n Example: main.exe inputfile.txt generations outputfile.txt\n";
	system("pause");
}

/**
* Function: FileFinder
* 		Pulls filename from command line parameter
* @param:
*		char** argv		array holding file name
		int i			size of said array
* @returns:
*       string Filename		Name of requested file in readable string form
*/
std::string FileFinder(char** argv, int i)
{
	std::string FileName;
	int j = 0;
	while (argv[i][j])
	{
		FileName += argv[i][j];
		j++;
	}
	return FileName;
}

/**
* Function: GenerationFinder
* 		Pulls generation number from command line parameter
* @param:
*		char** argv		array holding file name
*		int i			size of said array
* @returns:
*       int GenRun		Number of Generations to run for
*/
int GenerationReader(char** argv, int i)
{
	std::string StringNum;
	int GenRun = 0, j = 0, temp;

	while (argv[i][j])
	{
		StringNum += argv[i][j];
		j++;
	}
	for (int k = 0; k < j; k++)
	{
		temp = StringNum.at(k) - '0';
		for (int l = 1; l < (j - k); l++)
		{
			temp *= 10;
		}
		GenRun += temp;
	}
	return GenRun;
}

/**
* Function: RunGame
* 		Plays the Game of Life
* @param:
*		string IFile		input file
*		int RunGen			Generations to run for
*		string OFile		output file
* @returns:
*       none
*/
void RunGame(std::string IFile, int RunGen, std::string OFile);

int main(int argc, char** argv)
{
	if (argc < 4) {
		printUsage();
		exit(0);
	}
	std::string IFile, OFile;
	int RunGen = 30;

	IFile = FileFinder(argv, 1);
	RunGen = GenerationReader(argv, 2);
	OFile = FileFinder(argv, 3);
	RunGame(IFile, RunGen, OFile);

	return 0;
}

void RunGame(std::string IFile, int RunGen, std::string OFile)
{
	int Cols, Rows;
	int i = 0, j = 0, k;
	char temp;
	std::string First, Last;
	std::ifstream infile;
	infile.open(IFile);
	infile >> First >> Last >> Cols >> Rows;
	gameOfLife Gol(Cols, Rows);

	for (i = 0; i < Rows; i++)
	{
		for (j = 0; j < Cols; j++)
		{
			infile >> temp;
			k = temp - '0';
			Gol.PopulateCell(i, j, k);
		}
	}

	while (RunGen)
	{
		Gol.countNeighbors();
		Gol.ApplyRules();
		RunGen--;
	}
	Gol.Print(First, Last, OFile, Cols, Rows);
}
