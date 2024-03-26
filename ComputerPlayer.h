#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include "Strategy.h"
#include "Player.h"
#include "RandomStrategy.h"  // Include the header of the default strategy

class ComputerPlayer : public Player {
private:
    Strategy* strategy;

public:
    // Update constructor to set a default strategy if none is provided
    explicit ComputerPlayer(Strategy* strategy = new RandomStrategy());
    ~ComputerPlayer();  // Don't forget the destructor to delete the strategy if it owns it

    char makeChoice() override;
    Strategy* getStrategy() const;  // Getter for the strategy
};

#endif // COMPUTERPLAYER_H
