#pragma once
#include <vector>
#include <raylib.h>
#include "WordleSolver.h"
#include <string>
class Grid {
private:
	int currRow;
	int currCol;
	std::vector<Color> colors;
	bool IsAlphabet(int key);
	void CheckForInput();
	void DrawLetters();
	void ColorGrid();
	WordleSolver& solverBot;
	Font letterFont;
public:
	std::vector<std::vector<char>> gridMatrix;
	std::vector<std::vector<int>> colorMatrix;
	Grid(WordleSolver& solver);
	~Grid();
	void DrawGrid();
	void GridUpdate();
};