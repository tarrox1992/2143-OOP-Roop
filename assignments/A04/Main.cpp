#include <SFML/Graphics.hpp>

using namespace sf;

struct golCell {
	bool isAlive;
	int neighborCount;
	RectangleShape Rect;
	int Width;
	int Height;

	golCell() {
		Width = 10;
		Height = 10;
		Rect.setSize(sf::Vector2f(Width, Height));
		Rect.setFillColor(Color::Green);
		Rect.setOutlineColor(Color::Black);
		Rect.setOutlineThickness(1);
	}

	void setCellPos(int x, int y) {
		Rect.setPosition(x*Width, y*Height);
	}

};

struct gameOfLife {
	int Width;
	int Height;
	// variables to keep window from updating on wrong frameCount
	int frameCount;
	int frameRate;
	RenderWindow Window;
	golCell** World;
	gameOfLife(int width, int height) {
		Width = width;
		Height = height;
		// hard codes frameRate and starting count
		frameCount = 0;
		frameRate = 50;
		Window.create(VideoMode(Width, Height), "Game of Life");

		World = new golCell*[height];

		for (int i = 0; i<height; i++) {
			World[i] = new golCell[width];
			for (int j = 0; j<width; j++) {
				World[i][j].setCellPos(i, j);
			}
		}
	}

	void drawWorld() {
		Window.clear();
		for (int i = 0; i<Height; i++) {
			for (int j = 0; j<Width; j++) {
				Window.draw(World[i][j].Rect);
			}
		}
		Window.display();
	}
};



int main() {

	gameOfLife Gol(1000, 1000);

	while (Gol.Window.isOpen())
	{
		//srand(1);
		Event event;
		//int i, j;

		while (Gol.Window.pollEvent(event))
		{
			//stuff I was experimenting with
			//i = rand() % 100;
			//j = rand() % 100;
			//Gol.World[i][j].Rect.setFillColor(Color::Magenta);

			// will keep window from updating if not on right frameCount
			if (Gol.frameCount == Gol.frameRate)
			{
				Gol.drawWorld();
				if (event.type == Event::Closed)
					Gol.Window.close();
				// resets frameCount
				Gol.frameCount = 0;
			}
			//increments frameCount if not updating window
			else Gol.frameCount++;
		}


	}

	return 0;
}
