// include/RandomStrategy.h
#ifndef RANDOMSTRATEGY_H
#define RANDOMSTRATEGY_H

#include "Strategy.h"
#include <cstdlib> // For std::rand() and std::srand()
#include <ctime>   // For std::time()

class RandomStrategy : public Strategy {
public:
    RandomStrategy();
    char makeChoice() override;
    void updateState(char humanChoice) override;
};

#endif // RANDOMSTRATEGY_H
