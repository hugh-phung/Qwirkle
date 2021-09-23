#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#define CPU 1
#define PLAYERS 2
#define AI_LOAD "#AI"
#define PLAYERS_LOAD "#multiplePlayers"

#define PLACE "place"
#define REPLACE "replace"
#define SAVE "save"
#define HELP "help"
#define QUIT "quit"
#define HINT "hint"
#define SKIP "skip"
#define TILE_ON_HAND "tileOnHand"
#define TILE_ON_BOARD "boardTilePlacement"
#define SAVE_EXTENSION ".save"
#define ASCII 65

#define MAX_PLAYERS 4
#define MIN_PLAYERS 2
#define MAX_HAND 6
#define MAX_TILES_IN_LINE 6
// Defining locations of string indexes for the player commands
#define TOTAL_COMMAND_LENGTH 15
// If the player enters a position on the board such as "A1"
#define TOTAL_COMMAND_LENGTH_CASE_1 14
// If the player enters a position on the board such as "A20"
#define TOTAL_COMMAND_LENGTH_CASE_2 15

#define HAND_TILE_INDEX 6
#define HAND_TILE_INDEX_REPLACE 8

// The index in which the tile is located in the users input
#define TILE_STRING_INDEX 12
#define TILE_STRING_LENGTH_SINGLE 2 
#define TILE_STRING_LENGTH_DOUBLE 3 
#define COMMAND_REPLACE 10 

#define NOT_FOUND -1

#define UP 'U'
#define DOWN 'D'
#define LEFT 'L'
#define RIGHT 'R'

#define COLOUR "colour"
#define SHAPE "shape"

#include <iostream>
#include <memory>
#include <fstream>
#include <ostream>
#include <utility>
#include "Player.h"
#include "TileBag.h"
#include "Board.h"
#include "BST.h"

using std::cout;
using std::cin;
using std::endl;

class GameEngine
{
    public:
        GameEngine();
        ~GameEngine();

        void newGame();
        void playTheGame();
        void playTheGameCPU();

        void saveTheGame(std::string fileName);
        void loadTheGame(std::string fileName);

    private:
        void newGameStart();

        void loadPlayers(std::istream& inStream, string input);
        void loadBoard(std::istream& inStream, std::string input);
        void loadTileBag(std::istream& inStream, std::string input);
        void loadCurrentPlayer(std::istream& inStream, std::string input);

        void placeOnBoard(Tile* tile, int row, int col);
        bool actionPlace(string command, std::shared_ptr<Player> player);
        bool actionReplace(string command, std::shared_ptr<Player> player);
        void playRound(std::shared_ptr<Player> player, bool* gameOver, bool* quit);
        void playRoundCPU(std::shared_ptr<Player> player, bool* gameOver);
        void replenishHandTiles(shared_ptr<Player> player);

        bool hasSurroundingTiles(int row, int col);
        bool edgeCase(int row, int col);
        bool hasSameColourOrShapeEdgeCases(Tile* tile, int row, int col);
        bool validTilePlacement(Tile* tile, int x, int y, shared_ptr<Player> player);
        bool isSameColourOrShape(Tile* tile, int row, int col);
        void updatePoints(shared_ptr<Player> player);
        void updatePoints(shared_ptr<Player> player, int incrementPoints);
        int countPointsInLine(int row, int col, char* direction);
        bool sixTileLineCheck(int row, int col, char direction, Tile* tile, string type);

        bool checkLeftIsValid(Tile* tile, int row, int col);
        bool checkRightIsValid(Tile* tile, int row, int col);
        bool checkUpIsValid(Tile* tile, int row, int col);
        bool checkDownIsValid(Tile* tile, int row, int col);

        int getBoardPlacementRow(string boardPlacementString);
        int getBoardPlacementCol(string boardPlacementString);

        void printRound(std::shared_ptr<Player> player);
        void printCommands();
        void clearedHandGameOver(std::shared_ptr<Player> player, bool* gameOver);
        void gameOverPrint();
        void findOptimalPlacement(std::shared_ptr<Player> player);
        void giveHand(std::shared_ptr<Player> player); 
        bool playersHaveEnoughTiles();
        bool playerNoLongerHasTiles();
        void setOtherPlayerTurn(std::shared_ptr<Player> currentPlayer);
        bool playerHasTile(string tileString, shared_ptr<Player> player);
        bool tileIsValid(string tileString, string type);
        bool selectionNumValid(std::string number, int min, int max);
        
        std::vector<std::shared_ptr<Player>> playerVector;
        bool playerNameValid(std::string name, std::vector<std::string> playerNames, int* index);
        std::shared_ptr<TileBag> tileBag;
        std::shared_ptr<Board> board;
        bool* playerTurns;
        int numPlayers;
        bool askingHint;
        bool firstTurn;
        bool cpuTurn;
        bool cpuGame;
        bool playerGame;
        int current_round_score;

};

#endif // GAMEENGINE_H
