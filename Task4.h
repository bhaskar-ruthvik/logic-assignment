#include <iostream>
#include "Task3.h"

//                    Task 4: Compute the height of the binary tree

/// A function that recursively traverses the tree until it reaches a propositional atom and starts computing the height by add to itself the max height between its left and right children. 
int FindTreeHeight(Node* rootnode){
    if(rootnode==NULL){
        return 0;
    }
    int left_subtree_height = FindTreeHeight(rootnode->left);
    int right_subtree_height = FindTreeHeight(rootnode->right);

    if(right_subtree_height>=left_subtree_height){
        return right_subtree_height +1;
    } 

    return left_subtree_height+1;

}