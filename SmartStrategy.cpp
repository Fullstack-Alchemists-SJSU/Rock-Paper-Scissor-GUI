// src/SmartStrategy.cpp
#include "SmartStrategy.h"
#include <algorithm>
#include <iostream>
#include <random>

SmartStrategy::SmartStrategy() {
    loadFrequencies();
}

SmartStrategy::~SmartStrategy() {
    saveFrequencies();
}

char SmartStrategy::makeChoice() {
    if (recentChoices.size() < N - 1) {
        // Not enough data to predict; use a random choice
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, 2);
        char choices[] = {'R', 'P', 'S'};
        return choices[distrib(gen)];
    } else {
        return predictNextMove(); // Predict based on history
    }
}

void SmartStrategy::updateState(char humanChoice) {
	std::cout << "INSIDE SmartStrategy::updateState" << std::endl;
	recentChoices.push_back(humanChoice);
	// Ensure recentChoices does not exceed N characters
	if (recentChoices.size() > N) {
		recentChoices.erase(recentChoices.begin());
	}

	std::string recentChoicesStr(recentChoices.begin(), recentChoices.end());
    // Update frequencies locally
	choiceFrequencies[recentChoicesStr]++;
}

void SmartStrategy::loadFrequencies() {
    fileManager.loadFrequencies("frequencies.txt", choiceFrequencies);
}

void SmartStrategy::saveFrequencies() {
    fileManager.saveFrequencies("frequencies.txt", choiceFrequencies);
}

std::string SmartStrategy::getRecentSequence() {
    // Convert the last N-1 choices to a string (exclude the very last choice)
    return std::string(recentChoices.begin(), recentChoices.end() - 1);
}

char SmartStrategy::predictNextMove() {
    std::string recentSequence = getRecentSequence(); // Get the last N-1 choices as a string
    char mostProbableChoice = 'R'; // Default choice
    int highestFrequency = 0;

    // Iterate over choiceFrequencies to find the sequence with the highest frequency
    // that starts with the recentSequence
    for (const auto& pair : choiceFrequencies) {
        std::string sequence = pair.first.substr(0, pair.first.size() - 1);
        char choice = pair.first.back();
        int frequency = pair.second;

        if (sequence == recentSequence && frequency > highestFrequency) {
            highestFrequency = frequency;
            mostProbableChoice = choice;
        }
    }

    // Predict the human player's next move based on the most frequent past sequence
    // and choose the winning move against it
    if (highestFrequency == 0) {
        // If no matching sequence found, make a random choice
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, 2);
        char choices[] = {'R', 'P', 'S'};
        return choices[distrib(gen)];
    } else {
        // Choose the winning move against the predicted move
        if (mostProbableChoice == 'R') return 'P'; // Paper covers rock
        if (mostProbableChoice == 'P') return 'S'; // Scissors cut paper
        if (mostProbableChoice == 'S') return 'R'; // Rock crushes scissors
    }

    // Fallback, should not be reached due to the logic covering all cases
    return 'R';
}

