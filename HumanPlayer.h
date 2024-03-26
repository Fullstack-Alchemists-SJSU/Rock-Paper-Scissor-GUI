// include/HumanPlayer.h
#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.h"
#include <iostream>

class HumanPlayer : public Player {
public:
    char makeChoice() override; // Only declare the method here
};

#endif // HUMANPLAYER_H
