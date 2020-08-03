#include "visitor.h"

void intrusiveExample()
{ 
    auto e = new Intrusive::AdditionExpression{
        new Intrusive::DoubleExpression{1},
        new Intrusive::AdditionExpression{
            new Intrusive::DoubleExpression{2},
            new Intrusive::DoubleExpression{3}}};
    
    std::ostringstream oss;
    e->print(oss);
    std::cout << oss.str() << std::endl; // prints (1+(2+3))
}

void reflectiveExample() {
    auto e = new Reflective::AdditionExpression{
        new Reflective::DoubleExpression{1},
        new Reflective::AdditionExpression{
            new Reflective::DoubleExpression{2},
            new Reflective::DoubleExpression{3}}};
    
    Reflective::ExpressionPrinter ep;
    ep.print(e);
    std::cout << ep.toString() << std::endl; // prints (1+(2+3))
}