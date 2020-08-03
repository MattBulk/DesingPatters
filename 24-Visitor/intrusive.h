#ifndef INTRUSIVE_H
#define INTRUSIVE_H

#include "../commons.h"
namespace Intrusive
{

    class Expression
    {
    private:
        /* data */
    public:
        Expression(/* args */) {}
        ~Expression() {}

        virtual void print(std::ostringstream &oss) = 0;
    };

    class DoubleExpression : public Expression
    {
    public:
        /* data */
        double value;

    public:
        DoubleExpression(double value) : value{value} {}
        ~DoubleExpression() {}

        void print(std::ostringstream &oss)
        {
            oss << value;
        }
    };

    class AdditionExpression : public Expression
    {
    public:
        /* data */
        Expression *left, *right;

    public:
        AdditionExpression(Expression *const left, Expression *const right) : left{left}, right{right} {}
        ~AdditionExpression() {}

        void print(std::ostringstream &oss)
        {
            oss << "(";
            left->print(oss);
            oss << "+";
            right->print(oss);
            oss << ")";
        }
    };
} // namespace Intrusive

#endif