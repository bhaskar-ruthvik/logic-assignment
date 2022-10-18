//including the required header files

#include <iostream>
#include <string>

//                         Task 1: Converting infix expression to prefix expression                               //




template<class T>  // we create a struct node using template T so as to accomodate for linked lists with different data type elements
struct Listnode{
            T data; 
            Listnode* next; //pointer pointing to same struct type
        };

/* Creating a stack class and implementing its functions*/
template<class K>
class Stack{
    private:
        Listnode<K>* head= new Listnode<K>();
    public:
        void push(K c){     //adds a new node at the head of the linked list. Hence the time-complexity is O(1)
            Listnode<K>* temp = new Listnode<K>();
            temp->data = c;
            temp->next = head;
            head = temp;
         
        }
        void pop(){      //removes the node at the head of the linked list. So the time-complexity is O(1)
            Listnode<K>* temp1 = head;
            head = temp1->next;
            
        }
        K top(){   //returns the top of the stack which is the head of the linked list. Time-complexity is O(1)
            return head->data;
        }
        bool empty(){  //checks if the stack is empty and returns a bool. Time-complexity is O(1)
            if((head->data)==0){
                return true;
            }
            else{
                return false;
            }
            
        }
};

/* Step 1. Reversing the string that was input by the user */
std::string ReversedExpression(std::string exp){
    
    for(int i=0;i<exp.length()/2;i++){
        char temp;
        temp = exp[i];
        exp[i] = exp[exp.length()-1-i];
        exp[exp.length()-1-i] = temp;
    }
    for(int i=0; i<exp.length();i++){
        if(exp[i]=='('){
            exp[i]=')';
        } else if(exp[i]==')'){
            exp[i]='(';
        }
    }
    
    return exp;
}


bool CheckPrecedence(char incoming,char stack_top){ //declaring the precedence of operators by which conversions take place
    switch(incoming){
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
std::string RemoveParentheses(std::string exp){ //removing parenthesis as they lose significance in infix,prefix,postfix forms
    std::string return_str;
    for(int i=0;i<exp.length();i++){
        if(exp[i]=='('||exp[i]==')'){
            
        }else{
            return_str+=exp[i];
        }
    }
    return return_str;
}

/* Step2. Converting the reverse string to Postfix form using the stack class created */
std::string PostfixConverter(std::string reversed){
    std::string return_str;
    Stack<char> S; 
    for(int i=0;i<reversed.length();i++){
        bool isExp = reversed[i]=='('||reversed[i]=='*'||reversed[i]=='+'||reversed[i]=='~'||reversed[i]==')'||reversed[i]=='>';
            if(isExp){
            if(S.empty()){
                S.push(reversed[i]);
            }else{
                if(CheckPrecedence(reversed[i],S.top())){
                    S.push(reversed[i]);   
                }
                else{
                    return_str+=S.top();
                    S.pop();
                    S.push(reversed[i]);
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
/* Step3. Converting the postfix expression into prefix form of the original string by reversing the final string obtained from previous function*/
std::string PrefixConverter(std::string exp){
    std::string reverse_exp = ReversedExpression(exp);
    std::string postfix = PostfixConverter(reverse_exp);
    return postfix;  
}

//                     Task 2                         //
struct Node{
    Node* left;
    char data;
    Node* right;
};
struct Node* root;

bool isExp(char c){
    return c=='('||c=='*'||c=='+'||c=='~'||c==')'||c=='>';
}

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
       
        if(S.top()->left==NULL&&S.top()->right==NULL&&isExp(S.top()->data)&&S.top()->data!='~'){
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
        else if((S.top()->left!=NULL && S.top()->right!=NULL)||!isExp(S.top()->data)){
           
            S.pop();
            i--;

        }


      
    }
    
    
 
     
}

void ParseBinaryTree(Node* rootnode){
    if(rootnode==NULL){
        return;
    }
    ParseBinaryTree(rootnode->left);
    std::cout<< rootnode->data;
    ParseBinaryTree(rootnode->right);


}

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
bool EvaluateNegation(bool prop1){
    return !prop1;
}

bool isDuplicate(std::string str,char c){
    int count = 0;
    for(int i=0;i<str.length();i++){
        if(str[i]==c){
            count++;
        }
    }
    if(count<=1){
    return false;
    } else{
        return true;
    }
    
}
char a[26] ={0};
bool b[26] = {0};
int len = 0;
void FindPropositionalAtoms(std::string str){
    
    for(int i=0; i<str.length();i++){
        if(!isExp(str[i])&& !isDuplicate(str,str[i])){
            a[len++] = str[i]; 
        }
    }
    std::cout<< "The propositional expression contains the following propositional atoms: "<<std::endl;
     for(int i=0; i<len;i++){
        std::cout << a[i] << ' ';
     }
  
  std::cout<< std::endl;
  

}
void AssignTruthValues(){
    
    for(int i=0;i<len;i++){
        std::cout<< a[i] << " = ";
            bool truth_value;
            std::cin>> truth_value;
            b[i] = truth_value;
    }
    std::cout<< "The following are the truth values provided"<<std::endl;
    std::cout<< "\tAtom\tTruthValue\n";
    for(int i=0;i<len;i++){
        std::cout << '\t' << a[i] << '\t' << b[i] << '\n';
    }

    std::cout<< std::endl;
    
}
bool valueAt(char c){
    for(int i=0;i<len;i++){
        if(a[i]==c){
            return b[i];
        }
    }
    return false;
}
bool ComputeTruthValues(Node* rootnode){
    int i =0;
    if(!isExp(rootnode->data)){
        return valueAt(rootnode->data);
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



void LogicAssignment(){
std::string name;
    std::cout<< "Enter a propositional statement in infix form: "<<std::endl;
    std::getline(std::cin,name);
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
    
    
}

int main(){
    LogicAssignment(); 
   
    
}