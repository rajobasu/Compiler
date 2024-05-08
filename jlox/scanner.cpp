//
// Created by Rajarshi on 19/4/24.
//
#include <cassert>
#include "scanner.h"
#include "errors.h"


void Scanner::scanToken() noexcept {
    char c = advance();
    switch (c) {
        case '(':
            addToken(TokenType::LEFT_PAREN);
            break;
        case ')':
            addToken(TokenType::RIGHT_PAREN);
            break;
        case '{':
            addToken(TokenType::LEFT_BRACE);
            break;
        case '}':
            addToken(TokenType::RIGHT_BRACE);
            break;
        case ',':
            addToken(TokenType::COMMA);
            break;
        case '.':
            addToken(TokenType::DOT);
            break;
        case '-':
            addToken(TokenType::MINUS);
            break;
        case '+':
            addToken(TokenType::PLUS);
            break;
        case ';':
            addToken(TokenType::SEMICOLON);
            break;
        case '*':
            addToken(TokenType::STAR);
            break;
        case '!':
            addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
            break;
        case '=':
            addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
            break;
        case '<':
            addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
            break;
        case '>':
            addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
            break;
        case '/':
            if (match('/')) {
                // A comment goes until the end of the line.
                while (peek() != '\n' && !isAtEnd()) advance();
            } else {
                addToken(TokenType::SLASH);
            }
            break;
            
        case ' ':
        case '\r':
        case '\t':
            // Ignore whitespace.
            break;

        case '\n':
            line++;
            break;

        default:
            error(line, "Unexpected token.");
    }
}

std::vector<Token> Scanner::scanTokens() noexcept {
    return {};
}


bool Scanner::isAtEnd() const noexcept {
    return current >= source.size();
}

char Scanner::advance() noexcept {
    assert(!isAtEnd());

    return source[current++];
}

void Scanner::addToken(TokenType token_type) noexcept {
    std::string lexeme = source.substr(start, current - start);
    scanned_tokens.emplace_back(token_type, lexeme, line);
}

bool Scanner::match(char expected) noexcept {
    if (isAtEnd()) return false;
    if (expected != source[current]) return false;

    current++;
    return true;
}

char Scanner::peek() noexcept {
    assert(!isAtEnd());

    return source[current];
}
