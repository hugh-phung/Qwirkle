#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include "TileCodes.h"
#include <string>

#define NUMBER_ASCII 48


// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile {
public:
   Colour colour;
   Shape  shape;

   Tile(Colour colour, Shape shape);
   Tile(std::string tile);
   Tile(Tile& other);

   // Get the tile colour
   Colour getColour();

   //Check if a tile is the same as the other
   bool isDuplicate(Tile* other);

   // Checks for the same colour or shape
   bool hasSameColour(Tile* other);
   bool hasSameShape(Tile* other);

   void printTile();

   // Get the tile shape
   Shape getShape();

   // Returns tile as string
   std::string getTileAsString();
};

#endif // ASSIGN2_TILE_H
