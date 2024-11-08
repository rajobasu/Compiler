cmake_minimum_required(VERSION 3.26)
project(Compiler)

set(CMAKE_CXX_STANDARD 23)
add_executable(jlox jlox/main.cpp
        jlox/errors.cpp
        jlox/errors.h
        jlox/tokens.cpp
        jlox/tokens.h
        jlox/scanner.cpp
        jlox/scanner.h
        jlox/Expression.h
        jlox/Parser.cpp
        jlox/Parser.h
        jlox/Base.h
        jlox/VisitorBase.h
        jlox/ExpressionVisitors.h
        jlox/ExpressionVisitors.cpp
)
