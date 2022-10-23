#include <iostream>
#include "Task5.h"
#include <string>

/// A function that combines all the previous functions to run the tasks in the required order
void LogicAssignment(){
std::string infix;
    std::cout<< "This test was done on an AMD Ryzen 7 5800HS CPU and NVIDIA GTX1650 GPU"<<std::endl;
    std::cout<< "Enter a propositional statement in infix form: "<<std::endl;
    std::getline(std::cin,infix);
  
    std::string prefix = PrefixConverter(infix);
    std::cout<< "The prefix form of the statement is: "<< prefix << std::endl;
  
    AddToBinaryTree(prefix);
    std::cout<< "The in-order traversal of the parse tree leads to the equation: ";
    ParseBinaryTree(root);  

    std::cout<< "\nThe height of the parse tree is equal to: "<< FindTreeHeight(root)<<std::endl;
    
    FindPropositionalAtoms(infix);
    std::cout<< "Enter the truth value for the proposition: "<<std::endl;
    AssignTruthValues();

    std::cout<< "The output of the expression with the given truth values is " <<ComputeTruthValues(root);

    // continuation of the chrono related code to find time of execution 
    // auto end = std::chrono::high_resolution_clock::now();  
    // double time_taken = 
    // std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    // time_taken *= 1e-9;
    // std::cout << "\nTime taken for program to execute is : " << std::fixed << time_taken << std::setprecision(9);
    // std::cout << " seconds" << std::endl;
}