#include "ComputerPlayer.h"

ComputerPlayer::ComputerPlayer(Strategy* strategy)
    : strategy(strategy) {}

ComputerPlayer::~ComputerPlayer() {
    delete strategy;  // Ensure we do not have a memory leak
}

char ComputerPlayer::makeChoice() {
    return strategy->makeChoice();
}

Strategy* ComputerPlayer::getStrategy() const {
    return strategy;
}
