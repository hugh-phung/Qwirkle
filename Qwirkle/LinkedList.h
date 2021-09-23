#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

class LinkedList {
public:

   LinkedList();
   ~LinkedList();

   void print();
   int getLength();
   
   Tile* get(int i);

   void addFront(Tile* tile);
   void addBack(Tile* tile);
   void addAt(Tile* tile, int index);

   void deleteFront();
   void deleteBack();
   void deleteAt(int i);
   
   std::string getContents();
   
   void clear();

private:
   Node* head;
   Node* tail;
   int length; 
   std::string colour(Colour colour);

};

#endif // ASSIGN2_LINKEDLIST_H
