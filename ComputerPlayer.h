#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include "Player.h"
#include "Strategy.h"

class ComputerPlayer : public Player {
private:
    Strategy* strategy;
   char lastChoice;  // Add a member to store the last choice
public:
    explicit ComputerPlayer(Strategy* strategy);
    virtual ~ComputerPlayer();
    char makeChoice() override;
    void setStrategy(Strategy* newStrategy); // Method to change the strategy
    Strategy* getStrategy() const;
    char getLastChoice() const;  // Add this method
};

#endif // COMPUTERPLAYER_H
