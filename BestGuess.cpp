#include "BestGuess.h"
#include <raylib.h>
#include "constants.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
BestGuess::BestGuess(): topPicks(GetBestFirstGuess()) {
    wordFont = GetFontDefault();
}

void BestGuess::DrawHeading() {
	const char* heading = "Top Picks";
	int gridWidth = numCols * (cellSize + cellMargin);
	int textX = gridOffsetX + gridWidth + headingMarginX;
	int textY = gridOffsetY -cellSize;
	DrawText(heading, textX, textY, headingSize, headingColor);
}

std::vector<std::string> BestGuess::GetBestFirstGuess() {
    /*
    Gets the best first guess from the precalculated vector which is printed onto firstGuess.txt
    */
    std::ifstream inputFile("./firstGuess.txt");
    std::vector<std::string> guesses;

    if (!inputFile) {
        std::cerr << "Error opening file: "  << std::endl;
        return guesses;
    }

    std::string firstGuess;
    while (std::getline(inputFile, firstGuess) && guesses.size() < 10) {
        guesses.push_back(firstGuess);
    }

    inputFile.close(); 
    return guesses;
}

void BestGuess::DrawTopPicks() {
    int gridWidth = numCols * (cellSize + cellMargin);
    Vector2 position{};
    position.x = gridOffsetX + gridWidth + headingMarginX +guessMarginX;
    position.y = gridOffsetY;
    int spacing = 40;
    const char* words;
    for (auto& picks : topPicks) {
        words = TextToUpper(picks.c_str());
        DrawTextEx(wordFont,words, position, guessSize,guessSpacing, WHITE);
        position.y += spacing;
    }

}

void BestGuess::UpdateTopPicks(std::vector<std::string>& newPick ) {
    this->topPicks = newPick;
}