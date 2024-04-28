#include "GameEngine.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "SmartStrategy.h" // Include other strategy headers as needed

#include <iostream>

GameEngine::GameEngine(Player* human)
    : humanPlayer(human),
    computerPlayer(new ComputerPlayer(new RandomStrategy())),  // Initialize with SmartStrategy by default
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
    std::cout << "Total Rounds = " << totalRounds << "\n";
}

int GameEngine::getTotalRounds() const {
    std:: cout<<"Total Rounds =" << totalRounds << "\n";
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
    return computerChoice;  // Just return the stored choice
}

void GameEngine::humanPlayerMakesChoice(char choice) {
    humanChoice = choice;
    computerChoice = computerPlayer->makeChoice(); // Generate and store the computer choice immediately
}

char GameEngine::playNextRound() {
    if (roundCount < totalRounds) {
        std::cout << "Round " << (roundCount + 1) << "/" << totalRounds << std::endl;
        return playRound();
    } else {
        std::cout << "All rounds completed. Game Over!" << std::endl;
        return 'E'; // Indicate that all rounds are completed
    }
}

char GameEngine::playRound() {
    char result;

    // No need to get computer choice here, as it's already stored

    std::cout << "\nHuman: " << humanChoice << " vs Computer: " << computerChoice << std::endl;

    // Determine the winner based on humanChoice and computerChoice
    if ((humanChoice == 'R' && computerChoice == 'S') ||
        (humanChoice == 'S' && computerChoice == 'P') ||
        (humanChoice == 'P' && computerChoice == 'R')) {
        std::cout << "Human wins this round!" << std::endl;
        scoreHuman++;
        result = 'H'; // Human wins
    } else if (humanChoice == computerChoice) {
        std::cout << "This round is a tie!" << std::endl;
        tieScore++;
        result = 'T'; // Tie
    } else {
        std::cout << "Computer wins this round!" << std::endl;
        scoreComputer++;
        result = 'C'; // Computer wins
    }

    return result;
}

void GameEngine::resetScores() {
    scoreHuman = 0;
    scoreComputer = 0;
    tieScore = 0;
}

