// include/Strategy.h
#ifndef STRATEGY_H
#define STRATEGY_H

class Strategy {
public:
    virtual ~Strategy() {}
    virtual char makeChoice() = 0;
    virtual char predictNextMove() = 0;
    virtual void updateState(char humanChoice) { /* Empty default implementation */ }
};

#endif // STRATEGY_H
