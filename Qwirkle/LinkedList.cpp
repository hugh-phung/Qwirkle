#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList()
{
    this->head = nullptr;
    this->tail = nullptr; 
    this->length = 0;
}

LinkedList::~LinkedList()
{
    clear();
}

int LinkedList::getLength()
{
    return length;
}

std::string LinkedList::colour(Colour colour)
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

// Returns a string of all the contents in the linked list as "R1,Y3,B2" etc
std::string LinkedList::getContents()
{
    std::string linkedListContents = "";
    Node* current = head;
    if (current != nullptr && current->next != nullptr)
    {
        while (current->next!= nullptr)
        {
            linkedListContents += current->tile->getColour() + std::to_string(current->tile->getShape()) + ",";
            current = current->next;
        }
        linkedListContents += current->tile->getColour() + std::to_string(current->tile->getShape());
    }

    else if (current != nullptr)
    {
        linkedListContents += current->tile->getColour() + std::to_string(current->tile->getShape());
    }

    return linkedListContents;
}

// Prints out the contents in the linked list as "R1,Y3,B2" etc
void LinkedList::print()
{
   Node* current = head;
   if (current != nullptr && current->next != nullptr)
   {
    while (current->next!= nullptr)
    {
        std::cout << colour(current->tile->getColour()) << current->tile->getColour() << current->tile->getShape() << RESET_COLOUR << ",";
        current = current->next;
    }
    std::cout << colour(current->tile->getColour()) << current->tile->getColour() << current->tile->getShape() << RESET_COLOUR << std::endl;

   }

   else if (current != nullptr)
   {
        std::cout << colour(current->tile->getColour()) << current->tile->getColour() << current->tile->getShape() << RESET_COLOUR << std::endl;
   }
}

void LinkedList::clear()
{
    while (head != nullptr)
    {
        deleteFront();
    }
}

// returns a tile at the index 'i'
Tile* LinkedList::get(int i)
{
    Node* currentNode = head;
    int x = 0;
    Tile* returnValue = nullptr;

    while (currentNode != nullptr)
    {
        if (x == i)
        {
            returnValue = currentNode->tile;
        }
        currentNode = currentNode->next;
        ++x;
    }

    return returnValue;
}

void LinkedList::addFront(Tile* tile)
{
    Node* newNode = new Node(tile, nullptr);
    newNode->next = head;
    if (head != nullptr)
    {
        head->prev = newNode;
    }

    else
    {
        tail = newNode;
    }

    head = newNode;
    ++length;
}

void LinkedList::addBack(Tile* tile)
{
    Node* newNode = new Node(tile, nullptr);
    newNode->prev = tail;

    if (tail != nullptr)
    {
        tail->next = newNode;
    }

    else
    {
        head = newNode;
    }

    tail = newNode;
    ++length;
}

void LinkedList::deleteBack()
{
    if (tail != nullptr)
    {
        Node* deleteNode = tail;
        tail = tail->prev;

        if (tail != nullptr)
        {
            tail->next = nullptr;
        }

        else
        {
            head = nullptr;
        }
        --length;
        delete deleteNode;
        deleteNode = nullptr;
    }
}

// Adds a tile at a certain index in the linked list
void LinkedList::addAt(Tile* tile, int index){

    Node* newNode = new Node(tile, nullptr);

    Node* currentNode = head;
    int count = 0;

    if (head == nullptr && index == 0)
    {
        addFront(tile);
    }

    else if (index <= length && index >= 0 && head != nullptr)
    {
        if (index == 0)
        {
            addFront(tile);
        }

        else if (index == length)
        {
            addBack(tile);
        }
        else 
        {
            while (count < index-1)
            {
                currentNode = currentNode->next;
                ++count;
            }

            if (currentNode != nullptr)
            {
                if (currentNode->next != nullptr)
                {
                    Node* nodeAfter = currentNode->next;
                    currentNode->next = newNode;
                    newNode->next = nodeAfter;
                    nodeAfter->prev = newNode;
                    newNode->prev = currentNode;
                    ++length;
                }
            }
        }

    }

    else if (head == nullptr)
    {
        std::cout << "No contents available" << std::endl;
    }

    else if (index > length || index < 0)
    {
        std::cout << "Invalid index" << std::endl;
    }
}

// Deletes a tile at the index 'i'
void LinkedList::deleteAt(int i)
{
    if (i >= 0 && i < length)
    {
        if (i == 0)
        {
            deleteFront();
        }

        else if (i == length)
        {
            deleteBack();
        }

        else{
            Node* currentNode = head;
            if (head != nullptr)
            {
                int count = 0;
                while (count < i)
                {
                    currentNode = currentNode->next;
                    ++count;
                }

                if (currentNode->next == nullptr)
                {
                    tail = currentNode->prev;
                }

                else
                {
                    currentNode->next->prev = currentNode->prev;
                }

                if (currentNode->prev == nullptr)
                {
                    head = currentNode->next;
                }

                else
                {
                    currentNode->prev->next = currentNode->next;
                }

                delete currentNode;
                currentNode = nullptr;
                --length;
            }
        }
    }
    
}

void LinkedList::deleteFront()
{
    if (head != nullptr)
    {
        Node* deleteNode = head;
        head = head->next;

        if (head != nullptr)
        {
            head->prev = nullptr;

        }

        else
        {
            tail = nullptr;
        }

        delete deleteNode;
        deleteNode = nullptr;
        --length;
    }
    
}
