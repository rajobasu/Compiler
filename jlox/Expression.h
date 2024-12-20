#pragma once

#include "Base.h"
#include "tokens.h"
#include "Utils.h"


class BinaryExpression;
class UnaryExpression;
class GroupingExpression;
class LiteralExpression;

using Expression = std::variant<
        BinaryExpression,
        UnaryExpression,
        GroupingExpression,
        LiteralExpression>;


// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------

class BinaryExpression {
public:
    BinaryExpression(
            std::unique_ptr<Expression> left_,
            std::unique_ptr<Expression> right_,
            Token _operator_
    );
public:
    std::unique_ptr<Expression> left;
    Token _operator;
    std::unique_ptr<Expression> right;
};


// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------


class GroupingExpression {
public:
    explicit GroupingExpression(
            std::unique_ptr<Expression> expression_
    );
public:
    std::unique_ptr<Expression> expression;
};

// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------


class UnaryExpression {
public:
    UnaryExpression(Token operator_, std::unique_ptr<Expression> expression_);
public:
    Token _operator;
    std::unique_ptr<Expression> expression;
};

// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------


class LiteralExpression {
public:
    explicit LiteralExpression(Literal value_) : value(std::move(value_)) {}
public:
    Literal value;
};





template <typename ExpressionSubTypeT, typename... Args>
inline std::unique_ptr<Expression> make_expression(Args&&... args) {
    return make_variant_upointer<Expression, ExpressionSubTypeT>(std::forward<Args>(args)...);
}



