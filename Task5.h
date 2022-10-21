#include <iostream>
#include "Task4.h"

//                  Task 5: Evaluate the propositional expression with the provided truth values

/// A function that takes in the truth values of two propositional atoms and the operator and computes resulting truth value
bool EvaluateProposition(bool prop1,bool prop2, char op){ 
    switch(op){
        case '*':
            return prop1&&prop2;
            break;
        case '+':
            return prop1||prop2;
            break;
        case '>':
            return !prop1||prop2;
            break;
        default: 
            return false;
    }
}

///A function to evaluate negation specifically
bool EvaluateNegation(bool prop1){
    return !prop1;
}

///Array that is going to contain the propositional atoms without repetition.
char atoms[1000] ={0};

///Array that contains the corresponding truth values for the propositional atoms at the same index in array atoms. 
bool truth_values[1000] = {0};

///Variable that contains the number of propositional atoms in a given expression. 
int len = 0; 

///A function that checks if a certain propositional atom occurs twice in a given expression
bool Contains(char atoms[],char c){ 
    for(int i=0;i<len;i++){
        if(atoms[i]==c){
            return true;
        }
    }
    return false;
    
}

/// A function that loops through the string and checks for duplicates and adds the propositional atoms to an array
void FindPropositionalAtoms(std::string str){
    
    for(int i=0; i<str.length();i++){
        if(!IsOperator(str[i])&&!Contains(atoms,str[i])){
            atoms[len++] = str[i]; 
            
        }
    }
    std::cout<< "The propositional expression contains the following propositional atoms: "<<std::endl;
     for(int i=0; i<len;i++){
        std::cout << atoms[i] << ' ';
     }
  
  std::cout<< std::endl;
  

}

/// A function that takes in input from the user and adds the corresponding truth values of each propositional atom to the same index in another array that holds the truth values
void AssignTruthValues(){
    
    for(int i=0;i<len;i++){
        std::cout<< atoms[i] << " = ";
            bool truth_value;
            std::cin>> truth_value;
            truth_values[i] = truth_value;
    }
    std::cout<< "The following are the truth values provided"<<std::endl;
    std::cout<< "\tAtom\tTruthValue\n";
    for(int i=0;i<len;i++){
        std::cout << '\t' << atoms[i] << '\t' << truth_values[i] << '\n';
    }

    std::cout<< std::endl;
    
}

///A function to the find the truth value provided for the propositional atom given the atom
bool ValueAt(char c){
    for(int i=0;i<len;i++){
        if(atoms[i]==c){
            return truth_values[i];
        }
    }
    return false;
}

/// A function that recursively goes to the propositional atom on the leftmost of the tree and starts evaluating the truth value of the expression from bottom up
bool ComputeTruthValues(Node* rootnode){
    int i =0;
    if(!IsOperator(rootnode->data)){
        return ValueAt(rootnode->data);
    }
    if(rootnode->data!='~'){
        bool lv = ComputeTruthValues(rootnode->left);
        bool rv = ComputeTruthValues(rootnode->right);
        return EvaluateProposition(lv,rv,rootnode->data);
    }
    else{
        return EvaluateNegation(ComputeTruthValues(rootnode->right));
    }
}
