//
// Created by Rajarshi on 23/11/24.
//

#include "Expression.h"


BinaryExpression::BinaryExpression(
        std::unique_ptr<Expression> left_,
        std::unique_ptr<Expression> right_,
        Token _operator_) : left(std::move(left_)), right(std::move(right_)), _operator(std::move(_operator_)) {}


GroupingExpression::GroupingExpression(std::unique_ptr<Expression> expression_) : expression(std::move(expression_)) {}

UnaryExpression::UnaryExpression(Token operator_, std::unique_ptr<Expression> expression_) :
    _operator(std::move(operator_)), expression(std::move(expression_)) {}
