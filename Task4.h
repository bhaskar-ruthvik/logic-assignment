#include <iostream>
#include "Task3.h"

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