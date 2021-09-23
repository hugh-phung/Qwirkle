#include "Hand.h"

Hand::Hand()
{
    this->hand = new LinkedList();
    this->size = 0; 
}

Hand::Hand(Hand& other)
{
    hand = new LinkedList(*other.hand);
}

Hand::~Hand()
{
    delete hand;
}

int Hand::getIndexOfTileStr(std::string tileString)
{
    int returnIndex = INVALID_NUM;
    for (int i = 0; i < getLength(); ++i)
    {
        if (getTile(i)->getTileAsString() == tileString)
        {
            returnIndex = i;
        }
    }
    return returnIndex;
}

void Hand::print()
{
    hand->print();
}

int Hand::getLength()
{
    return hand->getLength();
}

Tile* Hand::getTile(int index)
{
    return hand->get(index);
}
void Hand::addTile(Tile* tile)
{ 
    hand->addBack(tile);
}

void Hand::removeTile(int index)
{
    hand->deleteAt(index);
}

void Hand::clear()
{
    hand->clear();
}

std::string Hand::getHandContents()
{
    return hand->getContents();
}

void Hand::setHand(std::string playerHand) 
{ 
    std::istringstream handStream(playerHand);
    std::string temp;
    while(std::getline(handStream, temp, ',')) 
    {
        Tile* tile = new Tile(temp);
        
        // create new tile and then put into hand.
        hand->addBack(tile);
    }
}

