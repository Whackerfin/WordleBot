#include "constants.h"

//Colors
const Color backgroundColor = { 18,18,19,255 };
const Color correctColor = {97,140,85,255};
const Color misplacedColor = {177,160,76,255};
const Color wrongColor = backgroundColor;
const Color gridLineColor = {58,58,60,255};
const Color headingColor = { 135,206,235,255 };

//Dimensions
const int windowWidth = 1000;
const int windowHeight = 700;
const int gridOffsetX = 100;
const int gridOffsetY = 150;
const int cellSize = 75;
const int cellMargin = 7;
const int headingMarginX = 200;
const int guessMarginX = 30;

//Text
const float letterSize = 40.0f;
const float letterSpacing = 1.0f;
const float headingSize = 30.0f;
const float guessSize = 28.0f;
const float guessSpacing = 6.0f;


//Grid size
const int numRows = 6;
const int numCols = 5;

//Wordle Solver Constrains
const int  maxListSize = 200;