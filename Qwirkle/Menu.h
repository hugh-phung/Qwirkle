#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <fstream>

#include "GameEngine.h"

class Menu {
    public:
        //Display the menu
        void displayMenu();
        void newGame();
        void loadGame();
        void credits();
        ~Menu();

    private:
        std::shared_ptr<GameEngine> gameEngine;
        bool checkFileExists(std::string filePath);


};

#endif // MENU_H