//
// Created by Rajarshi on 19/4/24.
//
#include "Base.h"
#include "tokens.h"

#pragma once

using namespace std;

namespace error_handling {
    class parse_exception : std::exception {};

    extern bool hadError;

    void error(int line, const string &message);
    void error(const Token&, const string&);
    static void report(int line, const string &where, const string &message);
}