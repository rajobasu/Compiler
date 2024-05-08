//
// Created by Rajarshi on 19/4/24.
//
#include <string>
#include <iostream>
#include <utility>

#pragma once

enum class TokenType {
    // Single-character tokens.
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

    // One or two character tokens.
    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,

    // Literals.
    IDENTIFIER, STRING, NUMBER,

    // Keywords.
    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

    LOX_EOF
};

struct Token {
    Token(TokenType _token_type, std::string&& _lexeme, int _line)
            : token_type(_token_type), lexeme(std::move(_lexeme)), line_number(_line) {}

    Token(TokenType _token_type, std::string& _lexeme, int _line)
            : token_type(_token_type), lexeme(std::move(_lexeme)), line_number(_line) {}

    const TokenType token_type;
    const std::string lexeme;
    const int line_number;
};

std::ostream& operator<<(std::ostream& out, const TokenType& token_type);
std::ostream& operator<<(std::ostream& out, const Token& token);