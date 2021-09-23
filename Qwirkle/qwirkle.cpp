
#include "LinkedList.h"
#include "Board.h"
#include "TileBag.h"
#include "Menu.h"

#include <iostream>

#define EXIT_SUCCESS    0

int main(void) {

   std::cout << "Welcome to Qwirkle!" << std::endl;
   std::cout << "-------------------" << std::endl;
   std::shared_ptr<Menu> menu = std::make_shared<Menu>();
   menu->displayMenu();

   return EXIT_SUCCESS;
}
