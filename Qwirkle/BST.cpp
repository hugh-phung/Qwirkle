#include "BST.h"
#include <iostream>

BST::BST()
{
    root = nullptr;
}

BST::~BST()
{
    root = nullptr;
}

void BST::add(const int points, const std::shared_ptr<Tile> tile, const int row, const int col)
{
 
    root = add(root, points, tile, row, col);

}

std::shared_ptr<BST_Node> BST::add(std::shared_ptr<BST_Node> node, const int points, const std::shared_ptr<Tile> tile, const int row, const int col)
{
    std::shared_ptr<BST_Node> returnNode = nullptr;

    // Base case
    if (node == nullptr)
    {
        returnNode = std::make_shared<BST_Node>(points, tile, row, col);
    }

    else
    {
        // Add to left side of node
        if (points <= node->points)
        {
            std::shared_ptr<BST_Node> subtree = add(node->left, points, tile, row, col);
            node->left = subtree;
            returnNode = node;
        }

        // Add to right side of node
        else if (points > node->points)
        {
            std::shared_ptr<BST_Node> subtree = add(node->right, points, tile, row, col);
            node->right = subtree;
            returnNode = node;
        }
    }

    return returnNode;
}

std::shared_ptr<BST_Node> BST::getMaxNode()
{
    return getMaxNode(root);
}

// Recursively enters the right most node to find the greatest value
std::shared_ptr<BST_Node> BST::getMaxNode(std::shared_ptr<BST_Node> node)
{
    std::shared_ptr<BST_Node> returnNode = nullptr;
    if (node != nullptr)
    {
        if (node->right != nullptr)
        {
            returnNode = getMaxNode(node->right);
        }
        else
        {
            returnNode = node;
        }
    }

    return returnNode;
}

void BST::print()
{
    print(root);
}

void BST::print(std::shared_ptr<BST_Node> node)
{
    if (node != nullptr)
    {
        print(node->left);
        std::cout << node->points << std::endl;
        print(node->right);
    }
    
}

bool BST::contains(int points)
{
    return contains(root, points);
}

bool BST::contains(std::shared_ptr<BST_Node> node, int points)
{
    bool returnValue = true;
    if (node == nullptr)
    {
        returnValue = false;
    }

    else if (points < node->points)
    {
        returnValue = contains(node->left, points);
    }

    else if (points > node->points)
    {
        returnValue = contains(node->right, points);
    }

    return returnValue;
}
