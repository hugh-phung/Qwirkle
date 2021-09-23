#include "GameEngine.h"
#include <string>

GameEngine::GameEngine()
{

}

GameEngine::~GameEngine()
{
    delete playerTurns;
    playerTurns = nullptr;
}

// Loads the game from an input file string
void GameEngine::loadTheGame(std::string fileName)
{
    std::ifstream inStream(fileName);

    // Loads in the contents of the save file line by line
    std::string input;
    inStream >> input;
    if (input == AI_LOAD)
    {
        cpuGame = true;
        playerGame = false;
        numPlayers = MIN_PLAYERS;
    }
    else if (input == PLAYERS_LOAD)
    {
        cpuGame = false;
        playerGame = true;
        inStream >> input;
        numPlayers = std::stoi(input);
    }
    else
    {
        inStream.clear();
        inStream.seekg(0, std::ios::beg);
        numPlayers = MIN_PLAYERS;
    }

    loadPlayers(inStream, input);
    loadBoard(inStream, input);
    loadTileBag(inStream, input);
    loadCurrentPlayer(inStream, input);

    inStream.close();

    std::cin.ignore();

    cout << endl;
    cout << "\nQwirkle game loaded successfully\n" << endl;

    // Loading CPU or Player game
    if (cpuGame)
    {
        playTheGameCPU();
    }

    else
    {
        playTheGame();
    }
    
}

void GameEngine::loadPlayers(std::istream& inStream, std::string input)
{
    // milestone 3 test cases will also include the number of players
    for (int i = 0; i < numPlayers; ++i)
    {
        inStream >> input;
        playerVector.push_back(std::make_shared<Player>(input));
        inStream >> input;
        playerVector[i]->setScore(stoi(input));
        inStream >> input;
        playerVector[i]->getHand()->setHand(input);
    }
}

void GameEngine::loadBoard(std::istream& inStream, std::string input)
{
    board = std::make_shared<Board>();
    inStream >> input;
    board->createBoardFromSave(input);
    getline(inStream, input);
    getline(inStream, input);
    board->setBoardFromSave(input);
}

void GameEngine::loadTileBag(std::istream& inStream, std::string input)
{
    tileBag = std::make_shared<TileBag>();
    getline(inStream, input);
    tileBag->placeTilesFromSave(input);
}

void GameEngine::loadCurrentPlayer(std::istream& inStream, std::string input)
{
    // Initiate array of player turns
    playerTurns = new bool[numPlayers];
    for (int i = 0; i < numPlayers; ++i)
    {
        playerTurns[i] = false;
    }
    inStream >> input;

    for (int i = 0; i < numPlayers; ++i)
    {
        if (input == playerVector[i]->getName())
        {
            playerTurns[i] = true;
        }
    }

    // Setting turn for CPU
    if (cpuGame)
    {
        cpuTurn = true;
    }

}

// Obtains game details and writes to a file
void GameEngine::saveTheGame(std::string fileName)
{

    std::string saveAsName = fileName + SAVE_EXTENSION;
    std::ofstream outFile;
    outFile.open(saveAsName);

    if (cpuGame)
    {
        outFile << AI_LOAD << endl;
    }
    else if (playerGame)
    {
        outFile << PLAYERS_LOAD << endl;
        outFile << numPlayers << endl;
    }

    for (int i = 0; i < numPlayers; ++i)
    {
        outFile << playerVector[i]->getName() << endl;
        outFile << playerVector[i]->getScore() << endl;
        outFile << playerVector[i]->getHand()->getHandContents() << endl;  
    }

    outFile << board->getMaxRow() << "," << board->getMaxCol() << endl;
    outFile << board->getBoardState() << endl;
    outFile << tileBag->getBagContents() << endl;

    for (int i = 0; i < numPlayers; ++i)
    {
        if (playerTurns[i] == true)
        {
            outFile << playerVector[i]->getName() << endl;
        }
    }
    
    outFile.close();
}

void GameEngine::newGame()
{   
    int gameType = -1;
    bool loop = true;
    cout << "\nChoose players\n" << endl;
    cout << "1. CPU " << endl;
    cout << "2. Players" << endl;
    do
    {
        cin >> gameType;
        cin.clear();
        cin.ignore();

        // CPU Game
        if (gameType == CPU)
        {
            loop = false;

            playerGame = false;
            cpuGame = true;
            cpuTurn = false;
            numPlayers = MIN_PLAYERS;
  
            newGameStart();
        }

        // Game against players
        else if (gameType == PLAYERS)
        {
            loop = false;

            playerGame = true;
            cpuGame = false;

            cout << "\nHow many players? (2 - 4 players)\n" << endl;
            numPlayers = 0;
            std::string numPlayersString = "";
            do {
                cout << "> ";
                cin >> numPlayersString;
                cin.ignore();
            }while (!selectionNumValid(numPlayersString, MIN_PLAYERS, MAX_PLAYERS) && !cin.eof());
            
            numPlayers = stoi(numPlayersString);
            newGameStart();

        }
    
    } while (loop && !cin.eof());
}

bool GameEngine::selectionNumValid(std::string number, int min, int max)
{
    bool isValid = true;
    // Checking if input is a single digit
    if (number.size() == 1)
    {
        // Checks if the input isn't a number
        if (!isdigit(number.c_str()[0]))
        {
            isValid = false;

        }

        // If it is a number, check if it is above and below the min and max allowed num of players
        if (isValid == true)
        {
            int numberInt = stoi(number);
            if (numberInt < min || numberInt > max)
            {
                isValid = false;
            }
        }
    }
    else
    {
        isValid = false;
    }
    return isValid;
}

void GameEngine::newGameStart()
{
    cout << "\nStarting a New Game\n" << endl;

    // Initiating array of player turns
    playerTurns = new bool[numPlayers];
    for (int i = 0; i < numPlayers; ++i)
    {
        playerTurns[i] = false;
    }

    // Initiating vector of player names
    std::vector<std::string> playerNames;
    for (int i = 0; i < numPlayers; ++i)
    {
        playerNames.push_back("");
    }
    
    // Entering names for players   
    int counter = 0;
    bool loop = true;
    while (loop && !cin.eof())
    {
        if (counter == numPlayers)
        {
            loop = false;
        }

        else
        {
            char playerName[] = "";
            
            do
            {
                cout << "Enter a name for player " << counter+1 << " (uppercase characters only)" << endl;
                cout << "> "; 
                cin >> playerName;
                playerNames[counter] = playerName;
                cout << "\n";


            } while (!playerNameValid(playerNames[counter], playerNames, &counter) && !cin.eof());
        }
       
    }
    cin.ignore();

    // Initialise the players
    for (int i = 0; i < numPlayers; ++i)
    {
        playerVector.push_back(std::make_shared<Player>((playerNames[i])));
    }

    // Initialise the tileBag and the board
    tileBag = std::make_shared<TileBag>();
    tileBag->shuffleTileBag();
    board = std::make_shared<Board>();
    board->setBoardDimensions(MAX_ROW, MAX_COL);

    // Filling up the players hands with 6 tiles
    for (int i = 0; i < numPlayers; ++i)
    {
        giveHand(playerVector[i]);
    }

    // Setting the turn to the first player
    playerTurns[0] = true;

    // Setting the current round score to add to 0
    current_round_score = 0;

    // Makes sure each player starts with enough tiles equal to the maximum hand 
    if (playersHaveEnoughTiles())
    {
        // A method used to start the game
        if (!cin.eof())
        {
            cout << "Let's Play!\n" << endl;
            if (cpuGame)
            {
                playTheGameCPU();
            }

            else
            {
                playTheGame();
            }
        }
        else
        {
            cout << "\nGoodbye\n" << endl;
        }
    }
}

bool GameEngine::playerNameValid(std::string name, std::vector<std::string> namesArray, int* index)
{
    bool flag = true;
    char notAllowed[] = "qwertyuiopasdfghjklzxcvbnm1234567890!@#$%^&*()`~-_=+[{]};:<,>.?/|'";

    // Checks if the player entered doesn't already exist
    for (int i = 0; i < numPlayers; ++i)
    {
        if (namesArray[i] != "")
        {    
            if (*index != i)   
            {
                if (std::string(namesArray[i]) == (std::string(name)))
                {
                    flag = false;
                }
            }
        }
    }
    /* 
     * Looping through the name and notAllowed character arrays to 
     * find if they match 
     */ 
    for (int i = 0; (name[i] != '\0'); ++i)
    {
        for (int j = 0; (notAllowed[j] != '\0'); ++j)
        {
            if (name[i] == notAllowed[j])
            {
                flag = false;
            }
        }
    }

    // Increments counter if successful
    if (flag == true)
    {
        ++(*index);
    }
    
    return flag;
}

// Checks whether the input tile matches appropriate tile conventions
bool GameEngine::tileIsValid(string tileString, string type)
{
    bool flag = true;
    const char* tileAsChar = tileString.c_str();
    char letter = tileAsChar[0];
    char notAllowed[] = "1234567890!@#$%^&*()`~-_=+[{]};:<,>.?/|'";

    // Checks if the inputted tileString is upper case 
    if (letter != toupper(letter))
    {
        flag = false;
    }

    // Checks for special characters
    for (int i = 0; i < (notAllowed[i] != '\0'); ++i)
    {
        if (letter == notAllowed[i])
        {
            flag = false;
        }
    }

    // If we're checking the tile that is in the player's hand  
    if (type == TILE_ON_HAND)
    {
        if (tileString.length() == TILE_STRING_LENGTH_SINGLE)
        {
            int shape= getBoardPlacementCol(tileString);
            if (shape <= (MAX_SHAPES-MAX_SHAPES) || shape > MAX_SHAPES)
            {
                flag = false;
            }
        }
        else
        {
            flag = false;
        }
    }

    // If we're checking the tile coordinates on the board
    else if (type == TILE_ON_BOARD)
    {
        if (tileString.length() == TILE_STRING_LENGTH_SINGLE || tileString.length() == TILE_STRING_LENGTH_DOUBLE)
        {
            int col = getBoardPlacementCol(tileString);
            if ((col < (board->getMaxCol()-board->getMaxCol())) || col > board->getMaxCol()-1)
            {
                flag = false;
            }
        }
        else
        {
            flag = false;
        }
    }

    else
    {
        flag = false;
    }

    return flag;
}

// Returns the integer representation of a row letter
int GameEngine::getBoardPlacementRow(string tilePlacementString)
{
    const char* tileAsChar = tilePlacementString.c_str();
    char row = tileAsChar[0];

    // This converts the character into its integer representation
    int rowReturn = row - ASCII;

    return rowReturn;
}

// Returns the numeric component of a tile string, mainly used to find the columns as an integer
int GameEngine::getBoardPlacementCol(string tilePlacementString)
{
    int returnCol = -1;
    bool stringIsNumeric = true;
    const char* tileAsChar = tilePlacementString.c_str();

    // Checks all characters in string to see if it CAN be converted to an integer in the first place
    for (int i = 1; tileAsChar[i] != '\0'; ++i)
    {
        if (!isdigit(tileAsChar[i]))
        {
            stringIsNumeric = false;
        }
    }

    // Converts to integer
    if (stringIsNumeric)
    {
        string tilePlacementNumberOnlyString = tilePlacementString.substr(1);
        returnCol = stoi(tilePlacementNumberOnlyString);    
    }

    return returnCol;
}


// Places the tile to a particular row and column on the board
void GameEngine::placeOnBoard(Tile* tile, int row, int col)
{
    if (tile != nullptr && row < board->getMaxRow() && col < board->getMaxCol())
    {
        board->placeTile(tile, row, col);
    }
}

// Increments a player's points with the current round's score
void GameEngine::updatePoints(shared_ptr<Player> player)
{
    player->incrementScore(current_round_score);
}

// Overloading method to increment with a particular score
void GameEngine::updatePoints(shared_ptr<Player> player, int incrementPoints)
{
    player->incrementScore(incrementPoints);
}

// Refills the player's hand by drawing a tile from the tile bag
void GameEngine::replenishHandTiles(shared_ptr<Player> player)
{
    if (tileBag->getLength() > 0)
    {
        Tile* tileToAddToHand = tileBag->drawTile();
        if (tileToAddToHand != nullptr)
        {
            player->getHand()->addTile(tileToAddToHand);
        }
        else
        {
            delete tileToAddToHand;
            tileToAddToHand = nullptr;
        }   
    }

}

// Places a tile from a player's hand onto the the board
bool GameEngine::actionPlace(string command, std::shared_ptr<Player> player)
{      
    bool success = false;

    // Gathering strings of tiles and board placement from the passed in string
    string tileString = command.substr(HAND_TILE_INDEX, TILE_STRING_LENGTH_SINGLE);
    string tilePlacementString = "";

    // When the string of the board placement position is of 2 characters, e.g. F7
    if (command.size() == TOTAL_COMMAND_LENGTH_CASE_1)
    {
        tilePlacementString = command.substr(TILE_STRING_INDEX, TILE_STRING_LENGTH_SINGLE);
    }

    // When the string of the board placement position is of 3 characters, e.g. F12
    else if (command.size() == TOTAL_COMMAND_LENGTH_CASE_2)
    {
        tilePlacementString = command.substr(TILE_STRING_INDEX, TILE_STRING_LENGTH_DOUBLE);
    }

    int indexOfTileInHand = player->getHand()->getIndexOfTileStr(tileString);
    int row = getBoardPlacementRow(tilePlacementString);
    int col = getBoardPlacementCol(tilePlacementString);

    if(indexOfTileInHand != NOT_FOUND) 
    { 
        if (board->isEmpty(row, col))
        {
            // On the first turn the player can place anywhere
            if (firstTurn)
            {
                int startingPoint = 2;
                
                // Places a tile on the board and removes it from the player's hand
                Tile* tileToAddtoBoard = new Tile(*(player->getHand()->getTile(indexOfTileInHand)));
                player->getHand()->removeTile(indexOfTileInHand);
                placeOnBoard(tileToAddtoBoard, row, col);

                // Refill the player's hand with tiles
                replenishHandTiles(player);

                // On the first turn, the player receives 2 points for tile placement
                updatePoints(player, startingPoint);

                firstTurn = false;
                success = true;
            }

            // Otherwise the placement must be valid
            else
            {
                Tile* tileToAddtoBoard = new Tile(*(player->getHand()->getTile(indexOfTileInHand)));
                if (validTilePlacement(tileToAddtoBoard, row, col, player))
                {
                    // Removes a tile from a player's hand and replaces it with one from the bag
                    player->getHand()->removeTile(indexOfTileInHand);
                    placeOnBoard(tileToAddtoBoard, row, col);

                    // Refill the player's hand with tiles
                    replenishHandTiles(player);

                    // Updates points for each placement
                    updatePoints(player);

                    success = true;
                }
                else
                {
                    delete tileToAddtoBoard;
                    tileToAddtoBoard = nullptr;
                }
            }

        }

        else
        {
            cout << "\nTile cannot be placed at that position\n" << endl;
        }

    }
    else if (indexOfTileInHand == -1)
    {
        cout << "\nPlayer does not have tile\n" << endl;
    }

    return success;
    
}

// Replaces a tile from a player's hand with one from the top of the tile bag
bool GameEngine::actionReplace(string command, std::shared_ptr<Player> player)
{
    bool success = false;

    // Obtains the string of the tile in the command
    string tileString = command.substr(HAND_TILE_INDEX_REPLACE, TILE_STRING_LENGTH_SINGLE);
    
    // Checks if player has tile in their current hand
    int indexOfTileInHand = player->getHand()->getIndexOfTileStr(tileString);

    // If player has that tile in the command, add it to the back of the tile bag 
    // and then grab a new one to replenish their hand
    if (indexOfTileInHand != NOT_FOUND)
    {
        if (tileBag->getLength() > 0)
        {
            Tile* newTile = new Tile(*(player->getHand()->getTile(indexOfTileInHand)));
            tileBag->addTile(newTile);
            player->getHand()->removeTile(indexOfTileInHand);
            replenishHandTiles(player);
            success = true;
        }
        else
        {
            cout << "\nNothing left in the tile bag, switching turns\n" << endl;
            success = true;
        }

    }
    else
    {
        cout << "\nPlayer does not have tile\n" << endl;
    }

    return success;
}

void GameEngine::playRoundCPU(std::shared_ptr<Player> player, bool* gameOver)
{
    printRound(player);

    if (firstTurn)
    {
        int firstTurnPoints = 2;
        // If player decides to replace on the first turn and the board is still empty,
        // the CPU will place its first tile in the center of the board
        Tile* tileToAddtoBoard = new Tile(*(player->getHand()->getTile(0)));
        player->getHand()->removeTile(0);
        placeOnBoard(tileToAddtoBoard, board->getMaxRow()/2, board->getMaxCol()/2);

        // Prints placement for CPU
        cout << player->getName() << " places " << tileToAddtoBoard->getTileAsString() 
                        << " at " << (char)((board->getMaxRow()/2)+ASCII) << board->getMaxCol()/2 << "\n" << endl;
        
        // Refill the player's hand with tiles
        replenishHandTiles(player);

        // Updates points for each placement
        updatePoints(player, firstTurnPoints);

        firstTurn = false;
    }

    else
    {
        shared_ptr<BST> pointsTree = std::make_shared<BST>();
        bool empty = true;

        // Loops through each possible placement on the board for each tile in the player's hand
        for (int k = 0; k < player->getHand()->getLength(); ++k)
        {
            for (int i = 0; i < board->getMaxRow(); ++i)
            {
                for (int j = 0; j < board->getMaxCol();++j)
                {
                    if (board->isEmpty(i, j))
                    {
                        if (validTilePlacement(player->getHand()->getTile(k), i, j, player))
                        {
                            std::shared_ptr<Tile> tileInTree = std::make_shared<Tile>((player->getHand()->getTile(k)->getTileAsString()));
                            pointsTree->add(current_round_score, tileInTree, i, j);
                            empty = false;                
                        }

                    }

                }
            }
        }
        if (empty)
        {
            // If there are no valid placements, replace the first tile in hand into the bag
            if (tileBag->getLength() > 0)
            {
                Tile* newTile = new Tile(*(player->getHand()->getTile(0)));
                cout << "\n" << player->getName() << " is placing tile " 
                                                  << newTile->getTileAsString() << "\n" << endl;

                tileBag->addTile(newTile);
                player->getHand()->removeTile(0);
                replenishHandTiles(player);
            }
            else
            {
                cout << "\nNothing left in the tile bag, switching turns\n" << endl;
            }
        }

        else
        {
            std::shared_ptr<BST_Node> maxNode = pointsTree->getMaxNode();

            int indexOfTileInHand = player->getHand()->getIndexOfTileStr(maxNode->tile->getTileAsString());

            Tile* tileToAddtoBoard = new Tile(*(player->getHand()->getTile(indexOfTileInHand)));

            // Removes a tile from a player's hand and replaces it with one from the bag
            player->getHand()->removeTile(indexOfTileInHand);
            placeOnBoard(tileToAddtoBoard, maxNode->row, maxNode->col);

            // Prints tile placement
            cout << player->getName() << " places " << tileToAddtoBoard->getTileAsString() 
                                    << " at " << (char)((maxNode->row)+ASCII) << maxNode->col << "\n" << endl;
                                    

            // Refill the player's hand with tiles
            replenishHandTiles(player);

            // Updates points for each placement
            updatePoints(player, maxNode->points);
        }
    }


    if (player->getHand()->getLength() == 0)
    {
        clearedHandGameOver(player, gameOver);
    }

    setOtherPlayerTurn(player);  
}

void GameEngine::playRound(std::shared_ptr<Player> player, bool* gameOver, bool* quit)
{    
    printRound(player);
    string command;
    bool success = false;
    
    // Loops round if the player is stupid and enters bad input
    while (!success)
    {
        if (!cin.eof())
        {
            success = false;
            cout << "> ";
            getline(cin, command);
            cout << endl;
            // Obtaining the action command
            string delimiter = " ";
            string playerAction = command.substr(0, command.find(delimiter));

            // If user enters 'save ' followed by the name of the file 
            // A save file will be created
            if (playerAction == SAVE)
            {
                string fileName = "unnamed_save_file";
                // Finds the user input as the name of the save file
                if (command.size() > playerAction.size())
                {
                    fileName = command.substr(command.find(delimiter)+1, command.size()-1);
                }
                saveTheGame(fileName);
            }

            else if (playerAction == HELP)
            {
                printCommands();
            }

            else if (playerAction == QUIT)
            {
                success = true;
                *quit = true;
            }

            else if (playerAction == HINT)
            {
                askingHint = true;
                findOptimalPlacement(player);
                askingHint = false;
            }

            else if (playerAction == SKIP)
            {
                success = true;
            }
            
            // Total command length denotes the total possible length
            // for the place and replace commands
            else if (command.size() <= TOTAL_COMMAND_LENGTH) 
            {   
                // If player choose to place a tile
                if (playerAction == PLACE)
                {
                    // Case1 and Case2 are for when the board placement position
                    // is of 2 characters or 3 characters
                    if (command.size() == TOTAL_COMMAND_LENGTH_CASE_1 || command.size() == TOTAL_COMMAND_LENGTH_CASE_2)
                    {
                        // Checks tile in hand
                        if (tileIsValid(command.substr(HAND_TILE_INDEX, TILE_STRING_LENGTH_SINGLE), TILE_ON_HAND))
                        {
                            // Checks tile board placement
                            if (tileIsValid(command.substr(TILE_STRING_INDEX, TILE_STRING_LENGTH_SINGLE), TILE_ON_BOARD))
                            {
                                success = actionPlace(command, player);
                            }
                            else if (tileIsValid(command.substr(TILE_STRING_INDEX, TILE_STRING_LENGTH_DOUBLE), TILE_ON_BOARD))
                            {                            
                                success = actionPlace(command, player);

                            }
                            else
                            {
                                cout << "\nInvalid placement position, try again\n" << endl;
                            }                           
                        }

                        else
                        {
                            cout << "\nInvalid tile in hand, try again\n" << endl;
                        }
                    }
                    else
                    {
                        cout << "\nInvalid place command, try again\n" << endl;
                    }
                }

                // will replace a tile from the player's hand to the tile bag
                else if (playerAction == REPLACE)
                {
                    if (command.size() == COMMAND_REPLACE)
                    {
                        if (tileIsValid(command.substr(HAND_TILE_INDEX_REPLACE,TILE_STRING_LENGTH_SINGLE), TILE_ON_HAND))
                        {
                            success = actionReplace(command, player);
                        }
                        else
                        {
                            cout << "\nInvalid replace command, try again\n" << endl;
                        }
                    }
                    else
                    {
                        cout << "\nInvalid replace command, try again\n" << endl;
                    }
                }
                else
                {
                    // Accomodating for when the user enters rubbish input
                    if (playerAction != SAVE && !cin.eof())
                    {
                        cout << "\nInvalid Input\n" << endl;
                    }
                }   
            }

            else
            {
                // More rubbish input checking
                if (!cin.eof())
                {
                    cout << "\nInvalid Input\n" << endl;
                }
            }
        }
        // When the user exits early by entering the end of file command
        else
        {
            success = true;
            cout << "\nGoodbye\n" << endl;
        }
    }

    // If a player depletes their hand first, 
    // Awards them with 6 extra points and ends the game
    if (player->getHand()->getLength() == 0)
    {
        clearedHandGameOver(player, gameOver);
    }

    // Sets the other player's turn at the end of the round
    setOtherPlayerTurn(player);  

}

void GameEngine::clearedHandGameOver(std::shared_ptr<Player> player, bool* gameOver)
{
    cout << "\n";

    int qwirklePoints = 6;
    cout << "The player " << player->getName() << " has cleared their hand!" << endl;
    cout << "They get +6 points" << endl;
    updatePoints(player, qwirklePoints);
    *gameOver = true;

    cout << "\n";

}

// Checking if the player has 6 tiles in their hand
bool GameEngine::playersHaveEnoughTiles()
{
    bool playersHaveEnoughTiles = true;

    for (int i = 0; i < numPlayers; ++i)
    {
        if (playerVector[i]->getHand()->getLength() != MAX_HAND)
        {
            cout << "\nNot enough tiles to distribute to players!\n" << endl;
            playersHaveEnoughTiles = false;         
        }
    }
    return playersHaveEnoughTiles;
}

// A helper method that checks if one or more players has 0 tiles in their hand
bool GameEngine::playerNoLongerHasTiles()
{
    bool playerNoLongerHasTiles = false;
    for (int i = 0; i < numPlayers; ++i)
    {
        if (playerVector[i]->getHand()->getLength() == 0)
        {
            playerNoLongerHasTiles = true;
        }
    }

    return playerNoLongerHasTiles;
}

// Game loop to rotate between each player and round
void GameEngine::playTheGame()
{  
    bool gameOver = false;
    /* 
     * First turn is kept track because on the first turn,
     * there will be no tile validation for nearby tiles.
     * They are free to place it anywhere on the board as long as it
     * is within the board's confines
     */
    firstTurn = false;  
    if (board->getNumberOfTilesOnBoard() == 0)
    {
        firstTurn = true;  
    }
    bool quit = false;

    // Initates game loop
    int counter = 0;
    while (!gameOver && !quit && !cin.eof())
    {
        if (playerTurns[counter] == true) 
        {
            playRound(playerVector[counter], &gameOver, &quit);
        }

        // End of game condition
        if (tileBag->isEmpty() && playerNoLongerHasTiles())
        {
            gameOver = true;
        }

        ++counter;

        // Resets counter after the last player's turn
        if (counter >= numPlayers)
        {
            counter = 0;
        }
    }

    // If user prematurely quits the game
    if (quit)
    {
        cout << "Goodbye\n" << endl;
    }

    // Game over statements
    if (gameOver)
    {
        gameOverPrint();
    }
}

void GameEngine::playTheGameCPU()
{  
    bool gameOver = false;
    /* 
     * First turn is kept track because on the first turn,
     * there will be no tile validation for nearby tiles.
     * They are free to place it anywhere on the board as long as it
     * is within the board's confines
     */
    firstTurn = false;  
    if (board->getNumberOfTilesOnBoard() == 0)
    {
        firstTurn = true;  
    }
    bool quit = false;

        // Initates game loop
        while (!gameOver && !quit && !cin.eof())
        {
            
            if (playerTurns[0]) 
            { 
                playRound(playerVector[0], &gameOver, &quit);
            }
            
            else if (!playerTurns[0])
            {
                playRoundCPU(playerVector[1], &gameOver);
            }

            // End of game condition
            if (tileBag->isEmpty() && playerNoLongerHasTiles())
            {
                gameOver = true;
            }
        }

        // If user prematurely quits the game
        if (quit)
        {
            cout << "Goodbye\n" << endl;
        }

        // Game over statements
        if (gameOver)
        {
            gameOverPrint();
        }
    
    
}

void GameEngine::gameOverPrint()
{
    cout << "Game over" << endl;

    for (int i = 0; i < numPlayers; ++i)
    {
        cout << "Score for " << playerVector[i]->getName() << " : " << playerVector[i]->getScore() << endl;

    }

    // Keeping track of all the points of players
    int pointsArray[numPlayers];
    for (int i = 0; i < numPlayers; ++i)
    {
        pointsArray[i] = playerVector[i]->getScore();
    }

    // Find the highest score
    int highestScore = -1;
    int winningPlayer = -1;
    for (int i = 0; i < numPlayers; ++i)
    {
        if (pointsArray[i] > highestScore)
        {
            highestScore = pointsArray[i];
            winningPlayer = i;
        }
    }

    // Determining if a draw has occurred where more than one player has the highest score
    bool draw = false;
    for (int i = 0; i < numPlayers; ++i)
    {
        if (highestScore == pointsArray[i] && i != winningPlayer)
        {
            draw = true;
        }
    }

    if (!draw)
    {
        cout << "Player " << playerVector[winningPlayer]->getName() << " won!" << endl;
    }
    else
    {
        cout << "Draw between two or more players!!!" << endl;
        cout << "HA HA no one wins >:)" << endl;
    }


    cout << "\nGoodbye\n" << endl;
}

// If the left board position is empty or contains a valid tile it returns true 
bool GameEngine::checkLeftIsValid(Tile* tile, int row, int col)
{
    bool leftIsValid = false;
    // Checks entire line for either same colour or shape.
    // First checks if the left-most position contains a tile.
    if (!(board->isEmpty(row, col - 1)))
    {
        // Following checks will then continue along a line to check if they match by colour
        if (board->getTile(row, col - 1)->getColour() == tile->getColour())
        {
            if (sixTileLineCheck(row, col, LEFT, tile, COLOUR))
            {
                leftIsValid = true;
            }
        }
        // Following checks will then continue along a line to check if they match by shape
        else if (board->getTile(row, col - 1)->getShape() == tile->getShape())
        {
            if (sixTileLineCheck(row, col, LEFT, tile, SHAPE))
            {
                leftIsValid = true;
            }
        }
    } 
    // If the position is empty then the left side doesn't need to be checked
    else
    {
        leftIsValid = true;
    }

    return leftIsValid;
}

// If the right board position is empty or contains a valid tile it returns true 
bool GameEngine::checkRightIsValid(Tile* tile, int row, int col)
{
    bool rightIsValid = false;
    // Checks entire line for either same colour or shape.
    // First checks if the right-most position contains a tile.
    if (!(board->isEmpty(row, col + 1)))
    {
        // Following checks will then continue along a line to check if they match by colour
        if (board->getTile(row, col + 1)->getColour() == tile->getColour())
        {
            if (sixTileLineCheck(row, col, RIGHT, tile, COLOUR))
            {
                rightIsValid = true;
            }
        }
        // Following checks will then continue along a line to check if they match by shape
        else if (board->getTile(row, col + 1)->getShape() == tile->getShape())
        {
            if (sixTileLineCheck(row, col, RIGHT, tile, SHAPE))
            {
                rightIsValid = true;
            }
        }
    } 
    else
    {
        rightIsValid = true;
    }
    return rightIsValid;
}

// If the below board position is empty or contains a valid tile it returns true 
bool GameEngine::checkDownIsValid(Tile* tile, int row, int col)
{
    bool downIsValid = false;
    // Checks entire line for either same colour or shape.
    // First checks if the down-most position contains a tile.
    if (!(board->isEmpty(row + 1, col)))
    {
        // Following checks will then continue along a line to check if they match by colour
        if (board->getTile(row + 1, col)->getColour() == tile->getColour())
        {
            if (sixTileLineCheck(row, col, DOWN, tile, COLOUR))
            {
                downIsValid = true;
            }
        }
        // Following checks will then continue along a line to check if they match by shape
        else if (board->getTile(row + 1, col)->getShape() == tile->getShape())
        {
            if (sixTileLineCheck(row, col, DOWN, tile, SHAPE))
            {
                downIsValid = true;
            }

        }
    } 
    else
    {
        downIsValid = true;
    }    

    return downIsValid;
}

// If the above board position is empty or contains a valid tile it returns true 
bool GameEngine::checkUpIsValid(Tile* tile, int row, int col)
{
    bool upIsValid = false;
    // Checks entire line for either same colour or shape.
    // First checks if the up-most position contains a tile.
    if (!(board->isEmpty(row - 1, col)))
    {
        // Following checks will then continue along a line to check if they match by colour
        if (board->getTile(row - 1, col)->getColour() == tile->getColour())
        {
            if (sixTileLineCheck(row, col, UP, tile, COLOUR))
            {
                upIsValid = true;
            }
        }
        // Following checks will then continue along a line to check if they match by shape
        else if (board->getTile(row - 1, col)->getShape() == tile->getShape())
        {
            if (sixTileLineCheck(row, col, UP, tile, SHAPE))
            {
                upIsValid = true;
            }
        }
    } 
    else
    {
        upIsValid = true;
    }
    return upIsValid;
}

/*
 * Return true if line already has six tiles
 * Counts all tiles in a line depending on the direction
 * Loop stops when it reaches six tiles, has a duplicate, or reaches an empty board position.
 */
bool GameEngine::sixTileLineCheck(int row, int col, char direction, Tile* tile, string type)
{
    /*
      - lineIsCompatible: details whether the line is valid for a placement
      - count: keeps track of the number of tiles in that line
      - stop: value to exits the loop
      - duplicateFound: returns true if the same tile being placed is already found in the line
      - illegalTile: Illegal tiles are tiles that are not valid for placement, making sure that the 
        line is of same colour or same shape
     */
    bool lineIsCompatible = false;
    int count = 1;
    bool stop = false;
    bool duplicateFound = false;
    bool illegalTile = false;
    if (direction == UP)
    {
        // Loops for six potential tiles
        while ((count <= MAX_TILES_IN_LINE && !stop))
        {
            // Continues as long as it is in bounds of the board
            if ((row-count >= board->getMaxRow()-board->getMaxRow()))
            {
                if (!board->isEmpty(row-count, col))
                {
                    // Checking duplicates on line
                    if (board->getTile(row-count, col)->isDuplicate(tile))
                    {
                        stop = true;
                        duplicateFound = true;
                    }

                    // Checking a line's tiles for the same colour
                    if (type == COLOUR)
                    {
                        if (!board->getTile(row-count, col)->hasSameColour(tile))
                        {
                            illegalTile = true;
                            stop = true;
                        }
                    }
                    
                    // Checking a line's tiles for the same shape
                    else if (type == SHAPE)
                    {
                        if (!board->getTile(row-count, col)->hasSameShape(tile))
                        {
                            illegalTile = true;
                            stop = true;
                        }   
                    }
                    
                    ++count;
                }
                else if (board->isEmpty(row-count, col))
                {
                    stop = true;
                }
            }
            else
            {
                stop = true;
            }
        }

    }

    // Same processs for lines that points downwards
    else if (direction == DOWN)
    {
        while ((count <= MAX_TILES_IN_LINE && !stop) )
        {
            if (row+count < board->getMaxRow())
            {
                if (!board->isEmpty(row+count, col))
                {
                    if (board->getTile(row+count, col)->isDuplicate(tile))
                    {
                        stop = true;
                        duplicateFound = true;
                    }
                    if (type == COLOUR)
                    {
                        if (!board->getTile(row+count, col)->hasSameColour(tile))
                        {
                            illegalTile = true;
                            stop = true;
                        }
                    }

                    else if (type == SHAPE)
                    {
                        if (!board->getTile(row+count, col)->hasSameShape(tile))
                        {
                            illegalTile = true;
                            stop = true;
                        }   
                    }
                    
                    ++count;
                }
                else if (board->isEmpty(row+count, col))
                {
                    stop = true;
                }
            }

            else
            {
                stop = true;
            }

        }
    }

    // Same process for lines that point left
    else if (direction == LEFT)
    {
        while ((count <= MAX_TILES_IN_LINE && !stop))
        {
            if ((col-count >= board->getMaxCol()-board->getMaxCol()))
            {
                if (!board->isEmpty(row, col-count))
                {
                    if (board->getTile(row, col-count)->isDuplicate(tile))
                    {
                        stop = true;
                        duplicateFound = true;

                    }

                    if (type == COLOUR)
                    {
                        if (!board->getTile(row, col-count)->hasSameColour(tile))
                        {
                            illegalTile = true;
                            stop = true;
                        }
                    }

                    else if (type == SHAPE)
                    {
                        if (!board->getTile(row, col-count)->hasSameShape(tile))
                        {
                            illegalTile = true;
                            stop = true;
                        }   
                    }
                    
                    ++count;
                }
                else if(board->isEmpty(row, col-count))
                {
                    stop = true;
                }
            }
            else
            {
                stop = true;
            }
        }
    }

    // Same process for lines that point right
    else if (direction == RIGHT)
    {
        while ((count <= MAX_TILES_IN_LINE && !stop))
        {
            if ((col+count < board->getMaxCol()))
            {
                if (!board->isEmpty(row, col+count))
                {

                    if (board->getTile(row, col+count)->isDuplicate(tile))
                    {
                        stop = true;
                        duplicateFound = true;
                    }

                    if (type == COLOUR)
                    {
                        if (!board->getTile(row, col+count)->hasSameColour(tile))
                        {
                            illegalTile = true;
                            stop = true;
                        }
                    }

                    else if (type == SHAPE)
                    {
                        if (!board->getTile(row, col+count)->hasSameShape(tile))
                        {
                            illegalTile = true;
                            stop = true;
                        }   
                    }  
                    
                    ++count;
                }
                else if (board->isEmpty(row, col+count))
                {
                    stop = true;
                }
            }
            else
            {
                stop = true;
            }

        }
    }
    
    /* 
    * Loops stop when
    * - Line eventually reaches an empty spot
    * - There is a duplicate tile
    */

    // If it reaches the end of the line where stop was never called and there are 6 full tiles
    if (count == MAX_TILES_IN_LINE && !stop)
    {
        lineIsCompatible = false;
    }

    /*
     * If stop was called because there's an empty spot and a duplicate was not found
     * The line should then be okay for the player to place a tile
     * If there are duplicates found, line is not compatible
     * If the rest of the line's colours and shapes are compatible then the placement is okay
     */
    if (stop && !duplicateFound && !illegalTile)
    {
        if (count == MAX_TILES_IN_LINE)
        {
            // Updates score here as well if the player manages to land 
            // six tiles and create a complete line
            current_round_score += count;
            cout << "\nQWIRKLE \n+6 BONUS POINTS\n" << endl;
        }
        lineIsCompatible = true;
        current_round_score += count;

    }
    return lineIsCompatible;
}

bool GameEngine::hasSurroundingTiles(int row, int col)
{
    bool hasTile = false;
    // directional check returns true if up, down, left or right is not empty
    if (!board->isEmpty(row-1, col) || !board->isEmpty(row+1, col) || !board->isEmpty(row, col-1) || !board->isEmpty(row, col+1))
    {
        hasTile = true;
    }
    return hasTile;
}
//Check that tile played share one attribute (color or shape) and that it is placed in the same line
bool GameEngine::validTilePlacement(Tile* tile, int row, int col, shared_ptr<Player> player)
{
    // If it has found a tile that has a matching colour or shape, then isValid is FALSE
    bool isValid = false;
    if (!edgeCase(row, col))
    {
        // Check that the tile placement is next to a tile
        if (hasSurroundingTiles(row, col))
        {
            // Resets score to add at start of each round
            current_round_score = 0;
            // Makes sure the tile either has a same shape or colour and is valid
            if (isSameColourOrShape(tile, row, col))
            {
                isValid = true;
            }
            //exit if conditions and return is Valid           
        }


    }
    else if (edgeCase(row, col))
    {
        current_round_score = 0;
        if (hasSameColourOrShapeEdgeCases(tile, row, col))
        {
            isValid = true;   
            //exit if conditions and rtn isValid
        }
    }

    if (!isValid && !cpuTurn && !askingHint)
    {
        cout << "\nInvalid placement\n" << endl;
    }
    return isValid;
}

// Returns true if the row or col is along the edge of the board
bool GameEngine::edgeCase(int row, int col)
{
    bool flag = false;
    if (row == board->getMaxRow() - board->getMaxRow() || row == board->getMaxRow() - 1 || 
        col == board->getMaxCol() - board->getMaxCol() || col == board->getMaxCol() - 1)
    {
        flag = true;
    }

    return flag;
}

// Returns true if up, down, left or right, depending on the edge case, has a tile of same colour or shape 
bool GameEngine::hasSameColourOrShapeEdgeCases(Tile* tile, int row, int col)
{
    bool flag = false;
    // If it is Top most row, do not check up position
    if (row == board->getMaxRow()-board->getMaxRow() && !flag)
    {
        // If is in top left corner, then only check right and down position
        if(col == board->getMaxCol()-board->getMaxCol() && !flag)  
        {
            // Now we check is there is an adjacent tile to check against
            if (!board->isEmpty(row, col+1) || !board->isEmpty(row+1, col))
            {
                if (checkRightIsValid(tile, row, col) && checkDownIsValid(tile, row, col))
                {
                    flag = true;
                }
            }

        }
        // If is in top right corner, then only check left and down position
        else if (col == board->getMaxCol()-1 && !flag)
        {
            if (!board->isEmpty(row, col-1) || !board->isEmpty(row+1, col))
            {
                if (checkLeftIsValid(tile, row, col) && checkDownIsValid(tile, row, col))
                {
                    flag = true;
                }
            }

        }
        // Check left, down, right
        else if (!flag)
        {
            if (!board->isEmpty(row, col-1) || !board->isEmpty(row+1, col) || !board->isEmpty(row, col+1))
            {
                if (checkLeftIsValid(tile, row, col) && checkDownIsValid(tile, row, col) && checkRightIsValid(tile, row, col))
                {
                    flag = true;
                }
            }

        }
    }
 
    // Bottom most row
    if (row == board->getMaxRow()-1 && !flag)
    {
        // bottom left corner, check for up and right
        if (col == board->getMaxCol()-board->getMaxCol() && !flag)
        {
            if (!board->isEmpty(row - 1, col) || !board->isEmpty(row, col+1))
            {
                if (checkUpIsValid(tile, row, col) && checkRightIsValid(tile, row, col))
                {
                    flag = true;
                }
            }

        }

        // bottom right corner, check up and left
        else if (col == board->getMaxCol()-1 && !flag)
        {
            if (!board->isEmpty(row-1, col) || !board->isEmpty(row, col-1))
            {
                if (checkUpIsValid(tile, row, col) && checkLeftIsValid(tile, row, col))
                {
                    flag = true;
                }
            }

        }

        // do checks on left, above, right of tile
        else if (!flag)
        {
            if (!board->isEmpty(row, col-1) || !board->isEmpty(row-1, col) || !board->isEmpty(row, col+1))
            {
                if (checkLeftIsValid(tile, row, col) && checkUpIsValid(tile, row, col) && checkRightIsValid(tile, row, col))
                {
                    flag = true;
                }
            }

        }
    }

    // Left most side
    if (col == board->getMaxCol()-board->getMaxCol() && !flag)
    {
        // top left corner, check down and right
        if (row == board->getMaxRow()-board->getMaxRow() && !flag)
        {
            if (!board->isEmpty(row+1, col) || !board->isEmpty(row, col+1))
            {
                if (checkDownIsValid(tile, row, col) && checkRightIsValid(tile, row, col))
                {
                    flag = true;
                }
            }
        }

        // bottom left corner, check up and right
        else if (row == board->getMaxRow()-1 && !flag)
        {
            if (!board->isEmpty(row-1, col) || !board->isEmpty(row, col+1))
            {
                if (checkUpIsValid(tile, row, col) && checkRightIsValid(tile, row, col))
                {
                    flag = true;
                }
            }
        }
        
        // do checks on above, bottom, right of tile 
        else if (!flag)
        {
            if (!board->isEmpty(row-1, col) || !board->isEmpty(row+1, col) || !board->isEmpty(row, col+1))
            {
                if (checkUpIsValid(tile, row, col) && checkRightIsValid(tile, row, col) && checkDownIsValid(tile, row, col))
                {
                    flag = true;
                }
            }

        }
    }

    // Right most side
    if (col == board->getMaxCol()-1 && !flag)
    {
        // top right corner, check down and left
        if (row == board->getMaxRow()-board->getMaxRow()  && !flag)
        {
            if (!board->isEmpty(row+1, col) || !board->isEmpty(row, col-1))
            {
                if (checkDownIsValid(tile, row, col) && checkLeftIsValid(tile, row, col))
                {
                    flag = true;
                }
            }

        }

        // bottom right corner, check up and left
        else if (row == board->getMaxRow()-1 && !flag)
        {   
            if (!board->isEmpty(row-1, col) || !board->isEmpty(row, col-1))
            {
                if (checkUpIsValid(tile, row, col) && checkLeftIsValid(tile, row, col))
                {
                    flag = true;
                }
            }

        }

       // do checks on left, above, bottom of tile 
        else if (!flag)
        {
            if (!board->isEmpty(row, col-1) || !board->isEmpty(row-1, col) || !board->isEmpty(row+1, col))
            {
                if (checkLeftIsValid(tile, row, col) && checkUpIsValid(tile, row, col) && checkDownIsValid(tile, row, col))
                {
                    flag = true;
                }
            }

        }

    }

    return flag;
}

// Returns true if all directions up, down, left and right of a tile either has the same colour or shape
bool GameEngine::isSameColourOrShape(Tile* tile, int row, int col)
{
    bool returnFlag = false;

    if (checkUpIsValid(tile, row, col) && checkDownIsValid(tile, row, col) && 
    checkLeftIsValid(tile, row, col) && checkRightIsValid(tile, row, col))
    {
        returnFlag = true;
    }

    return returnFlag;
}

// Returns true if a player has an selected tile
bool GameEngine::playerHasTile(string tileString, shared_ptr<Player> player)
{
    bool hasTile = false;

    int indexOfTileInHand = player->getHand()->getIndexOfTileStr(tileString);

    if (indexOfTileInHand != -1)
    {
        hasTile = true;
    }
    else
    {
        cout << "\nPlayer does not have tile\n" << endl;
    }

    return hasTile;
}

// This is called at the end of each turn to switch the turns over to the next player
void GameEngine::setOtherPlayerTurn(std::shared_ptr<Player> currentPlayer)
{
    if (!cpuGame)
    {
        // Searches for index of player
        int playerIndex = -1;
        for (int i = 0; i < numPlayers; ++i)
        {
            playerTurns[i] = false;
            if (playerVector[i]->getName() == currentPlayer->getName())
            {
                playerIndex = i;
            }
        }

        // Next player turn
        if (playerIndex < numPlayers-1)
        {
            playerTurns[playerIndex+1] = true;
        }

        // If last player, start from the beginning
        else if (playerIndex == numPlayers-1)
        {
            playerTurns[numPlayers-numPlayers] = true;
        }
  

    }

    // CPU mode only consists of one actual player, the first player
    else
    {
        if (playerTurns[0] == true)
        {
            playerTurns[0] = false;
            cpuTurn = true;
        }     
        else if (playerTurns[0] == false)
        {
            playerTurns[0] = true;
            cpuTurn = false;
        }
    }

}

// Summary of game details at the end of round
void GameEngine::printRound(std::shared_ptr<Player> player)
{
    cout << player->getName() << ", it's your turn!" << endl;
    for (int i = 0; i < numPlayers; ++i)
    {
        cout << "Score for " << playerVector[i]->getName() << ": " << playerVector[i]->getScore() << endl;  
    }

    board->printBoard(); 
    cout << "\n";

    cout << "Your hand is" << endl;
    player->getHand()->print();
    cout << "\n";
}

// Called at the start of a new game to set a player with tiles from the tilebag
void GameEngine::giveHand(std::shared_ptr<Player> player)
{
    for(int i = 0; i < MAX_HAND; i++)
    {
        replenishHandTiles(player);
    }    
} 

// This method is used to provide hints to the player
// Finds a board placement that will provide the most points
void GameEngine::findOptimalPlacement(std::shared_ptr<Player> player)
{
    if (firstTurn)
    {
        cout << "You have the first turn! Place it anywhere!\n" << endl;
    }

    else
    {
        shared_ptr<BST> pointsTree = std::make_shared<BST>();
        bool empty = true;

        // Loops through each possible placement on the board 
        // for each tile in the player's hand
        for (int k = 0; k < player->getHand()->getLength(); ++k)
        {
            for (int i = 0; i < board->getMaxRow(); ++i)
            {
                for (int j = 0; j < board->getMaxCol();++j)
                {
                    if (board->isEmpty(i, j))
                    {
                        if (validTilePlacement(player->getHand()->getTile(k), i, j, player))
                        {
                            std::shared_ptr<Tile> tileInTree = std::make_shared<Tile>((player->getHand()->getTile(k)->getTileAsString()));
                            pointsTree->add(current_round_score, tileInTree, i, j);
                            empty = false;                

                        }

                    }
                }
            }
        }

        if (empty)
        {
            if (tileBag->getLength() > 0)
            {
                cout << "\nYour hand has no viable tiles to place, try replacing a tile\n" << endl;
            }
            else
            {
                cout << "\nYou can't place anywhere and there are no tiles left in the tile bag." << endl;
                cout << "You should skip your turn\n" << endl;

            }
        }

        else
        {
            // Provides hints to see where to place for optimal points
            std::shared_ptr<BST_Node> maxNode = pointsTree->getMaxNode();
            cout << "Try placing " << maxNode->tile->getTileAsString() << " at " 
                                   << (char)((maxNode->row)+ASCII) << maxNode->col 
                                   << " for " << maxNode->points << " points" 
                                   << "\n" << endl;
        }

    }
}

void GameEngine::printCommands()
{
    cout << "Placing tiles:\t\t place <tile> at <position>" << endl;
    cout << "Replacing tiles:\t replace <tile>" << endl;
    cout << "Skip turn:\t\t skip" << endl;
    cout << "Provides hints:\t\t hint" << endl;
    cout << "Quits to menu:\t\t quit" << endl;
    cout << endl;
}