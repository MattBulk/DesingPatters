#ifndef REFLECTIVE_H
#define REFLECTIVE_H

#include "../commons.h"
namespace Reflective
{

    class Expression
    {
    private:
        /* data */
    public:
        Expression(/* args */) {}
        virtual ~Expression() = default;
    };

    class DoubleExpression : public Expression
    {
    public:
        /* data */
        double value;

    public:
        DoubleExpression(double value) : value{value} {}
        ~DoubleExpression() {}
    };

    class AdditionExpression : public Expression
    {
    public:
        /* data */
        Expression *left, *right;

    public:
        AdditionExpression(Expression *const left, Expression *const right) : left{left}, right{right} {}
        ~AdditionExpression() {}
    };

    class ExpressionPrinter
    {
    private:
        /* data */
        std::ostringstream oss;
    public:
        ExpressionPrinter(/* args */) {}
        ~ExpressionPrinter() {}

        void print(Expression *e)
        {
            if (auto de = dynamic_cast<DoubleExpression *>(e))
            {
                oss << de->value;
            }
            else if (auto ae = dynamic_cast<AdditionExpression *>(e))
            {
                oss << "(";
                print(ae->left);
                oss << "+";
                print(ae->right);
                oss << ")";
            }
        }

        std::string toString() const {return oss.str(); }
    };
} // namespace Reflective
#endif