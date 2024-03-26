#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Player.h"
#include "Strategy.h"

class GameEngine {
private:
    Player* humanPlayer;
    Player* computerPlayer;
    Strategy* strategy;
    int scoreHuman;
    int scoreComputer;
    int tieScore;  // Add this line to declare tieScore
    char humanChoice;
    char computerChoice;

    // Helper method to play a single round
    char playRound();

public:
    GameEngine(Player* human, Strategy* strategy);
    ~GameEngine();

    void humanPlayerMakesChoice(char choice);
    char playNextRound();
    void playGame();
    void resetScores();

    int getHumanScore() const;
    int getComputerScore() const;
    int getTieScore() const;
    char getHumanChoice() const;
    char getComputerChoice() const;

    void playRoundOfThree(); // If you have this method for playing a set of three chances
};

#endif // GAMEENGINE_H

/*
 #ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Player.h"
#include "Strategy.h"

class GameEngine {
private:
    Player* humanPlayer;
    Player* computerPlayer;
    Strategy* strategy;
    int scoreHuman;
    int scoreComputer;
    char humanChoice; // Store the human player's choice
    char computerChoice; // Store the computer player's choice

    // Helper method to play a single round
    char playRound();

public:
    GameEngine(Player* human, Strategy* strategy);
    ~GameEngine();

    void humanPlayerMakesChoice(char choice);
    char playNextRound();
    void playGame();
    void resetScores();

    // Getters for the scores
    int getHumanScore() const;
    int getComputerScore() const;
    int getTieScore() const; // If you have a tie score, you'll need to track it

    char getHumanChoice() const;
    char getComputerChoice() const;
};

#endif // GAMEENGINE_H
*/
