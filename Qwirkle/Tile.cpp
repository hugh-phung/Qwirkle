
#include "Tile.h"

Tile::Tile(Colour colour, Shape shape)
{
    this->colour = colour;
    this->shape = shape;
}

Tile::Tile(Tile& other)
{
    this->colour = other.colour;
    this->shape = other.shape;
}

Tile::Tile(std::string tile) 
{ 
    const char* tileAsChar = tile.c_str();
    Colour colour = tileAsChar[0];
    Shape shape = tileAsChar[1] - NUMBER_ASCII;
    this->colour = colour;
    this->shape = shape;
}

Colour Tile::getColour()
{
    return colour;
}

Shape Tile::getShape()
{
    return shape;
}

bool Tile::isDuplicate(Tile* other)
{
    bool flag = false;
    if(this->colour == other->colour &&
        this->shape == other->shape)
    {
        flag = true;
    }
    return flag;
}

bool Tile::hasSameColour(Tile* other)
{
    bool flag = false;
    if (this->colour == other->colour)
    {
        flag = true;
    }
    return flag;
}

bool Tile::hasSameShape(Tile* other)
{
    bool flag = false;
    if (this->shape == other->shape)
    {
        flag = true;
    }
    return flag;
}

std::string Tile::getTileAsString()
{
    std::string returnString = colour + std::to_string(shape);
    return returnString;
}

void Tile::printTile()
{
    std::cout << this->colour << this->shape << std::endl;
}