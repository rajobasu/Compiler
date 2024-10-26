//
// Created by rajarshi on 24/9/24.
//

#include "Parser.h"

std::unique_ptr<Expression> Parser::Parser::expression() {
    return equality();
}

std::unique_ptr<Expression> Parser::primary() {
    if (match(TokenType::FALSE)) return make_unique<LiteralExpression>(false);
    if (match(TokenType::TRUE)) return make_unique<LiteralExpression>(true);
    if (match(TokenType::NIL)) return make_unique<LiteralExpression>(nullptr);

    if (match(TokenType::NUMBER, TokenType::STRING)) return make_unique<LiteralExpression>(previous().literal);

    if (match(TokenType::LEFT_PAREN)) {
        auto expr = expression();
        consumeOrThrow(TokenType::RIGHT_PAREN, "Missing corresponding ).");
        return make_unique<GroupingExpression>(std::move(expr));
    }

    throw error(peek(), "Expected Expression");
}

std::unique_ptr<Expression> Parser::unary() {
    if (match(TokenType::BANG, TokenType::MINUS)) {
        auto operator_ = previous();
        auto right = unary();
        return make_unique<UnaryExpression>(operator_, std::move(right));
    }

    return primary();
}

std::unique_ptr<Expression> Parser::factor() {
    std::unique_ptr<Expression> expr = unary();

    while(match(TokenType::STAR, TokenType::SLASH)) {
        auto operator_ = previous();
        auto right = unary();
        expr = make_unique<BinaryExpression>(std::move(expr), std::move(right), operator_);
    }

    return expr;
}

std::unique_ptr<Expression> Parser::term() {
    std::unique_ptr<Expression> expr = factor();

    while(match(TokenType::MINUS, TokenType::PLUS)) {
        auto operator_ = previous();
        auto right = factor();
        expr = make_unique<BinaryExpression>(std::move(expr), std::move(right), operator_);
    }

    return expr;

}

std::unique_ptr<Expression> Parser::comparison() {
    std::unique_ptr<Expression> expr = term();

    while(match(TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL)) {
        auto operator_ = previous();
        auto right = term();
        expr = make_unique<BinaryExpression>(std::move(expr), std::move(right), operator_);
    }

    return expr;
}

std::unique_ptr<Expression> Parser::equality() {
    std::unique_ptr<Expression> expr = comparison();

    while(match(TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL)) {
        auto operator_ = previous();
        auto right = comparison();
        expr = make_unique<BinaryExpression>(std::move(expr), std::move(right), operator_);
    }

    return expr;
}