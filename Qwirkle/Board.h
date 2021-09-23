#ifndef BOARD_H
#define BOARD_H
#define MAX_ROW 26
#define MAX_COL 26
#define ASCII 65

#include "Tile.h"
#include <vector>
#include <memory>
#include <string>
#include <sstream>

using std::vector;
using std::shared_ptr; 

class Board{
    public:
        Board();
        ~Board();

        void printBoard();
        void placeTile(Tile* tile, int x, int y);
        bool isEmpty(int row, int col);
        Tile* getTile(int row, int col);
        void removeTile(int x, int y);
        std::string getBoardState();
        void setBoardFromSave(std::string boardString);
        void setBoardDimensions(int rows, int cols);
        void createBoardFromSave(std::string boardString);

        int getMaxRow();
        int getMaxCol();
        int getNumberOfTilesOnBoard();

    private:
        vector<vector<Tile*>> tiles;
        // vector<vector<shared_ptr<Tile>>> tiles;
        int numberOfTilesOnBoard;
        int max_rows;
        int max_cols;
        std::string colour(Colour colour);
};
    

#endif // BOARD_H