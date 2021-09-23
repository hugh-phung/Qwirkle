#include "Board.h"
#include <iostream>
#include <stdio.h>
#include <algorithm>

using std::vector;
using std::shared_ptr;

// BASE GAMEPLAY WILL USE A FIXED SIZE BOARD

Board::Board()
{

}

// This is called right after initialising board constructor
// This is organised to accomodate for loading ability
void Board::setBoardDimensions(int rows, int cols)
{
    this->max_rows = rows;
    this->max_cols = cols;
    vector<vector<Tile*>> tiles (max_rows, vector<Tile*> (max_cols, nullptr));
    this->tiles = tiles;
    this->numberOfTilesOnBoard = 0;
       
    for (int i = 0; i < max_rows; ++i)
    {
        for (int j = 0; j < max_cols; ++j)
        {
            tiles[i][j] = nullptr;
        }
    }
}

// Returns string of tiles on board for saving 
std::string Board::getBoardState()
{
    std::string boardTilePositions = "";
    int count = 0;
    for (int i = 0; i < max_rows; ++i)
    {
        for (int j = 0; j < max_cols; ++j)
        {
            if (numberOfTilesOnBoard == 0)
            {
                boardTilePositions = "";
            }

            if (tiles[i][j] != nullptr && numberOfTilesOnBoard != 0)
            {
                ++count;
                if (count < numberOfTilesOnBoard)
                {
                    boardTilePositions += tiles[i][j]->getColour() + std::to_string(tiles[i][j]->getShape()) + "@" + ((char)(i+ASCII)) + std::to_string(j) + ", ";
                }
                else if (count == numberOfTilesOnBoard)
                {
                    boardTilePositions += tiles[i][j]->getColour() + std::to_string(tiles[i][j]->getShape()) + "@" + (char)(i+ASCII) + std::to_string(j);
                }
            }
        }
    } 

    return boardTilePositions;
}


Board::~Board() 
{ 
    for (int i = 0; i < max_rows; ++i)
    {
        for (int j = 0; j < max_cols; ++j)
        {
            if (tiles[i][j] != nullptr) 
            { 
                delete tiles[i][j];
                tiles[i][j] = nullptr;
            }
        }
    } 
}

void Board::printBoard()
{
    char row = 'A';
    // Printing header of numbers
    std::cout << " ";
    for (int i = 0; i < max_cols; ++i)
    {
        printf("%4d", i);
    }
    std::cout << std::endl;
    
    std::cout << "  ";

    // Printing out header separator
    for (int i = 0; i < max_cols; ++i)
    {
        std::cout << "----"; 
    }  
    std::cout << std::endl;

    // Now we print the rows
    for (int i = 0; i < max_rows; ++i)
    {
        std::cout << row << " |";
        for (int j = 0; j < max_cols; ++j)
        {
            if (tiles[i][j] == nullptr)
            {
                std::cout << "   |";
            }

            else
            {
                std::cout<< colour(tiles[i][j]->getColour()) << tiles[i][j]->getColour() <<  
                tiles[i][j]->getShape() << RESET_COLOUR << " |";
            }
        }
        std::cout << std::endl;
        ++row;
    }
}
// Checks if the board is empty 
bool Board::isEmpty(int row, int col)
{
    bool isEmpty = true;
    if (row < max_rows-max_rows || row > max_rows-1 || col < max_cols-max_cols || col > max_cols-1)
    {
        isEmpty = false;
    }
    
    else if (tiles[row][col] != nullptr)
    {
        isEmpty = false;
    }
    return isEmpty;
}

// Returns a pointer to a tile at position (row, col)
Tile* Board::getTile(int row, int col)
{
    Tile* returnTile = nullptr;
    if (tiles[row][col] != nullptr)
    {
        returnTile = tiles[row][col];
    }
    return returnTile;
}

// Places a tile at position (row, col)
void Board::placeTile(Tile* tile, int x, int y) 
{
    tiles[x][y] = tile;
    ++numberOfTilesOnBoard;
}   

// Removes a tile from a board at position (row, col)
void Board::removeTile(int x, int y)
{
    if(tiles[x][y] != nullptr)
    {
        delete tiles[x][y];
        tiles[x][y] = nullptr;
        --numberOfTilesOnBoard;
    }
}

// Fills up the board from a save file
void Board::setBoardFromSave(std::string boardString)
{
    std::istringstream boardStream(boardString);
    std::string temp;
    while(std::getline(boardStream, temp, ',')) 
    {
        int stringStart = temp.size() - temp.size();
        // Removing the white space in line
        if ((int)temp.find(" ") == stringStart)
        {
            temp.erase(remove_if(temp.begin(), temp.end(), isspace), temp.end());
        }

        std::string delimiter = "@";
        
        // Obtaining the string of the user's tile
        std::string tileToPlace = temp.substr(stringStart, temp.find(delimiter));
        
        // Obtaining the string of the position to place onto the board
        const char* tileChar = tileToPlace.c_str();
        std::string position = temp.substr(temp.find(delimiter)+1, temp.length());

        Tile* tile = new Tile(tileChar);

        int rowPosition = (position[0] - ASCII);
        int colPosition = stoi(position.substr(1));
       
        placeTile(tile, rowPosition, colPosition);
        
    }    
}

// Sets the board dimensions from a save file
void Board::createBoardFromSave(std::string boardString)
{
    std::istringstream boardStream(boardString);
    std::string temp; 
    std::getline(boardStream >> std::ws, temp, ',');   
    int rows = std::stoi(temp);
    std::getline(boardStream >> std::ws, temp, ',');   
    int cols = std::stoi(temp);
    setBoardDimensions(rows, cols);
}

int Board::getMaxRow()
{
    return max_rows;
}
int Board::getMaxCol()
{
    return max_cols;
}

int Board::getNumberOfTilesOnBoard()
{
    return numberOfTilesOnBoard;
}

std::string Board::colour(Colour colour)
{
    std::string returnString = "";
    if (colour == RED)
    {
        returnString = RED_COLOUR;
    }
    else if (colour == ORANGE)
    {
        returnString = ORANGE_COLOUR;
    }
    else if (colour == YELLOW)
    {
        returnString = YELLOW_COLOUR;
    }
    else if (colour == GREEN)
    {
        returnString = GREEN_COLOUR;
    }

    else if (colour == BLUE)
    {
        returnString = BLUE_COLOUR;
    }

    else if (colour == PURPLE)
    {
        returnString = PURPLE_COLOUR;
    }

    return returnString;
}