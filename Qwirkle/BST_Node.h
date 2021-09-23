#ifndef BST_NODE_H
#define BST_NODE_H

#include <memory>
#include "Tile.h"
class BST_Node
{
    public:
        BST_Node(int points, std::shared_ptr<Tile> tile, int row, int col);
        BST_Node(const BST_Node& other);
        ~BST_Node();

        int points;
        std::shared_ptr<Tile> tile;
        int row;
        int col;
        std::shared_ptr<BST_Node> left;
        std::shared_ptr<BST_Node> right;

};

#endif // BST_NODE_H