#include <iostream>

#include "00-Intro/openClosed.h"
#include "02-Builder/builder.h"
#include "07-Bridge/bridge.h"
#include "08-Composite/composite.h"
#include "09-Decorator/decorator.h"
#include "12-Proxy/proxy.h"
#include "13-Chain_of_resp/chain.h"
#include "14-Command/command.h"
#include "17-Mediator/mediator.h"
#include "19-NullObject/nullobject.h"
#include "22-Strategy/strategy.h"
#include "23-Template/template.h"
#include "24-Visitor/visitor.h"

int main (int argc, char *argv[]) { 
    
    std::cout << "Desing Pattern Repo" << std::endl;

    // openClosedExample();
    // simpleBuilder();
    // communicatingIntent();
    // groovyExample();
    // compositeExample();     // need to separate classes
    // pimplExample();
    // bridgeExample();
    // creatureExample();
    // groupingObjectExample();
    // neuralExample();
    // decoFirstExample();
    // functionalDecoExample();
    // smartPointerExample();
    // lazyExample();
    // baseChainExample();
    // brokenChainExample();
    // commandExample();
    // compositeCommandExample();
    // commandQuerySeparationExample();
    // mediatorExample();
    // mediatorSignalExample();
    // nullObjectExample();
    // dynamicStrategyExample();
    // staticStrategyExample();
    // templateExample();
    intrusiveExample();
    reflectiveExample();
    return 0; 
}

