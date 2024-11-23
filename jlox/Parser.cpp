//
// Created by rajarshi on 24/9/24.
//

#include "Parser.h"
#include "Utils.h"

Statement Parser::statement() {
    if (match(TokenType::PRINT)) return print_statement();
    return expression_statement();
}

Statement Parser::print_statement() {
    auto expr = expression();
    consume_or_throw(TokenType::SEMICOLON, "Expect ';' after value.");
    return PrintStatement(std::move(*expr));
}

Statement Parser::expression_statement() {
    auto expr = expression();
    consume_or_throw(TokenType::SEMICOLON, "Expect ';' after value.");
    return ExpressionStatement(std::move(*expr));
}

std::unique_ptr<Expression> Parser::Parser::expression() {
    return equality();
}

std::unique_ptr<Expression> Parser::primary() {
    if (match(TokenType::FALSE)) return make_expression<LiteralExpression>(false);
    if (match(TokenType::TRUE)) return make_expression<LiteralExpression>(true);
    if (match(TokenType::NIL)) return make_expression<LiteralExpression>(nullptr);

    if (match(TokenType::NUMBER, TokenType::STRING)) return make_expression<LiteralExpression>(previous().literal);

    if (match(TokenType::LEFT_PAREN)) {
        auto expr = expression();
        consume_or_throw(TokenType::RIGHT_PAREN, "Missing corresponding ).");
        return make_expression<GroupingExpression>(std::move(expr));
    }

    throw error(peek(), "Expected Expression");
}

std::unique_ptr<Expression> Parser::unary() {
    if (match(TokenType::BANG, TokenType::MINUS)) {
        auto operator_ = previous();
        auto right = unary();
        return make_expression<UnaryExpression>(operator_, std::move(right));
    }

    return primary();
}

std::unique_ptr<Expression> Parser::factor() {
    std::unique_ptr<Expression> expr = unary();

    while(match(TokenType::STAR, TokenType::SLASH)) {
        auto operator_ = previous();
        auto right = unary();
        expr = make_expression<BinaryExpression>(std::move(expr), std::move(right), operator_);
    }

    return expr;
}

std::unique_ptr<Expression> Parser::term() {
    std::unique_ptr<Expression> expr = factor();

    while(match(TokenType::MINUS, TokenType::PLUS)) {
        auto operator_ = previous();
        auto right = factor();
        expr = make_expression<BinaryExpression>(std::move(expr), std::move(right), operator_);
    }

    return expr;

}

std::unique_ptr<Expression> Parser::comparison() {
    std::unique_ptr<Expression> expr = term();

    while(match(TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL)) {
        auto operator_ = previous();
        auto right = term();
        expr = make_expression<BinaryExpression>(std::move(expr), std::move(right), operator_);
    }

    return expr;
}

std::unique_ptr<Expression> Parser::equality() {
    std::unique_ptr<Expression> expr = comparison();

    while(match(TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL)) {
        auto operator_ = previous();
        auto right = comparison();
        expr = make_expression<BinaryExpression>(std::move(expr), std::move(right), operator_);
    }

    return expr;
}

void Parser::synchronise() {
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
            default: break;
        }
    }

    advance();
}