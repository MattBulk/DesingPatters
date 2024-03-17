#include <iostream>

#include "chap02/stack.h"
#include "chap02/mixboxc2.h"
#include "chap02/myarray.h"
#include "chap03/mixboxc3.h"
#include "chap03/gameCharacter.h"
#include "chap03/multipleHeritage.h"
#include "chap04/openClose.h"
#include "chap05/exceptions.h"
#include "chap06/mixbox6.h"
#include "chap07/mixbox7.h"
#include "chap08/mixbox8.h"
#include "commons.h"

#include "adapter/adapter.h"
#include "observer/observer.h"
#include "observer/mvc.h"
#include "factory/factory.h"
#include "factory/abfactory.h"

void arrayExample();
void stackExample();

int main (int argc, char *argv[]) { 
    
    std::cout << "Bertini OOP Book" << std::endl;

    // CHAPTER - 02
    // arrayExample();
    // stackExample();
    // xExample();
    // explicitExample();
    // staticExample();
    // friendExample();
    // constExample();
    // deepAndShallowExample();

    // CHAPTER - 03
    // substitutionExample();
    // bindingExample();
    // virtualExample();
    // deleteExample();
    // covariantExample();
    // hidingExample();
    // abstractExample();
    // gameCharacter();     // throw error
    // conversionExample();
    // dynamicCastExample();
    // mammalExample();
    // diamondExample();
    // solvingExample();
    // exceptionExample();
    // templateExample();
    // myPairExample();
    // functorExample();
    // lambdaExample();
    // raiiExample();
    // uniquePtrExample();
    // sharedPtrExample();
    // weakPtrExample();
    // autoExample();
    // decltypeExample();
    // moveExample();
    // lambda2Example();
    // functionExample();
    // tupleExample();

    // adapterExample();
    // observerPullExample();
    // observerPushExample();
    // observerMultiExample();
    // mvcExample();
    // factoryExample();
    abFactoryExample();

    int a[7] = {3, 4, 3, 2, 1, 6, 5};

    int *b = &a[0] + sizeof(a)/sizeof(a[0]); // calculates the address and the step to the next item.

    return 0; 
}

void arrayExample() {
    MYArray A(5), B(5);
    A[0] = 10;
    B[0] = 5;
    int res = (A == B) ? 1 : 0;
    print("A == B ", res);

    MYArray C(A);
    print("copy constructor ", C[0]);

    MYArray D(20);
    D = A;
    print("equal operator ", D[0]);
}

void stackExample() {

    Stack s;
    s.init(3);

    print("push 10 ",s.push(10));
    print("push 20 ",s.push(20));
    print("push 30 ",s.push(30));
    print("push 40 ",s.push(40));

    int result;
    print("pop ", s.pop(result));
    print("result ", result);
    print("pop ", s.pop(result));
    print("result ", result);
    print("pop ", s.pop(result));
    print("result ", result);
    print("pop ", s.pop(result));
    print("result ", result);

    Stack *pStack;
    pStack = new Stack(10);
    pStack->push(22);
    print("pop dynamic ", pStack->pop(result));
    print("result dynamic ", result);
    delete pStack;
}