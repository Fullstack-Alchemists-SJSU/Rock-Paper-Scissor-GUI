#include "GameEngine.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "SmartStrategy.h" // Include other strategy headers as needed
#include <iostream>

GameEngine::GameEngine(Player* human)
    : humanPlayer(human),
    computerPlayer(new ComputerPlayer(new SmartStrategy())),  // Initialize with SmartStrategy by default
    scoreHuman(0), scoreComputer(0), tieScore(0),
    humanChoice(' '), computerChoice(' ') {
}

void GameEngine::setStrategy(Strategy* newStrategy) {
    if (computerPlayer != nullptr) {
        computerPlayer->setStrategy(newStrategy);
    }
}

char GameEngine::getComputerPrediction() const {
    return computerPlayer->getPrediction();
}

GameEngine::~GameEngine() {
    delete humanPlayer;
    delete computerPlayer; // ComputerPlayer's destructor should delete its own strategy
}


int GameEngine::getHumanScore() const {
    return scoreHuman;
}
void GameEngine::setTotalRounds(int rounds) {
    totalRounds = rounds;
}

int GameEngine::getTotalRounds() const {
    return totalRounds;
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
    if (computerPlayer != nullptr) {
        return computerPlayer->makeChoice();
    }
    return ' ';  // Return a default value if computerPlayer is null
}

void GameEngine::humanPlayerMakesChoice(char choice) {
    humanChoice = choice;
    computerPlayer->makeChoice(); // Ensure computer makes a choice too, for consistency
}

char GameEngine::playNextRound() {
    return playRound();
}

char GameEngine::playRound() {
    computerChoice = computerPlayer->makeChoice();

    std::cout << "Human: " << humanChoice << " vs Computer: " << computerChoice << std::endl;

    char result;
    if ((humanChoice == 'R' && computerChoice == 'S') ||
        (humanChoice == 'S' && computerChoice == 'P') ||
        (humanChoice == 'P' && computerChoice == 'R')) {
        std::cout << "Human wins this chance!" << std::endl;
        result = 'H';
        scoreHuman++;
    } else if (humanChoice == computerChoice) {
        std::cout << "This chance is a tie!" << std::endl;
        result = 'T';
        tieScore++;
    } else {
        std::cout << "Computer wins this chance!" << std::endl;
        result = 'C';
        scoreComputer++;
    }

     roundCount++;
    if (roundCount >= totalRounds) {
        // Handle the end of the game, e.g., show results, disable inputs, etc.
        std::cout << "Game Over! Final Scores - Human: " << scoreHuman
                 << ", Computer: " << scoreComputer
                 << ", Ties: " << tieScore << std::endl;
    }
    lastResult = result; // Store the last result for retrieval
    return result;
}

void GameEngine::resetScores() {
    scoreHuman = 0;
    scoreComputer = 0;
    tieScore = 0;
}

