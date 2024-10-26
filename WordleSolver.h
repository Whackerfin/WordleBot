#pragma once
#include "WordleUtils.h"
#include <string>
#include <vector>
#include "BestGuess.h"
#include <raylib.h>
class WordleSolver {
public:
	WordleSolver(BestGuess& bestGuess);
	VectorStrings words;
	VectorStrings wordsFreqRanked;
	void MakeAGuess(std::string& guess,std::vector<int>& colorVector);
	
private:
	BestGuess& guessHolder;
};