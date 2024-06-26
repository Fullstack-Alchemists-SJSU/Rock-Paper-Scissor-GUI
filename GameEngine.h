#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Player.h"
#include "ComputerPlayer.h"  // Include ComputerPlayer
#include "Strategy.h"
#include "SmartStrategy.h"   // Include if you're using SmartStrategy in GameEngine
#include "RandomStrategy.h"  // Include if you're using RandomStrategy in GameEngine

class GameEngine {
private:
    Player* humanPlayer;
    ComputerPlayer* computerPlayer;  // Use ComputerPlayer type for specific strategy handling
    Strategy* strategy;
    int scoreHuman;
    int scoreComputer;
    int tieScore;
    char humanChoice;
    char computerChoice;
    char lastResult;


    int roundCount; // Make sure this is declared in the class definition
    int totalRounds;

public:
    explicit GameEngine(Player* human);
    ~GameEngine();

    void setStrategy(Strategy* strategy);
    void humanPlayerMakesChoice(char choice);
    char playNextRound();
    char playRound();
    void playGame();
    void resetScores();

    int getHumanScore() const;
    int getComputerScore() const;
    int getTieScore() const;
    char getHumanChoice() const;
    char getComputerChoice() const;
    char getResult() const;
    char getComputerPrediction() const;
    void playRoundOfThree();
    void setTotalRounds(int rounds);
    int getTotalRounds() const;


};

#endif // GAMEENGINE_H
