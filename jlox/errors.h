//
// Created by Rajarshi on 19/4/24.
//
#include <utility>

#include "Base.h"
#include "tokens.h"

#pragma once

using namespace std;

namespace error_handling {
    class parse_exception : std::exception {
    };

    struct runtime_exception : std::exception {
        runtime_exception(Token _token, string _reason) : token(std::move(_token)), reason(std::move(_reason)) {}
        const Token token;
        const string reason;
    };

    extern bool hadError;
    extern bool hadRuntimeError;

    void error(int line, const string &message);

    void error(const Token &, const string &);

    void runtime_error(const Token &, const string &);

    static void report(int line, const string &where, const string &message);
}