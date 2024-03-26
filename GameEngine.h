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

    char playRound();

public:
    explicit GameEngine(Player* human);
    ~GameEngine();

    void setStrategy(Strategy* strategy);
    void humanPlayerMakesChoice(char choice);
    char playNextRound();
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


};

#endif // GAMEENGINE_H
