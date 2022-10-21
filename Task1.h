#include <iostream>
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
