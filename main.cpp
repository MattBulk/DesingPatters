#include <iostream>

#include "00-Intro/openClosed.h"
#include "02-Builder/builder.h"
#include "07-Bridge/bridge.h"
#include "08-Composite/composite.h"


int main (int argc, char *argv[]) { 
    
    std::cout << "Desing Pattern Repo" << std::endl;

    // openClosedExample();
    // simpleBuilder();
    // communicatingIntent();
    // groovyExample();
    // compositeExample();     // need to separate classes
    pimplExample();
    bridgeExample();
    creatureExample();
    groupingObjectExample();
    neuralExample();
    return 0; 
}