//
// Created by Rajarshi on 6/11/24.
//

#pragma once

#include "Base.h"
#include "errors.h"
#include "Expression.h"

struct ExpressionPrinter {
    ostream& ostream_ref;
    explicit ExpressionPrinter(ostream& _ostream_ref) : ostream_ref(_ostream_ref) {}

    void operator()(const BinaryExpression &expr) const;
    void operator()(const UnaryExpression &expr) const;
    void operator()(const GroupingExpression &expr) const;
    void operator()(const LiteralExpression &expr) const;
};

class ExpressionEvaluator {
public:
    Literal operator()(const BinaryExpression &expr) const;
    Literal operator()(const UnaryExpression &expr) const;
    Literal operator()(const GroupingExpression &expr) const;
    Literal operator()(const LiteralExpression &expr) const;
public:
    void interpret(const Expression& expr) {
        try {
            Literal value = std::visit(*this, expr);
            cout << value << endl;
        } catch (error_handling::runtime_exception &e) {
            error_handling::runtime_error(e.token, e.reason);
        }
    }
};
