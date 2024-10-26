#include "Simulation.h"
#include "WordleUtils.h"
Simulation::Simulation() :answers{ GetAnswers() } {
	
}
void Simulation::StartSimulation() {
	std::string Guess; 
    int feedback=0;
    int score;
    int averageSum{};
    float averageScore{};
    VectorStrings words{};
    VectorStrings bestGuess{};
    VectorStrings anomalies{};
    VectorStrings wordsFreqRanked = relativeFrequencyCount();
    int count = 0;
    std::cout << "Started" << "\n";
    for (auto& ans : answers)
    {
        Guess = "tares";
        count += 1;
        words = possibleWords();
        
        score = 0;
        feedback = 0;
        while (feedback != 242)
        {

            feedback = feedback_generator(Guess, ans);
            score += 1;
            words=reduce_list(Guess, feedback, words);
            bestGuess= get_best_guesses(words,wordsFreqRanked);
            if (bestGuess.empty()) {
                score = 10;
                break;
            }
            Guess = bestGuess[0];
        }
        
        if (score <= 6)
        {
            averageSum += score;
        }
        else {
            anomalies.push_back(ans);
        }
        std::cout << "Score : " << score << " for ans: " <<ans<< "\n";
        std::cout << "Completed: " << count << " / " << answers.size() << "\n";
        
    }
    averageScore = averageSum / static_cast<float>(answers.size());

    std::ofstream outputFile;
    outputFile.open("./Stats.txt", std::ios::app); // Append mode

    if (!outputFile) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }

    outputFile << "Score: " << averageScore << "\n";
    outputFile << "Anomalies: ";
    for (size_t i = 0; i < anomalies.size(); ++i) {
        outputFile << anomalies[i];
        if (i < anomalies.size() - 1) {
            outputFile << ", "; // Comma-separated
        }
    }
    outputFile.close();
}




std::vector<std::string> Simulation::GetAnswers() {

    std::ifstream inputFile("./simulationWords.txt");
    std::vector<std::string> words;
    if (inputFile.is_open()) {
        std::string line;

        while (std::getline(inputFile, line)) {
            words.push_back(line);
        }

        inputFile.close();
    }
    else {
        std::cout << "Failed to open the file." << std::endl;
    }

    return words;
}