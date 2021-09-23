#include "Menu.h"
#include "GameEngine.h"
#include <memory>

Menu::~Menu()
{
    
}
void Menu::displayMenu(){

    bool menuDisplay = true;

    while (menuDisplay && !std::cin.eof())
    {
        std::cout << "Menu" << std::endl;
        std::cout << "----" << std::endl;
        std::cout << "1. New Game" << std::endl;
        std::cout << "2. Load Game" << std::endl;
        std::cout << "3. Credits" << std::endl;
        std::cout << "4. Quit" << std::endl;
        std::cout << "\n";
        std::cout << "> "; 

        int selection = 0;
        std::cin >> selection;
        std::cout << std::endl;
        if (selection == 1)
        {
            newGame();

        }

        else if (selection == 2)
        {
            loadGame();

        }

        else if (selection == 3)
        {
            credits();

        }
        
        else if (selection == 4 || !cin.good())
        {
            menuDisplay = false;
            std::cout << "Goodbye" << std::endl;
        }

        else 
        {
            std::cout << "\nInvalid selection, please try again\n" << std::endl;
        }

    }
}

void Menu::newGame()
{
    gameEngine = std::make_shared<GameEngine>();
    gameEngine->newGame();
}

void Menu::credits()
{    
    std::cout << "-----------------------------------" << std::endl;
    std::cout << "INDIVIDUAL COMPONENT" << std::endl;
    std::cout << "MILESTONE 3" << std::endl;
    std::cout << "Name: Hugh Trung-Hieu Phung" << std::endl;
    std::cout << "Student ID: s3842508" << std::endl;
    std::cout << "Email: s3842508@student.rmit.edu.au" << std::endl;

    std::cout << "-----------------------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    std::cout << "Name: Abd-Alrahman Ibrahim El Sayed" << std::endl;
    std::cout << "Student ID: s3542549" << std::endl;
    std::cout << "Email: s3542549@student.rmit.edu.au" << std::endl;
    std::cout << std::endl;

    std::cout << "Name: Ary Vinicio Pietroski Ramires" << std::endl;
    std::cout << "Student ID: s3857679" << std::endl;
    std::cout << "Email: s3857679@student.rmit.edu.au" << std::endl;
    std::cout << std::endl;

    std::cout << "Name: David Li Hong Xu" << std::endl;
    std::cout << "Student ID: s3844051" << std::endl;
    std::cout << "Email: s3844051@student.rmit.edu.au" << std::endl;
    std::cout << std::endl;
    
    std::cout << "\u001b[32m";
    std::cout << "Name: Hugh Trung-Hieu Phung" << std::endl;
    std::cout << "Student ID: s3842508" << std::endl;
    std::cout << "Email: s3842508@student.rmit.edu.au" << std::endl;
    std::cout << "\u001b[32m";
    std::cout << "\u001b[0m";
    

    std::cout << "-----------------------------------" << std::endl;

}

void Menu::loadGame()
{
    bool loop = true;
    std::string filePath;
    std::cout << "\nEnter the filename from which load a game" << std::endl;
    while (loop && !std::cin.eof())
    {
        if (!cin.eof())
        {
            std::cout << "> " ;
            std::cin >> filePath;

            if (checkFileExists(filePath))
            {
                // call game engine loadTheGame
                gameEngine = std::make_shared<GameEngine>();
                gameEngine->loadTheGame(filePath);
                loop = false;
            }

            else
            {
                loop = false;
            }
        }
        else
        {
            std::cout << "\nGoodbye\n" << std::endl;
        }
   
    }
}

// A helper method that checks if the specified file from the file path exists
bool Menu::checkFileExists(std::string filePath) 
{ 
    bool exists = false;
    std::ifstream saveFile(filePath);
    if (saveFile.fail()) 
    { 
        exists = false;
    }
    else 
    {
        exists = true;
    }
    saveFile.close();
    return exists;
}