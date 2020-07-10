#ifndef COMMONS_H
#define COMMONS_H

#include <iostream>
#include <string>

template<class T, class U>
void print(const T &arg1, const U &arg2) {
    std::cout << arg1 << arg2 << std::endl;
}

#endif