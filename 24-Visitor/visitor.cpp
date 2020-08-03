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