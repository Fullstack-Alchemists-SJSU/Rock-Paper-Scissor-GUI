// src/HumanPlayer.cpp
#include "HumanPlayer.h"
#include <iostream>

char HumanPlayer::makeChoice() {
    char choice;
    std::cout << "Enter your choice (R, P, S): ";
    std::cin >> choice;
    return choice;
}
