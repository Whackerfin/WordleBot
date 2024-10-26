#pragma once
#include <vector>
#include <string>
#include <raylib.h>
class BestGuess {
public:
	void UpdateTopPicks(std::vector<std::string>& newPick);
	void DrawHeading();
	void DrawTopPicks();
	BestGuess();
private:
	Font wordFont;
	std::vector<std::string> GetBestFirstGuess();
	std::vector<std::string> topPicks;
};
