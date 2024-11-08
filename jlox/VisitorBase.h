//
// Created by Rajarshi on 6/11/24.
//

#pragma once

#include "Base.h"

struct VisitorBase;

struct VisitableBase {
    virtual void acceptVisitor(const VisitorBase&) const = 0;
    virtual ~VisitableBase() = default;
};

struct VisitorBase {
    virtual void visit(const VisitableBase&) const {
        cout << "oh no" << endl;
    };
    virtual ~VisitorBase() = default;
};
