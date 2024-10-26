//
// Created by Rajarshi on 19/4/24.
//
#include <cassert>
#include <optional>
#include "scanner.h"
#include "errors.h"

static bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

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

        case '"':
            string();
            break;

        case '\n':
            line++;
            break;

        default:
            if (isDigit(c)) {
                number();
            } else if (isAlpha(c)) {
                identifier();
            } else {
                error_handling::error(line, "Unexpected character.");
            }
    }
}

std::vector<Token> Scanner::scanTokens() noexcept {
    while (!isAtEnd()) {
        // We are at the beginning of the next lexeme.
        start = current;
        scanToken();
    }

    addToken(TokenType::LOX_EOF);
    return scanned_tokens;
}


bool Scanner::isAtEnd() const noexcept {
    return current >= source.size();
}

char Scanner::advance() noexcept {
    assert(!isAtEnd());

    return source[current++];
}

void Scanner::addToken(TokenType token_type, Literal &&literal) noexcept {
    std::string lexeme = source.substr(start, current - start);
    scanned_tokens.emplace_back(token_type, lexeme, std::forward<Literal>(literal), line);
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

char Scanner::peekNext() noexcept {
    if (current + 1 >= source.size()) return '\0';
    return source[current + 1];
}

void Scanner::string() noexcept {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') line++;
        advance();
    }

    if (isAtEnd()) {
        error_handling::error(line, "Unterminated string.");
        return;
    }

    // The closing ".
    advance();

    // Trim the surrounding quotes.
    addToken(
            TokenType::STRING,
            source.substr(start + 1, current - start - 1)
    );
}

void Scanner::number() noexcept {
    while (isDigit(peek())) advance();

    // Look for a fractional part.
    if (peek() == '.' && isDigit(peekNext())) {
        // Consume the "."
        advance();

        while (isDigit(peek())) advance();
    }

    addToken(TokenType::NUMBER,
             stod(source.substr(start, current - start + 1)));
}

bool Scanner::isAlpha(char c) noexcept {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           c == '_';
}

void Scanner::identifier() noexcept {
    while (isAlpha(peek()) || isDigit(peek())) advance();

    std::string text = source.substr(start, current - start);
    auto it = KEYWORD_LIST.find(text);
    if (it != KEYWORD_LIST.end()) {
        addToken(it->second);
        return;
    }

    addToken(TokenType::IDENTIFIER, std::move(text));
}

