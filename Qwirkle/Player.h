#ifndef PLAYER_H
#define PLAYER_H


#include "LinkedList.h" 
#include "Hand.h"
#include <string>

using std::string;

class Player{
    public:
    Player(string name);
    ~Player();
    
    // Sets player name
    void setName(string name);
    
    // Get player name 
    string getName();

    // Get player score
    int getScore();

    // Set player score
    void setScore(int score);
    
    // Increment score
    void incrementScore(int score);

    Hand* getHand();
    
    private:
    Hand* hand;
    string name;
    int score;
};


#endif //PLAYER_H