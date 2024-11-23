//
// Created by rajarshi on 23/11/24.
//

#include "Statement.h"

ExpressionStatement::ExpressionStatement(Expression expr_): expr(std::move(expr_)) {}
PrintStatement::PrintStatement(Expression expr_): expr(std::move(expr_)) {}