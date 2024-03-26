// include/Player.h
#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    virtual ~Player() {} // Virtual destructor to allow for proper subclass destruction
    virtual char makeChoice() = 0; // Pure virtual function for making a choice ('R', 'P', or 'S')
};

#endif // PLAYER_H
