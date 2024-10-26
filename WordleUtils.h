#pragma once
#include <string>     
#include <vector>  
#include <boost/container/flat_map.hpp>
#include <boost/unordered_set.hpp>
#include <unordered_set>
#include "constants.h"
#include <unordered_map>
#include <chrono>
#include <filesystem>
#include <iostream>  
#include <fstream>       
#include <array>
#include <cmath>
#include <queue>
#include <utility>
#include <algorithm>

using WordPatternMap = boost::container::flat_map<int, boost::unordered_set<std::string>>;
using PatternDict = boost::container::flat_map<std::string, WordPatternMap>;
using VectorStrings = std::vector<std::string>;
using WordPair = std::pair<std::string, std::string>;



VectorStrings possibleWords();
int feedback_generator(const std::string& guess, const std::string& answer);
double calculate_entropy(const std::string& word, VectorStrings& words);
VectorStrings get_best_guesses(VectorStrings& words,VectorStrings& wordsFreqRanked);
VectorStrings reduce_list(const std::string& guess, int feedback, VectorStrings& words);
VectorStrings getTopTenWordsRelative(VectorStrings& words,VectorStrings& wordsFreqRanked);
VectorStrings relativeFrequencyCount();
void rankStrings(VectorStrings& strings, const VectorStrings& rankedWords);