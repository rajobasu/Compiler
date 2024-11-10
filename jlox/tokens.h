//
// Created by Rajarshi on 19/4/24.
//
#include "Base.h"
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


using Literal = std::variant<std::monostate, bool, nullptr_t, double, std::string>;

template <typename T>
constexpr std::string get_literal_type_as_string();

template <>
constexpr std::string get_literal_type_as_string<double>() {
    return "double";
}

template <>
constexpr std::string get_literal_type_as_string<std::string>() {
    return "string";
}

template <>
constexpr std::string get_literal_type_as_string<nullptr_t>() {
    return "nil";
}

template <>
constexpr std::string get_literal_type_as_string<bool>() {
    return "bool";
}

template <>
constexpr std::string get_literal_type_as_string<std::monostate>() {
    return "[Empty Literal]";
}






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

std::ostream& operator<<(std::ostream& out, const std::monostate&);
std::ostream& operator<<(std::ostream &out, const TokenType&);
std::ostream& operator<<(std::ostream& out, const Literal&);
std::ostream& operator<<(std::ostream &out, const Token&);