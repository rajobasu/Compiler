//
// Created by Rajarshi on 6/11/24.
//

#pragma once

#include "Base.h"
#include "VisitorBase.h"
#include "Expression.h"

class ExpressionVisitor : public VisitorBase {
public:
    virtual void visit(const BinaryExpression&) const = 0;
    virtual void visit(const GroupingExpression&) const = 0;
    virtual void visit(const UnaryExpression&) const = 0;
    virtual void visit(const LiteralExpression&) const = 0;
};

class ExpressionPrinter : public ExpressionVisitor {
private:
    ostream& ostream_ref;
public:
    ExpressionPrinter(ostream& _ostream_ref) : ostream_ref(_ostream_ref) {}
public:
    void visit(const BinaryExpression&) const override;
    void visit(const GroupingExpression&) const override;
    void visit(const UnaryExpression&) const override;
    void visit(const LiteralExpression&) const override;

    ~ExpressionPrinter() {
        ostream_ref << endl;
    }
};
