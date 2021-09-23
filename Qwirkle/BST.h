#ifndef BST_H
#define BST_H

#include "BST_Node.h"
#include <memory>

class BST
{
    public:
        BST();
        ~BST();
        void add(const int points, const std::shared_ptr<Tile> tile, const int row, const int col);
        std::shared_ptr<BST_Node> getMaxNode();
        bool contains(int points);

        void print();

    private:
        std::shared_ptr<BST_Node> root;
        std::shared_ptr<BST_Node> add(std::shared_ptr<BST_Node> node, const int points, const std::shared_ptr<Tile> tile, const int row, const int col);
        std::shared_ptr<BST_Node> getMaxNode(std::shared_ptr<BST_Node> node);
        void print(std::shared_ptr<BST_Node> node);
        bool contains(std::shared_ptr<BST_Node> root, int points);



};

#endif // BST_H