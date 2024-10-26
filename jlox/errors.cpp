//
// Created by Rajarshi on 19/4/24.
//

#include <iostream>

#include "errors.h"

namespace error_handling {



    bool hadError = false;

    void error(int line, const string &message) {
        report(line, "", message);
    }

    void error(const Token& token, const string& message) {
        if (token.token_type == TokenType::LOX_EOF) {
            report(token.line_number, " at end", message);
        } else {
            report(token.line_number, " at '" + token.lexeme + "'", message);
        }
    }

    static void report(int line, const string &where, const string &message) {
        cout << "[Line " << line << "]: Error " << where << ": " << message << endl;
        hadError = true;
    }

}