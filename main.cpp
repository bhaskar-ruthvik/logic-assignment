/// Logic Assignment - Propositional Logic
/// By Bhaskar Ruthvik Bikkina (2021A7PS1345H), Siddhant Srinivas(2021A7PS0050H), Soumil Ray(2021A7PS2652H)
///
/// The assignment has been written and tested on an Asus Zephyrus G14 with an AMD Ryzen 7 5800HS CPU, an NVIDIA GTX 1650 GPU, 16GB Dual-channel RAM and 1TB ROM. 
/// The IDE used for the project is Visual Studio Code for Windows x64 and the code has been written in C++ 20
/// Doxygen has been used to make the documentation work easier
/// The project uses a stack class implemented using a Linked-List and a Binary Tree as the Primary Data Structures
/// "using namespace std" has not been used so as to avoid name clashes with other functions in the STL library 
/// The memory usage has been tested using the visual studio code developer tools
/// The time taken by the program to execute has been measured using the chrono library along with some useful functions from iomanip and ios libraries
///
//including the required header files

#include <iostream>
#include <string>

//The header files required for calculating execution time
// #include <iomanip>
// #include <chrono>
// #include <ios>


//                       Task 1: Converting infix expression to prefix expression                               

/// We create a struct node using template T so as to accomodate for linked lists with different data type elements
template<class T> 
struct Listnode{
            T data; 
            Listnode* next; ///pointer pointing to same struct type
        };

/// Creating a stack class and implementing its functions 
template<class K>
class Stack{
    private:
        Listnode<K>* head= new Listnode<K>();
    public:
        void push(K c){     ///Adds a new node at the head of the linked list. Hence the time-complexity is O(1)
            Listnode<K>* temp = new Listnode<K>();
            temp->data = c;
            temp->next = head;
            head = temp;
         
        }
        void pop(){      ///Removes the node at the head of the linked list. So the time-complexity is O(1)
            Listnode<K>* temp1 = head;
            head = temp1->next;
            
        }
        K top(){   ///Returns the top of the stack which is the head of the linked list. Time-complexity is O(1)
            return head->data;
        }
        bool empty(){  ///Checks if the stack is empty and returns a bool. Time-complexity is O(1)
            if((head->data)==0){
                return true;
            }
            else{
                return false;
            }
            
        }
};

/// Reversing the string that was input by the user 
std::string ReversedExpression(std::string exp){
    
    for(int i=0;i<exp.length()/2;i++){ ///Loops through half the length of the string and swaps the first and last characters in order to reverse the string
        char temp;
        temp = exp[i];
        exp[i] = exp[exp.length()-1-i];
        exp[exp.length()-1-i] = temp;
    }
    for(int i=0; i<exp.length();i++){ ///Swaps the direction of the parenthesis to make sure the reversed expression obtained is still well-formed
        if(exp[i]=='('){
            exp[i]=')';
        } else if(exp[i]==')'){
            exp[i]='(';
        }
    }
    
    return exp;
}

///Declaring the precedence of operators by which conversions take place
bool CheckPrecedence(char incoming,char stack_top){ 
    switch(incoming){ /// Switch statement used to specify the precedence of the operators with other operators and even for the operator itself should it occur again later
        case '(':
            return true;
            break;
        case '~':
            if(stack_top=='+'||stack_top=='*'||stack_top=='>'){
                return true;
            }else{
                return false;
            }
            break;
        case '*':
            if(stack_top=='+'||stack_top=='>'){
                return true;
            }
            else{
                return false;
            }
            break;
        case '+':
            if(stack_top=='>'){
                return true;
            }
            else{
                return false;
            }
            break;
        case '>':
        case ')':
            return false;
            break;
        default: 
            return false;
    }
}
///Removing parentheses as they lose significance in infix,prefix,postfix forms
std::string RemoveParentheses(std::string exp){ 
    std::string return_str;
    for(int i=0;i<exp.length();i++){
        if(exp[i]=='('||exp[i]==')'){
            
        }else{
            return_str+=exp[i];
        }
    }
    return return_str;
}

/// Converting the reverse string to Postfix form using the stack class created
///
/// The function loops through the length of the string and adds operators to the stack. While adding the operators to the stack it checks the operator already on top of the stack and compares their precedence.
///If the incoming operator has a higher precendence then it will be added to the stack otherwise the operator currently at the top of the stack will be popped and added to the return string. When operands are encountered they are directly added to the string 
///
std::string PostfixConverter(std::string reversed){
    std::string return_str;
    Stack<char> S; ///Declaring a stack of characters to aid in converting the reversed expression to its postfix formP
    for(int i=0;i<reversed.length();i++){
        bool IsOperator = reversed[i]=='('||reversed[i]=='*'||reversed[i]=='+'||reversed[i]=='~'||reversed[i]==')'||reversed[i]=='>';
            if(IsOperator){
            if(S.empty()){
                S.push(reversed[i]);
            }else{
                if(CheckPrecedence(reversed[i],S.top())){
                    S.push(reversed[i]);   
                }
                else{
                    return_str+=S.top();
                    S.pop();
                    // S.push(reversed[i]);
                    i--;
                }

            }
        }else{
            return_str += reversed[i]; 
        }
   
        }
         while(!S.empty()){
            return_str+= S.top();
            S.pop();
            
        }
        return_str = RemoveParentheses(return_str);
        return_str = ReversedExpression(return_str);

    return return_str;
           
}
/// Converting the postfix expression into prefix form of the original string by reversing the final string obtained from previous function
std::string PrefixConverter(std::string exp){
    std::string reverse_exp = ReversedExpression(exp);
    std::string postfix = PostfixConverter(reverse_exp);
    return postfix;  
}


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
}


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


//                   Task 4: Compute the height of the binary tree

///Recursive function that traverses the tree and compares if the left branch is taller or right branch is taller and returns the max value of the two and adds 1
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
char atoms[26] ={0};

///Array that contains the corresponding truth values for the propositional atoms at the same index in array atoms. 
bool truth_values[26] = {0};

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

/// A function that combines all the previous functions to run the tasks in the required order
void LogicAssignment(){
std::string name;
    std::cout<< "This test was done on an AMD Ryzen 7 5800HS CPU and NVIDIA GTX1650 GPU"<<std::endl;
    std::cout<< "Enter a propositional statement in infix form: "<<std::endl;
    std::getline(std::cin,name);

    //using chrono to calculate execution time
    // auto start = std::chrono::high_resolution_clock::now(); 
  
    std::string prefix = PrefixConverter(name);
    std::cout<< "The prefix form of the statement is: "<< prefix << std::endl;
  
    AddToBinaryTree(prefix);

    std::cout<< "The in-order traversal of the parse tree leads to the equation: ";
    ParseBinaryTree(root);  

    std::cout<< "\nThe height of the parse tree is equal to: "<< FindTreeHeight(root)<<std::endl;
    
    FindPropositionalAtoms(name);
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

/// Main function that runs the LogicAssignment() function
int main(){
    LogicAssignment();  
}