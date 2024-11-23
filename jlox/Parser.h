//
// Created by rajarshi on 24/9/24.
//

#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H

#include "Base.h"
#include "tokens.h"
#include "Expression.h"
#include "errors.h"
#include "Statement.h"

class Parser {
public:
    Parser(vector<Token> tokens_) : tokens(std::move(tokens_)) {}

public:
    std::vector<Statement> parse() {
        std::vector<Statement> statements;
        while(!isAtEnd()) statements.push_back(statement());
        return statements;
    }

private:
    Statement statement();
    Statement print_statement();
    Statement expression_statement();

    std::unique_ptr<Expression> expression();

    std::unique_ptr<Expression> equality();

    std::unique_ptr<Expression> comparison();

    std::unique_ptr<Expression> term();

    std::unique_ptr<Expression> factor();

    std::unique_ptr<Expression> unary();

    std::unique_ptr<Expression> primary();

private:
    [[nodiscard]] const Token &peek() const {
        return tokens[current];
    }

    bool isAtEnd() {
        return peek().token_type == TokenType::LOX_EOF;
    }

    [[nodiscard]] bool checkCurrentTokenType(TokenType tokenType) {
        if (isAtEnd()) return false;
        return peek().token_type == tokenType;
    }

    [[nodiscard]] const Token &previous() const {
        return tokens[current - 1];
    }

    const Token &advanceAndReturn() {
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

    void synchronise();

    error_handling::parse_exception error(const Token &token, const string &message) {
        error_handling::error(token, message);
        throw error_handling::parse_exception();
    }

    void consume_or_throw(TokenType type, const string &message) {
        if (checkCurrentTokenType(type)) advance();
        else throw error(peek(), message);
    }

    template<typename... TokenTypeT>
    bool match(TokenTypeT &&... tokenTypes) {
        bool success = (checkCurrentTokenType(std::forward<decltype(tokenTypes)>(tokenTypes)) || ...);
        if (success) advance();
        return success;
    }

private:
    uint32_t current = 0;
    std::vector<Token> tokens;
};


#endif //COMPILER_PARSER_H
