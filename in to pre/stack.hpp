#include <iostream>
class stack
{
public:
    int top;
    int max_size;
    char *STK;
    stack(int);
    bool is_empty();
    bool is_full();
    char pop();
    bool push(char);
    void show_STK();
    int top_char();
};

stack::stack(int a)
{
    top = -1;
    max_size = a;
    STK = new char[max_size];
}

bool stack::is_full(){
    if (top >= max_size)
    {
        return true;
    }
    return false;
}

bool stack::is_empty(){
    if (top < 0)
    {
        return true;
    }
    return false;
}

char stack::pop() {
    if(is_full()){
        return false;
    }
    else {
        return STK[top--];
    }
}

bool stack::push(char temp){
    if (is_full())
    {
        return false;
    }
    ++top;
    STK[top] = temp;
    return true;
}

void stack::show_STK(){
    for (int i = top; i > -1; i--)
    {
        std::cout<<STK[i]<<" \n";
    }
}

int stack::top_char(){
    return STK[top];
}