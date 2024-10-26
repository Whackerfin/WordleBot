#include "WordleSolver.h"
#include <iostream>
#include <algorithm>
WordleSolver::WordleSolver(BestGuess& bestGuess):guessHolder(bestGuess) {
	words = possibleWords();
	wordsFreqRanked = relativeFrequencyCount();
	std::cout << "Initialized" << std::endl;
}
void WordleSolver::MakeAGuess(std::string& guess, std::vector<int>& colorVector) {

	//Calculate feedback in ternary
	if (guess == "") {
		return;
	}
	int ternaryNumber = 0;
	int multiplying_factor = 1;
	for (int i{ 4 }; i >= 0; i--)
	{

		ternaryNumber +=colorVector[i] * multiplying_factor;
		multiplying_factor *= 3;

	}
	// Convert to lowercase in place
	std::transform(guess.begin(), guess.end(), guess.begin(),
		[](unsigned char c) { return std::tolower(c); });
	//Reduce the list
	words = reduce_list(guess, ternaryNumber, words);
	std::cout << words.size() << std::endl;
	std::cout << ternaryNumber << std::endl;
	VectorStrings newTopGuess = get_best_guesses(words,wordsFreqRanked);
	guessHolder.UpdateTopPicks(newTopGuess);
	
}

