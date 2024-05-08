//
// Created by Rajarshi on 19/4/24.
//
#include <string>

#pragma once

using namespace std;

extern bool hadError;

void error(int line, const string& message);
static void report(int line, const string& where,const string& message);
