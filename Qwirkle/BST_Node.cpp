#include "BST_Node.h"

BST_Node::BST_Node(int points, std::shared_ptr<Tile> tile, int row, int col)
{
    this->points = points;
    this->tile = tile;
    this->row = row;
    this->col = col;
    left = nullptr;
    right = nullptr;
}

BST_Node::BST_Node(const BST_Node& other)
{
    this->points = other.points;
    this->tile = other.tile;
    this->row = other.row;
    this->col = other.col;
    this->left = other.left;
    this->right = other.right;
}

BST_Node::~BST_Node()
{
    left = nullptr;
    right = nullptr;
}