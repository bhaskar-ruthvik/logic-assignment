#include <iostream>
#include "Task5.h"
//The header files required for calculating execution time
#include <iomanip>
#include <chrono>
#include <ios>


int main(){
    std::string infix_expression;
    int iter;
    infix_expression = "a+b>c+d+e>f>g>h>i+j";
    //  using chrono to calculate execution time
    
    std::cout<< "The infix expression being used is the following: "<<infix_expression <<std::endl;
    auto start = std::chrono::high_resolution_clock::now(); 
    std::string prefix = PrefixConverter(infix_expression);
    std::cout<< "The prefix form of the entered infix expression is: "<<prefix << std::endl;
    AddToBinaryTree(prefix);
    std::cout<< "The expression obtained through in-order traversal of the binary tree is: ";
    ParseBinaryTree(root);
    std::cout<<"\nThe height of the binary tree obtained is: "<< FindTreeHeight(root) <<std::endl;
    truth_values[0]=truth_values[1]=truth_values[2]=truth_values[3]=truth_values[4]=truth_values[5]=truth_values[6]=truth_values[7]=truth_values[8]=truth_values[9]=0;
    std::cout<< "The evaluated truth value of the propositional expression with the given truth values is: "<< ComputeTruthValues(root);
    // continuation of the chrono related code to find time of execution 
    auto end = std::chrono::high_resolution_clock::now();  
    double time_taken = 
    std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    time_taken *= 1e-9;
    std::cout << "\nTime taken for program to execute is : " << std::fixed << time_taken << std::setprecision(9);
    std::cout << " seconds" << std::endl;

    
}