#include "WordleUtils.h"


VectorStrings possibleWords()
{
    /*
    Reading out all the five letter words in english language
    */

    std::ifstream inputFile("./FiveLetterWords.txt");
    VectorStrings words;
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

VectorStrings relativeFrequencyCount() {
    /*
    The second guess take a few seconds many a times and to deal with this whenever the first guess has not reduced the word
    count a lot we shall find the best guess by using relative frequency rather than entropy
    */
    VectorStrings words;
    const std::string& file_path = "relativeFreq.txt";
    std::ifstream file(file_path); 

    if (!file.is_open()) {
        std::cerr << "Could not open the file: " << file_path << std::endl;
        return words; // Return empty vector if file cannot be opened
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string word;
        std::getline(ss, word, ','); // Get the word before the comma
        words.push_back(word);      
    }

    file.close(); 
    return words;

}

int feedback_generator(const std::string& guess, const std::string& answer)
{
    /* Generate a feedback on comparing two words eg [2,0,1,1,0]
        Gray - (0)
        Yellow -(1)
        Green -(2)
        Then convert that into a base 3 number for easier comparison and memory optimization rather than storing it as an array
    */

    std::array <int, 5> feedback_array{};
    std::array <bool, 5> character_is_used{};

    // Green Case
    for (int i{ 0 }; i < 5; i++)
    {
        if (guess[i] == answer[i])
        {
            feedback_array[i] = 2;
            character_is_used[i] = true;
        }
    }
    //Yellow Case
    for (int i{ 0 }; i < 5; i++)
    {
        if (feedback_array[i] == 2)
            continue;
        for (int j{ 0 }; j < 5; j++)
        {
            if (character_is_used[j])
                continue;
            if (guess[i] == answer[j]) {
                feedback_array[i] = 1;
                character_is_used[j] = true;
                break;
            }
        }
    }

    //Convert feedback array into a ternary number

    int ternaryNumber = 0;
    int multiplying_factor = 1;
    for (int i{ 4 }; i >= 0; i--)
    {

        ternaryNumber += feedback_array[i] * multiplying_factor;
        multiplying_factor *= 3;

    }

    return ternaryNumber;
}


double calculate_entropy(const std::string& word, VectorStrings& words)
{
    /*
    Loop through all patterns find the entropy for each case then find the average using
     the summation of product of probability and informations bits
     Since we have made our feedback into a base 3 number there could be 0 to 242 possible patterns
     but not all patterns are valid,invalid patterns would have no words that have that feedback so we can
     skip those patterns by checking if number of elements returned is zero
    */

    const int MAX{ 242 };
    int num_elements{};
    double entropy{};
    double probability{};
    double bits{};
    for (int i = 0; i < MAX + 1; i++)
    {
        num_elements = 0;
        for (auto& w : words)
        {
            if (feedback_generator(word, w) == i)
                num_elements += 1;
        }
        if (num_elements == 0)
            continue;

        probability = static_cast<double>(num_elements) / words.size();
        bits = -1 * static_cast<double>(log2(probability));
        entropy += (probability * bits);
    }
    return entropy;
}





VectorStrings get_best_guesses(VectorStrings& words,VectorStrings& wordsFreqRanked)
{
    /*
    Except for the first guess which would take a long time to calculate the  second guess
     onwards the number of possible combinations reduce by a ton hence only the first guess was precalculated
     and stored onto a file and we use those directly for first guess.

     For second Guess we will use the highest used word in english alphabet rather than entropy if words list size is bigger
     than a certain amount
    */
    int size = words.size();
    if (size > maxListSize) {
        //Do relative frequency
        return (getTopTenWordsRelative(words,wordsFreqRanked));
    }



    // Min-heap to store top 10 words and their values
    auto start = std::chrono::high_resolution_clock::now();

    using Pair = std::pair<double, std::string>;
    auto cmp = [](const Pair& a, const Pair& b) { return a.first > b.first; };
    std::priority_queue<Pair, std::vector<Pair>, decltype(cmp)> min_heap(cmp);

    for (int i = 0; i < size; i++)
    {
        const std::string& word = words[i];
        double value = calculate_entropy(word,words);
        min_heap.emplace(value, word);
        if (min_heap.size() > 10) {
            min_heap.pop();
        }
    }


    // Collect the top words from the min-heap
    VectorStrings top_words;
    while (!min_heap.empty()) {
        top_words.push_back(min_heap.top().second);
        min_heap.pop();
    }
    // Rank Based on relative frequency
    rankStrings(top_words, wordsFreqRanked);
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the elapsed time in milliseconds
    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << "Execution time: " << elapsed.count() << " ms" << std::endl;
    
    return top_words;
}

void rankStrings(VectorStrings& strings, const VectorStrings& rankedWords) {
    // Step 1: Create a map to store the rank of each word based on its position in rankedWords
    std::unordered_map<std::string, int> rankMap;
    for (int i = 0; i < rankedWords.size(); ++i) {
        rankMap[rankedWords[i]] = i; // Assigning the index as the rank
    }

    // Step 2: Sort the strings in place using a custom comparator
    std::sort(strings.begin(), strings.end(), [&](const std::string& a, const std::string& b) {
        int rankA = rankMap.count(a) ? rankMap[a] : rankedWords.size(); // Last if not found
        int rankB = rankMap.count(b) ? rankMap[b] : rankedWords.size(); 
        return rankA < rankB; // Sort based on rank (lower is better)
        });
}


VectorStrings getTopTenWordsRelative(VectorStrings& words,VectorStrings& wordsFreqRanked) {
    /* Used for the second guess in case wordsList size exceeds certain limit */
    VectorStrings finalTen{};
    std::unordered_set<std::string> set2(words.begin(),words.end());
    for (auto& word : wordsFreqRanked) {
        if (set2.find(word) != set2.end()) {
            finalTen.push_back(word);
            if (finalTen.size() == 10) {
                break;
            }
        }
    }
    return finalTen;
}



VectorStrings reduce_list(const std::string& guess, int feedback, VectorStrings& words) {
    /*
    Filter out all the words that dont match the feedback with the guess to shrink out our list.
    */
    VectorStrings new_list{};
    for (auto& w : words)
    {
        if (feedback_generator(guess, w) == feedback)
        {
            new_list.push_back(w);
        }
    }
    return new_list;
}