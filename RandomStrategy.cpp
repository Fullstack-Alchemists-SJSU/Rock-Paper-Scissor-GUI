// src/RandomStrategy.cpp
#include "RandomStrategy.h"
#include <iostream>

RandomStrategy::RandomStrategy() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

char RandomStrategy::makeChoice() {
    int randomNum = std::rand() % 3;
    switch (randomNum) {
        case 0:
            return 'R'; // Rock
        case 1:
            return 'P'; // Paper
        case 2:
            return 'S'; // Scissors
        default:
            return 'R'; // Default case, should never be reached
    }
}

void RandomStrategy::updateState(char humanChoice) {
	// No impl needed
}

