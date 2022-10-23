#include<iostream>
#include "Task1.h"
#include<string>
//                     Task 2: Form a binary tree with the given expression                        

///Creating a struct node that will form the binary tree 
struct Node{
    Node* left;
    char data;
    Node* right;
};

///Declaring the root of the binary tree globally
struct Node* root;

///Checking if a given character is an Operator
bool IsOperator(char c){
    return c=='('||c=='*'||c=='+'||c=='~'||c==')'||c=='>';
}

void printTree(std::string prefix, Node* rootnode, bool isLeft)
{
    if( rootnode != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        std::cout << rootnode->data << std::endl;

        // enter the next tree level - left and right branch
        printTree( prefix + (isLeft ? "|   " : "    "), rootnode->left, true);
        printTree( prefix + (isLeft ? "|   " : "    "), rootnode->right, false);
    }
}

///function that uses explicit stack to add each character from the string parameter which in this case is the prefix expression
void AddToBinaryTree(std::string str){ 
    
    Node* temproot = new Node();
    
    temproot -> left = NULL;
    temproot-> right = NULL;
    temproot->data = str[0];
   
    root= temproot;
    Stack<Node*> S;
    
    S.push(root);
    
    for(int i=1;i<str.length();i++){
        Node* temp = new Node();
        temp->left = NULL;
        temp->data = str[i];
        temp->right = NULL;
       
        if(S.top()->left==NULL&&S.top()->right==NULL&&IsOperator(S.top()->data)&&S.top()->data!='~'){
            S.top()->left=temp;
            S.push(temp);
        }
        else if(S.top()->left==NULL && S.top()->right==NULL && S.top()->data=='~'){
            S.top()->right = temp;
            S.push(temp);
        }
        else if(S.top()->data=='~'&&S.top()->right!=NULL){
            S.pop();
            i--;
        }
        else if(S.top()->left!=NULL && S.top()->right==NULL){
            S.top()->right = temp;
            S.push(temp);
           
        }
        else if((S.top()->left!=NULL && S.top()->right!=NULL)||!IsOperator(S.top()->data)){
           
            S.pop();
            i--;

        }
    }   
    printTree("",root,false);
}



