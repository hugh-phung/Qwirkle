#ifndef TILE_BAG_H
#define TILE_BAG_H

#include "LinkedList.h"
#include <sstream>

class TileBag
{
    public:
        TileBag();
        ~TileBag();

        //Return a string representation of the Tiles elements in the TileBag linked list  
        std::string getBagContents();
        
        // Adds tile to back of bag
        void addTile(Tile* tile);
        
        void printBag();
        
        // Checks if the tile bag is empty
        bool isEmpty();
        
        // Must be called after initialising to shuffle the tile bag.
        void shuffleTileBag();
        
        Tile* drawTile();
    
        int getLength();

        void placeTilesFromSave(std::string tileBagString);

    private:
        LinkedList* tileBag;

};

#endif // TILE_BAG_H