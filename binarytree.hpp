#ifndef SDMUTILS_BINARYTREE_HPP
#define SDMUTILS_BINARYTREE_HPP

#include <iostream>

namespace sdm
{
    template<typename Type>
    class BinaryNode
    {
        Type data;
        BinaryNode* left = nullptr;
        BinaryNode* right = nullptr;

    public:
        constexpr BinaryNode(Type payload) : data(payload) {}
        ~BinaryNode() { if (left) delete left; if (right) delete right; }
        constexpr BinaryNode* getLeft() { return left; }
        constexpr BinaryNode* getRight() { return right; }
        constexpr Type getData() { return data; }
        constexpr void setLeft(BinaryNode* ptr) { left = ptr; }
        constexpr void setRight(BinaryNode* ptr) { right = ptr; }
        constexpr void setData(const Type& payload) { data = payload; }
    };
    template<typename Type>
    class BinaryTree
    {
        using Node = BinaryNode<Type>;
        Node* root = nullptr;

        constexpr void inorderPrint(Node* node)
        {
            if (!node) return;
            inorderPrint(node->getLeft());
            std::cout << node->getData() << std::endl;
            inorderPrint(node->getRight());
        }

    public:
        constexpr Node* getRoot() { return root; }
        constexpr void insert(Type payload)
        {
            Node* insert = new Node(payload);
            if (root == nullptr)
            {
                root = insert;
                return;
            }
            bool isLeft = false;
            Node* previous = root;
            Node* current = root;
            do
            {
                previous = current;
                isLeft = payload < current->getData();
                if (isLeft)
                    current = current->getLeft();
                else current = current->getRight();
            } while (current != nullptr);
            if (isLeft)
                previous->setLeft(insert);
            else previous->setRight(insert);
        }
        constexpr void print()
        {
            inorderPrint(root);
        }
    };
}

#endif //SDMUTILS_BINARYTREE_HPP
