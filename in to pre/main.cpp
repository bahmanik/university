#include <iostream>
#include <string>
#include "stack.hpp"
using namespace std;

//function declaratioms
bool is_operand(char);
string rev_string(string);
int precedence(char op);
bool isOperator(char c);

int main(){

    string prefix;
    string infix;
    cout<<"inter your equition: ";
    cin>>infix;
    stack operators(infix.length());
    
    // reversing string and adding it to stack
    infix = rev_string(infix);

    // turning 
    for (char c : infix)
    {
        // check to see if its oprand
        if (is_operand(c))
        {
            prefix += c;
        }
        else if (c == ')')
        {
            operators.push(c);
        }
        else if (c == '(')
        {
            while (!operators.is_empty() && operators.top_char() != ')')
            {
                prefix += operators.top_char();
                operators.pop();
            }
            // Pop the closing parenthesis
            operators.pop();
        }
        else if (isOperator(c)) {
            // Pop operators with higher or equal precedence and add to prefix
            while (!operators.is_empty() && precedence(operators.top_char()) >= precedence(c)) {
                prefix += operators.top_char();
                operators.pop();
            }
            // Push current operator to stack
            operators.push(c);
        }
    }
    
    // Pop remaining operators and add to prefix
    while (!operators.is_empty()) {
        prefix += operators.top_char();
        operators.pop();
    }

    // Reverse the prefix string to get the final result
    prefix = rev_string(prefix); 
    cout<<prefix;
}

bool is_operand(char letter){
    if ( ( letter >= 'a' && letter <= 'z' ) || ( letter >= 'A' && letter <= 'Z') )
    {
        return true;
    }
    return false;
}

string rev_string(string STR){
    stack Stack(STR.length());
    
    for (char i : STR)
    {
        Stack.push(i);
    }
    STR = "";
    int num = Stack.top;
    for (int i = 0; i <= num; i++)
    {
        STR += Stack.pop();
    }
    return STR;
}
int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}