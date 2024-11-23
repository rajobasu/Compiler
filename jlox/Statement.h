#pragma once

#include "Base.h"
#include "Utils.h"
#include "Expression.h"

class ExpressionStatement;
class PrintStatement;

using Statement = std::variant<ExpressionStatement, PrintStatement>;

class ExpressionStatement {
public:
    explicit ExpressionStatement(Expression expr_);
public:
    Expression expr;
};

class PrintStatement {
public:
    explicit PrintStatement(Expression expr_);
public:
    Expression expr;
};