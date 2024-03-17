#include "stack.h"

Stack::Stack() {
    
}

Stack::~Stack() {
    delete[] buffer;
}

Stack::Stack(int s) : TOS(0), size(s), buffer(new int[s]) {}

void Stack::init(int size) {
    this->TOS = -1;
    this->size = size;
    this->buffer = new int[size];
}

bool Stack::push(int value) {
    if(this->TOS == this->size-1)
        return(false);
    TOS++;
    this->buffer[TOS] = value;
    
    return(true);
}

bool Stack::pop(int &value) {
    if(this->TOS == -1)
        return(false);
    value = this->buffer[this->TOS];
    this->TOS--;
    return(true);
     
}