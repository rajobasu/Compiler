#pragma once

#include "Base.h"
#include <memory>
#include <utility>
#include "tokens.h"
#include "VisitorBase.h"





struct Expression : public VisitableBase{
    virtual void acceptVisitor(const VisitorBase&) const = 0;
    virtual ~Expression() = default;
};


// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------

class BinaryExpression : public Expression {
public:
    BinaryExpression(
            std::unique_ptr<Expression> left_,
            std::unique_ptr<Expression> right_,
            Token _operator_
    ) : left(std::move(left_)),
        right(std::move(right_)),
        _operator(std::move(_operator_)) {};
public:
    void acceptVisitor(const VisitorBase &visitor) const override {
        visitor.visit(*this);
    }
public:
    std::unique_ptr<Expression> left;
    Token _operator;
    std::unique_ptr<Expression> right;
};

// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------


class GroupingExpression : public Expression {
public:
    explicit GroupingExpression(
            std::unique_ptr<Expression> expression_
    ) : expression(std::move(expression_)) {}
public:
    void acceptVisitor(const VisitorBase &visitor) const override {
        visitor.visit(*this);
    }
public:
    std::unique_ptr<Expression> expression;
};

// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------


class UnaryExpression : public Expression {
public:
    UnaryExpression(Token operator_, std::unique_ptr<Expression> expression_) : _operator(std::move(operator_)),
                                                                                expression(std::move(expression_)) {}
public:
    void acceptVisitor(const VisitorBase &visitor) const override {
        visitor.visit(*this);
    }
public:
    Token _operator;
    std::unique_ptr<Expression> expression;
};

// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------


class LiteralExpression : public Expression {
public:
    explicit LiteralExpression(Literal value_) : value(std::move(value_)) {}
public:
    void acceptVisitor(const VisitorBase &visitor) const override {
        visitor.visit(*this);
    }
public:
    Literal value;
};