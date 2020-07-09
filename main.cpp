#include <iostream>


#include "creationals/builder.h"


int main (int argc, char *argv[]) { 
    
    std::cout << "Desing Pattern Repo" << std::endl;

    Builder b(10);

    std::cout << b.getTemperature();

    return 0; 
}