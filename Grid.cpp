#include "Grid.h"
#include <raylib.h>
#include "constants.h"
#include <iostream>

Grid::Grid(WordleSolver& solver) :solverBot(solver),gridMatrix(numRows, std::vector<char>(numCols, ' ')),
currRow{ 0 }, currCol{ 0 }, colorMatrix(numRows, std::vector<int>(numCols, 0)) ,colors({wrongColor,misplacedColor,correctColor})
{	
	letterFont = GetFontDefault();
};
Grid::~Grid() {
	UnloadFont(letterFont);
}
void Grid::DrawGrid() {
	int x{};
	int y{};
	for (int i{ currRow }; i < numRows; i++) 
	{
		for (int j{ 0 }; j < numCols; j++)
		{
			x = gridOffsetX + j * (cellSize + cellMargin);
			y = gridOffsetY + i * (cellSize + cellMargin);
			Rectangle rec = { x,y,cellSize,cellSize };
			DrawRectangleLines(x, y, cellSize, cellSize, gridLineColor);

		}
	}
}

	void Grid::CheckForInput() {
		int keyPress = GetKeyPressed();
		
		if (IsAlphabet(keyPress) && currRow < numRows && currCol < numCols)
		{

			gridMatrix[currRow][currCol] = 'A' + (keyPress - KEY_A);
			currCol += 1;
			
		}
		else if (keyPress == KEY_ENTER && currRow<numRows && currCol>=numCols)
		{
			std::string guess(gridMatrix[currRow].begin(), gridMatrix[currRow].end());
			solverBot.MakeAGuess(guess,colorMatrix[currRow]);
			currCol =0;
			currRow += 1;

		}
		else if (keyPress == KEY_BACKSPACE && currCol > 0)
		{
			gridMatrix[currRow][currCol-1] = ' ';
			colorMatrix[currRow][currCol - 1] = 0;
			currCol -= 1;
		}
		else if (keyPress == KEY_SPACE && currCol>0)
		{
			int currColor = colorMatrix[currRow][currCol-1];
			if (currColor >= 2)
			{
				currColor = 0;
			}
			else {
				currColor += 1;
			}
			colorMatrix[currRow][currCol-1] = currColor;
		}

	}
	bool Grid::IsAlphabet(int key) {
		return (key >= KEY_A && key <= KEY_Z);
	}

	void Grid::DrawLetters() {
		Vector2 position{};
		Vector2 letterDimension{};
		char letter{};
		for (int row{ 0 }; row < numRows; row++)
		{
			for (int col{ 0 }; col < numCols; col++) {
				letter = gridMatrix[row][col];
				
				if (letter != ' ')
				{
					char text[2] = { letter, '\0' };
					letterDimension = MeasureTextEx(letterFont, text,letterSize,letterSpacing );
					position.x = gridOffsetX + col * (cellSize + cellMargin)+ (cellSize - letterDimension.x) / 3;
					position.y = gridOffsetY + row* (cellSize + cellMargin)+ (cellSize - letterDimension.y) / 3;
					DrawTextEx(letterFont, text, position,letterSize, letterSpacing, WHITE);
				}
			}
		}
	}
	void Grid::ColorGrid() {
		int colorCode{};
		int x{};
		int y{};
		for (int row{ 0 }; row < numRows; row++)
		{
			for (int col{ 0 }; col < numCols; col++) {
				colorCode = colorMatrix[row][col];
				if (colorCode == 0)
					continue;
				x = gridOffsetX + col * (cellSize + cellMargin);
				y = gridOffsetY + row * (cellSize + cellMargin);
				DrawRectangle(x,y, cellSize, cellSize, colors[colorCode]);
			}
		}
	}
	void Grid::GridUpdate() {
		this->CheckForInput();
		this->ColorGrid();
		this->DrawLetters();
	}
