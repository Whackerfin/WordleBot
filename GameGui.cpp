#include "GameGui.h"
void GameGui::StartGame() {

	BestGuess guess = BestGuess();
	WordleSolver wordleBot = WordleSolver(guess);
	Grid grid = Grid(wordleBot);

	InitWindow(windowWidth, windowHeight, "Wordle Bot");
	SetTargetFPS(60);
	while (WindowShouldClose() == false)
	{
		BeginDrawing();
		ClearBackground(backgroundColor);
		guess.DrawHeading();
		guess.DrawTopPicks();
		grid.DrawGrid();
		grid.GridUpdate();
		EndDrawing();
	}
	CloseWindow();
}