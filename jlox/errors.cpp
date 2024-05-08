//
// Created by Rajarshi on 19/4/24.
//

#include <iostream>

#include "errors.h"


bool hadError = false;
void error(int line, const string& message) {
    report(line, "", message);
}

static void report(int line, const string& where, const string& message) {
    cout << "[Line " << line << "]: Error " << where << ": " << message << endl;
    hadError = true;
}