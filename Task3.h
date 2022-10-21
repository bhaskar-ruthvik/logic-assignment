#include <iostream>
#include "Task2.h"

//                     Task 3: Print the nodes of the binary tree by using in-order traversal

/// Recursive function that traverses the binary tree and prints the nodes of the tree using in-order traversal
void ParseBinaryTree(Node* rootnode){
    if(rootnode==NULL){
        return;
    }
    ParseBinaryTree(rootnode->left);
    std::cout<< rootnode->data;
    ParseBinaryTree(rootnode->right);


}

