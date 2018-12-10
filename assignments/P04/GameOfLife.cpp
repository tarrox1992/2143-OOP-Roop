/**
*  Course: CMPS 2143 - OOP
*
*  Purpose: Program based on John Conway's Game of Life
*
*  @author Tyler Roop
*  @version 1.1 10/15/18
*  @github repo: https://github.com/tarrox1992/2143-OOP-Roop/tree/master/assignments/P04
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define CELLSIZE 10

using namespace sf;

/**
* GOLCell : A single instance of a cell in a Game of Life array
* @Extends:
*   sf::Drawable
* @Data-Elements:
* 	RectangleShape rect;	// sfml rectangle type
* 	bool alive;		// is cell alive or not
* @Methods:
* 	void draw(RenderTarget& target, RenderStates state) const
*/
struct GOLCell : public Drawable
{
	RectangleShape rect;
	bool alive;
	int Neighbors;
	GOLCell()
	{
		rect.setSize(Vector2f(CELLSIZE, CELLSIZE));
		alive = false;
		Neighbors = 0;
	}
protected:
	/**
	* void draw: draws an SFML shape to an SFML window.
	*/
	void draw(RenderTarget& target, RenderStates state) const // means this method won't change 
															  // anything...	
	{
		target.draw(rect);
	}
};

/**
* gameOfLife : A single instance of board of Game of Life
* @Data-Elements:
* 	GOLCell** World		// 2d array of GOLCell
*	int Rows			// how many rows in array/gameboard
*	int Cols			// how many columns in array/gameboard
*	RenderWindow &WindowRef		// reference to sfml window so we can draw it
* @Methods:
* 	gameOfLife() initializes game with no rows or columns
*	gameOfLife(int C, int R) initializes game of life with R rows and C columns
*	void populateCell(int i, int j, int k) sets cell to alive or dead
*	void countNeighbors() counts cell's live neighbors and sets Neighbor variable of cell
* 	void ApplyRules()	Applies the rules of the game of life to the world
*	void Print(std::string First, std::string Last, std::string OFile, int C, int R)
*		Prints final board to outfile
*	void printBoard	prints game to sfml window
*/
class gameOfLife
{
private:
	GOLCell **World;
	int Rows;
	int Cols;
	RenderWindow &WindowRef;

public:

	gameOfLife(RenderWindow &thatWindow) : WindowRef(thatWindow)
	{
		Rows = 0;
		Cols = 0;
	}

	gameOfLife(RenderWindow &thatWindow, int C, int R) : WindowRef(thatWindow)
	{
		Rows = R;
		Cols = C;
		World = new GOLCell *[Rows];

		for (int i = 0; i < Rows; i++) {
			World[i] = new GOLCell[Cols];
		}
	}

	void PopulateCell(int i, int j, int k)
	{
		World[i][j].alive = k;
		if (World[i][j].alive)
		{
			World[i][j].rect.setFillColor(Color::Magenta);
			World[i][j].rect.setPosition(j * CELLSIZE, i * CELLSIZE);
		}
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
				{
					World[i][j].alive = true;
					World[i][j].rect.setFillColor(Color::Magenta);
					World[i][j].rect.setPosition(j * CELLSIZE, i * CELLSIZE);
				}
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
	*		int Gens		number of generations game ran for
	* @returns:
	*       None
	*/
	void Print(std::string First, std::string Last, std::string OFile, int C, int R, int Gens)
	{
		int i, j;
		std::ofstream outfile;
		outfile.open(OFile);
		outfile << First << ' ' << Last << "\n\n";
		outfile << "Generation " << Gens << '\n';
		for (i = 0; i < Rows; i++) {
			for (j = 0; j < Cols; j++) {
				outfile << World[i][j].alive << ' ';
			}
			outfile << '\n';
		}
	}

	/**
		* Function: printBoard
		* 	Prints board to an sfml window
		* @param:
		*	None
		* @returns:
		*       None
		*/
	void printBoard()
	{
		for (int i = 0; i < Rows; i++)
		{
			for (int j = 0; j < Cols; j++)
			{
				if (World[i][j].alive)
				{
					WindowRef.draw(World[i][j].rect);
				}
			}
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
	// Prints error if parameter count incorrect
	if (argc < 4) {
		printUsage();
		exit(0);
	}

	// strings to hold input and output filenames
	std::string IFile, OFile;

	// int to hold run generation
	int RunGen;

	IFile = FileFinder(argv, 1);
	RunGen = GenerationReader(argv, 2);
	OFile = FileFinder(argv, 3);
	RunGame(IFile, RunGen, OFile);

	return 0;
}

void RunGame(std::string IFile, int RunGen, std::string OFile)
{
	// Ints to hold number of columns and rows
	int Cols, Rows;

	// ints to help navigate array holding gamecells, framerate, and generation count
	int i = 0, j = 0, k, FR = 1000000000, GenCount = 0;

	// hold temporary number from file to determine initial condition
	char temp;

	// strings hold names from input file
	std::string First, Last;

	// input file variables
	std::ifstream infile;
	infile.open(IFile);

	// reveives names and number of columns and rows from file
	infile >> First >> Last >> Cols >> Rows;

	// sfml variables to run display window
	RenderWindow window(VideoMode(Cols * 10, Rows * 10), "Game of Life");
	Vector2u size = window.getSize();
	gameOfLife Gol(window, Cols, Rows);

	// pulls initial conditions from input file
	for (i = 0; i < Rows; i++) {
		for (j = 0; j < Cols; j++) {
			infile >> temp;
			k = temp - '0';
			Gol.PopulateCell(i, j, k);
		}
	}

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		// prints initial and final conditions to screen
		Gol.printBoard();
		window.display();
		window.clear();
		
		// runs game of life for a number of generations
		while (RunGen)
		{
			// loop slows down program to be visible to human
			if (!FR)
			{
				// functions to play and display game
				Gol.countNeighbors();
				Gol.ApplyRules();
				window.clear();
				Gol.printBoard();
				window.display();

				// counts generations
				RunGen--;
				GenCount++;

				// resets framerate variable
				FR = 1000000000;
			}
			// decrements framerate variable
			else FR--;
		}
	}

	Gol.Print(First, Last, OFile, Cols, Rows, GenCount);
}
