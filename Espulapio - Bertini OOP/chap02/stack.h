#ifndef STACK_H
#define STACK_H

class Stack {

public:
    Stack();
    ~Stack();

    Stack(int s);

    bool push(int value);

    bool pop(int &value);

    void init(int size);

private:
    int TOS;

    int *buffer;

    int size;
};
#endif