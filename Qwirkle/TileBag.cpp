#include <iostream>
#include <random>
#include <utility>
#include "TileBag.h"


TileBag::TileBag()
{
    tileBag = new LinkedList();
}

void TileBag::shuffleTileBag()
{
    /*
     * The only reason this code portion below isn't initialised with the tile bag constructor
     * is so it doesn't mess up the loading - the save file won't always have a full tile bag.
     * Shuffling begins by initating an ordered tile bag
     */
    for (int k = 0; k < TILE_SET; ++k)
    {
        for (int i = 0; i < MAX_COLOURS; ++i)
        {
            for (int j = 0; j < MAX_SHAPES; ++j)
            {
                Tile* newTile = new Tile(colours[i], shapes[j]);
                addTile(newTile);
            }
        }
    }
    
    /*
     * Shuffle algorithm works by selecting random indexes in the ordered tile bag,
     * then grabs the tile at that index to place in the new tile bag.
     */
    LinkedList* newTileBag = new LinkedList();
    std::random_device randomSeed;
    std::uniform_int_distribution<int> uniform_dist(0, tileBag->getLength());
    int count = 0;
    while (count < (MAX_TILES * TILE_SET))
    {
        int index = uniform_dist(randomSeed);
        if (tileBag->get(index) != nullptr)
        {
            Tile* newTileNewBag = new Tile(*(tileBag->get(index)));
            tileBag->deleteAt(index);
            newTileBag->addBack(newTileNewBag);
            ++count;
        }
    }

    /*
     * Deleting contents of old tile bag 
     * then transfer the class variable pointer to the contents of the new tile bag.
     */
    delete tileBag;
    tileBag = newTileBag;
    newTileBag = nullptr;


}

TileBag::~TileBag()
{
    if (tileBag != nullptr)
    {
        delete tileBag;
        tileBag = nullptr;
    }
}

void TileBag::addTile(Tile* tile)
{
    tileBag->addBack(tile);
}

/*
 * Draws a tile from the front of the tile bag to return,
 * then deletes it from the tile bag.
 */
Tile* TileBag::drawTile()
{
    Tile* returnTile = nullptr;
    if (tileBag->getLength() > 0)
    {
        returnTile = new Tile(*tileBag->get(0));
        tileBag->deleteFront();
    }
    return returnTile;
}

void TileBag::printBag()
{
    tileBag->print();
}

bool TileBag::isEmpty()
{
    bool flag = true;
    if (tileBag->getLength() != 0)
    {
        flag = false;
    }
    return flag;
}

int TileBag::getLength()
{
    return tileBag->getLength();
}

std::string TileBag::getBagContents() 
{ 
    return tileBag->getContents();
}

// Loads up the file bag from a save file 
void TileBag::placeTilesFromSave(std::string tileBagString)
{
    std::istringstream tileBagStream(tileBagString);
    std::string temp;
    while(std::getline(tileBagStream, temp, ',')) 
    {
        Tile* tile = new Tile(temp);
        this->addTile(tile);
    }
}