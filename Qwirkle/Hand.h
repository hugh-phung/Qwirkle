#ifndef HAND_H
#define HAND_H

#include "LinkedList.h"
#include <sstream>

class Hand
{
    public:
        Hand();
        Hand(Hand& other);
        ~Hand();

        int getLength();
        void print();
        int getIndexOfTileStr(std::string tileString);
        Tile* getTile(int index);
        void addTile(Tile* tile);
        void removeTile(int index);
        void clear();
        std::string getHandContents();
        void setHand(std::string playerHand);
    
    private:
        LinkedList* hand;
        int size;
};

#endif //HAND_H