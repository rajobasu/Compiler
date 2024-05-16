//
// Created by Rajarshi on 19/4/24.
//
#include <string>
#include <vector>
#include "tokens.h"
#include <optional>

#pragma once


class Scanner {
public:
    explicit Scanner(std::string &&_source) : source(std::move(_source)) {}

    explicit Scanner(const std::string &_source) : source(_source) {}

    std::vector<Token> scanTokens() noexcept;

private:
    [[nodiscard]] bool isAtEnd() const noexcept;

    void scanToken() noexcept;

    /**
     * Returns the next character by consuming it.
     * Assume that the current pointer is not at end.
     * @return - the next character in source.
     */
    char advance() noexcept;

    /**
     * @return - Whether the next character in source, if present, matches the expected character.
     */
    bool match(char c) noexcept;

    /**
     * Returns the next character without consuming it. It implements a lookahead of 1.
     * Assume that the current pointer is not at end.
     * @return - the next character in source.
     */
    char peek() noexcept;
    char peekNext() noexcept;

    void string() noexcept;

    void addToken(TokenType, Literal&& literal = std::monostate{}) noexcept;

    void number() noexcept;


private:
    std::string source;
    int start{0};
    int current{0};
    int line{1};
    std::vector<Token> scanned_tokens;

};