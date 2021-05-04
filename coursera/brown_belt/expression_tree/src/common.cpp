#include "Common.h"

class Number : public Expression
{
public:
    Number(const int value)
        : value_{value}
    {
    }
    int Evaluate() const override
    {
        return value_;
    }
    std::string ToString() const override
    {
        return std::to_string(value_);
    }

private:
    int value_;
};

class BinaryPredicate : public Expression
{
public:
    BinaryPredicate(ExpressionPtr left, ExpressionPtr right)
        : left_{std::move(left)}, right_{std::move(right)}
    {
    }
    int Evaluate() const final
    {
        return EvaluateOnValues(left_->Evaluate(), right_->Evaluate());
    }
    std::string ToString() const final
    {
        std::string result =
            "(" + left_->ToString() + ")" + GetSymbol() + "(" + right_->ToString() + ")";
        return result;
    }

private:
    ExpressionPtr left_;
    ExpressionPtr right_;

    virtual char GetSymbol() const = 0;
    virtual int EvaluateOnValues(int l, int r) const = 0;
};

class Plus : public BinaryPredicate
{
public:
    Plus(ExpressionPtr left, ExpressionPtr right)
        : BinaryPredicate(std::move(left), std::move(right))
    {
    }

private:
    char GetSymbol() const override
    {
        return '+';
    }
    int EvaluateOnValues(int lhs, int rhs) const override
    {
        return lhs + rhs;
    }
};

class Mult : public BinaryPredicate
{
public:
    Mult(ExpressionPtr left, ExpressionPtr right)
        : BinaryPredicate(std::move(left), std::move(right))
    {
    }

private:
    char GetSymbol() const override
    {
        return '*';
    }
    int EvaluateOnValues(int lhs, int rhs) const override
    {
        return lhs * rhs;
    }
};

ExpressionPtr Value(int value)
{
    return std::make_unique<Number>(value);
}

ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right)
{
    return std::make_unique<Plus>(std::move(left), std::move(right));
}

ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right)
{
    return std::make_unique<Mult>(std::move(left), std::move(right));
}