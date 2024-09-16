//
// Created by Rajarshi on 19/4/24.
//
#include <string>
#include <iostream>
#include <utility>
#include <unordered_map>
#include <variant>

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

const std::unordered_map<std::string, TokenType> KEYWORD_LIST = {
    {"and",    TokenType::AND},
    {"class",  TokenType::CLASS},
    {"else",   TokenType::ELSE},
    {"false",  TokenType::FALSE},
    {"for",    TokenType::FOR},
    {"fun",    TokenType::FUN},
    {"if",     TokenType::IF},
    {"nil",    TokenType::NIL},
    {"or",     TokenType::OR},
    {"print",  TokenType::PRINT},
    {"return", TokenType::RETURN},
    {"super",  TokenType::SUPER},
    {"this",   TokenType::THIS},
    {"true",   TokenType::TRUE},
    {"var",    TokenType::VAR},
    {"while",  TokenType::WHILE}
};


using Literal = std::variant<std::monostate, int, double, std::string>;

template<typename T>
concept LexemeType = std::convertible_to<T, std::string>;

struct Token {
    template<LexemeType L>
    Token(TokenType _token_type, L &&_lexeme, int _line)
            : token_type(_token_type), lexeme(std::forward<L>(_lexeme)), line_number(_line) {}

    template<LexemeType L>
    Token(TokenType _token_type, L &&_lexeme, Literal &&literal, int _line)
            : token_type(_token_type), lexeme(std::forward<L>(_lexeme)), literal(std::forward<Literal>(literal)),
              line_number(_line) {}

    const TokenType token_type;
    const std::string lexeme;
    const Literal literal;
    const int line_number;
};

std::ostream &operator<<(std::ostream &out, const TokenType &token_type);

std::ostream &operator<<(std::ostream &out, const Token &token);