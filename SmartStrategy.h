// include/SmartStrategy.h
#ifndef SMARTSTRATEGY_H
#define SMARTSTRATEGY_H

#include "Strategy.h"
#include "FileManager.h"
#include <vector>
#include <map>
#include <string>

class SmartStrategy : public Strategy {
private:
    std::vector<char> recentChoices;
    std::map<std::string, int> choiceFrequencies;
    static const int N = 5; // The number of choices to remember
    FileManager fileManager;

    std::string getRecentSequence(); // Helper to get the last N-1 choices as a string
    char predictNextMove(); // Predicts the next human move based on frequencies

public:
    SmartStrategy();
    virtual ~SmartStrategy();
    char makeChoice() override;
    void updateState(char humanChoice) override;
    void updateHistory(char humanChoice, char computerChoice);
    void loadFrequencies();
    void saveFrequencies();
};

#endif // SMARTSTRATEGY_H
