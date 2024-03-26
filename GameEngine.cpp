#include "GameEngine.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include <iostream>

GameEngine::GameEngine(Player* human, Strategy* strategy)
    : humanPlayer(human), computerPlayer(new ComputerPlayer(strategy)),
    strategy(strategy), scoreHuman(0), scoreComputer(0), tieScore(0),
    humanChoice(' '), computerChoice(' ') {}

GameEngine::~GameEngine() {
    delete humanPlayer;
    delete computerPlayer;
}

int GameEngine::getHumanScore() const {
    return scoreHuman;
}

int GameEngine::getComputerScore() const {
    return scoreComputer;
}

int GameEngine::getTieScore() const {
    return tieScore;
}

char GameEngine::getHumanChoice() const {
    return humanChoice;
}

char GameEngine::getComputerChoice() const {
    return computerChoice;
}

void GameEngine::humanPlayerMakesChoice(char choice) {
    humanChoice = choice;
}

void GameEngine::playGame() {
    playRoundOfThree();
}
char GameEngine::playNextRound() {
    return playRound(); // Calls the private playRound method
}


void GameEngine::playRoundOfThree() {
    int humanWins = 0, computerWins = 0;

    for (int chance = 0; chance < 3; ++chance) {
        // Assume humanPlayerMakesChoice(char choice) is called before this method
        char result = playRound();

        switch (result) {
        case 'H': humanWins++; break;
        case 'C': computerWins++; break;
        case 'T': tieScore++; break;
        }
    }

    if (humanWins > computerWins) {
        scoreHuman++;
    } else if (computerWins > humanWins) {
        scoreComputer++;
    } else {
        tieScore++;
    }
}



char GameEngine::playRound() {
    computerChoice = computerPlayer->makeChoice();  // Get the computer's choice

    std::cout << "Human: " << humanChoice << " vs Computer: " << computerChoice << std::endl;

    if ((humanChoice == 'R' && computerChoice == 'S') ||
        (humanChoice == 'S' && computerChoice == 'P') ||
        (humanChoice == 'P' && computerChoice == 'R')) {
        std::cout << "Human wins this chance!" << std::endl;
        return 'H';
    } else if (humanChoice == computerChoice) {
        std::cout << "This chance is a tie!" << std::endl;
        return 'T';
    } else {
        std::cout << "Computer wins this chance!" << std::endl;
        return 'C';
    }
}

void GameEngine::resetScores() {
    scoreHuman = 0;
    scoreComputer = 0;
    tieScore = 0;
}


/*
// src/GameEngine.cpp
#include "GameEngine.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include <iostream>

// Constructor
GameEngine::GameEngine(Player* human, Strategy* strategy)
    : humanPlayer(human), computerPlayer(new ComputerPlayer(strategy)),
    strategy(strategy), scoreHuman(0), scoreComputer(0), humanChoice(' '), computerChoice(' ') {}

// Destructor
GameEngine::~GameEngine() {
    delete humanPlayer;
    delete computerPlayer;
}


int GameEngine::getHumanScore() const {
    return scoreHuman;
}

int GameEngine::getComputerScore() const {
    return scoreComputer;
}

int GameEngine::getTieScore() const {
    // Assuming you have a variable to track ties, return it
    // If you don't currently track ties, you will need to add this functionality
    return 0; // Placeholder, replace with actual tie score variable
}

char GameEngine::getHumanChoice() const {
    return humanChoice;
}

char GameEngine::getComputerChoice() const {
    return computerChoice;
}
void GameEngine::humanPlayerMakesChoice(char choice) {
    humanChoice = choice; // Store the human player's choice
}

char GameEngine::playNextRound() {
    return playRound(); // Calls the private playRound method
}

// The method to play one round of the game
char GameEngine::playRound() {
    // No need to call humanPlayer->makeChoice() again, use humanChoice
    char humanChoice = this->humanChoice;
    computerChoice = computerPlayer->makeChoice();  // Store the choice for later retrieval

    std::cout << "Human: " << humanChoice << " vs Computer: " << computerChoice << std::endl;

    if ((humanChoice == 'R' && computerChoice == 'S') ||
        (humanChoice == 'S' && computerChoice == 'P') ||
        (humanChoice == 'P' && computerChoice == 'R')) {
        scoreHuman++;
        return 'H';
    } else if (humanChoice == computerChoice) {
        // Update tie score if you have a member variable for it
        return 'T';
    } else {
        scoreComputer++;
        return 'C';
    }
}


// The method to play the game for 20 rounds
void GameEngine::playGame() {
    std::cout << "Starting the Rock-Paper-Scissors game!" << std::endl;

    for (int round = 1; round <= 20; ++round) {
        std::cout << "Round " << round << std::endl;
        playRound();
    }

    std::cout << "Final score - Human: " << scoreHuman << " Computer: " << scoreComputer << std::endl;

    if (scoreHuman > scoreComputer) {
        std::cout << "Human wins the game!" << std::endl;
    } else if (scoreHuman < scoreComputer) {
        std::cout << "Computer wins the game!" << std::endl;
    } else {
        std::cout << "The game is a tie!" << std::endl;
    }
}


void GameEngine::resetScores() {
    scoreHuman = 0;
    scoreComputer = 0;
    // Reset any other necessary game state here
}*/
