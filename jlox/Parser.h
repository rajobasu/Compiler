//
// Created by rajarshi on 24/9/24.
//

#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H

#include "Base.h"
#include "tokens.h"
#include "Expression.h"
#include "errors.h"

class Parser {
public:
    Parser(vector<Token> tokens_): tokens(std::move(tokens_)) {}
public:
    unique_ptr<Expression> parse() {
        try {
            return expression();
        } catch (const error_handling::parse_exception& e) {
            return nullptr;
        }
    }
private:
    std::unique_ptr<Expression> expression();
    std::unique_ptr<Expression> equality();
    std::unique_ptr<Expression> comparison();
    std::unique_ptr<Expression> term();
    std::unique_ptr<Expression> factor();
    std::unique_ptr<Expression> unary();
    std::unique_ptr<Expression> primary();
private:
    [[nodiscard]] const Token& peek() const {
        return tokens[current];
    }

    bool isAtEnd() {
        return peek().token_type == TokenType::LOX_EOF;
    }

    [[nodiscard]] bool checkCurrentTokenType(TokenType tokenType) {
        if (isAtEnd()) return false;
        return peek().token_type == tokenType;
    }

    [[nodiscard]] const Token& previous() const {
        return tokens[current - 1];
    }

    const Token& advanceAndReturn() {
        if (!isAtEnd())current++;
        return previous();
    }

    void advance() {
        if (!isAtEnd())current++;
    }

    bool consume(TokenType type) {
        if (!checkCurrentTokenType(type)) return false;
        advance();
        return true;
    }

    void synchronise() {
        advance();

        while(!isAtEnd()) {
            if (previous().token_type == TokenType::LOX_EOF) return;

            switch (peek().token_type) {
                case TokenType::CLASS:
                case TokenType::FUN:
                case TokenType::FOR:
                case TokenType::WHILE:
                case TokenType::IF:
                case TokenType::RETURN:
                case TokenType::PRINT:
                case TokenType::VAR:
                    return;
                default:
            }
        }

        advance();
    }

    error_handling::parse_exception error(const Token& token, const string& message) {
        error_handling::error(token, message);
        throw error_handling::parse_exception();
    }

    void consumeOrThrow(TokenType type, const string& message) {
        if (checkCurrentTokenType(type)) advance();

        throw error(peek(), message);
    }

    template <typename... TokenTypeT>
    bool match(TokenTypeT&&... tokenTypes) {
        return ((checkCurrentTokenType(std::forward<decltype(tokenTypes)>(tokenTypes)) && (advance(), true)) || ...);
    }
private:
    uint32_t current = 0;
    std::vector<Token> tokens;
};


#endif //COMPILER_PARSER_H
