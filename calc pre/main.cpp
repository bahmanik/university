#include <iostream>
#include <string>
#include <stack>
using namespace std;

//function declaratioms
bool is_number(char c);
bool is_operator(char c);
int calc(int x, int y, char c);

int main(){
    string prefix;
    cout<<"inter your equition: ";
    getline(cin ,prefix);
    stack<string> operand;
    for (int i = 0; i < prefix.length(); i++)
    {
        if(is_number(prefix[i])){
            string temp = "";
            temp += prefix[i];
            while (i != prefix.length()-1  && prefix[i+1] != ' ')
            {
                i++;
                temp += prefix[i];
            }
            operand.push(temp);
        }
        else if (is_operator(prefix[i]))
        {
            int x = stoi(operand.top());
            operand.pop();
            int y = stoi(operand.top());
            operand.pop();
            int temp = calc(x, y, prefix[i]);
            operand.push(to_string(temp));
        }
    }
    cout<<operand.top()<<endl;
}

bool is_number(char letter){
    if ( letter >= '0' && letter <= '9')
    {
        return true;
    }
    return false;
}

bool is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int calc(int x, int y, char c){
    if (c == '+')
    {
        return y + x;
    }
    if (c == '-')
    {
        return y - x;
    }
    if (c == '*')
    {
        return y * x;
    }
    if (c == '/')
    {
        return y / x;
    }
    return false;
}