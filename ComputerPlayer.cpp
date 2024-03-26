#include "ComputerPlayer.h"

ComputerPlayer::ComputerPlayer(Strategy* strategy)
    : strategy(strategy) {}

ComputerPlayer::~ComputerPlayer() {
    delete strategy; // Ensure we do not have a memory leak
}

char ComputerPlayer::makeChoice() {
    lastChoice = strategy->makeChoice();  // Store the last choice
    return lastChoice;
}

char ComputerPlayer::getLastChoice() const {
    return lastChoice;
}
// In ComputerPlayer.cpp
void ComputerPlayer::setStrategy(Strategy* newStrategy) {
    if (strategy != nullptr) {
        delete strategy; // Careful with memory management here
    }
    strategy = newStrategy;
}

Strategy* ComputerPlayer::getStrategy() const {
    return strategy;
}


