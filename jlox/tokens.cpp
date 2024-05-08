//
// Created by Rajarshi on 19/4/24.
//

#include "tokens.h"


std::ostream& operator<<(std::ostream& out, const TokenType& token_type) {
    switch (token_type) {
        case TokenType::LEFT_PAREN: return out << "(";
        case TokenType::RIGHT_PAREN:return out << ")";
        case TokenType::LEFT_BRACE:return out << "{";
        case TokenType::RIGHT_BRACE:return out << "}";
        case TokenType::COMMA:return out << ",";
        case TokenType::DOT:return out << ".";
        case TokenType::MINUS:return out << "-";
        case TokenType::PLUS:return out << "+";
        case TokenType::SEMICOLON:return out << ";";
        case TokenType::SLASH:return out << "/";
        case TokenType::STAR:return out << "*";
        case TokenType::BANG:return out << "!";
        case TokenType::BANG_EQUAL:return out << "!=";
        case TokenType::EQUAL:return out << "=";
        case TokenType::EQUAL_EQUAL:return out << "==";
        case TokenType::GREATER:return out << ">";
        case TokenType::GREATER_EQUAL:return out << ">=";
        case TokenType::LESS:return out << "<";
        case TokenType::LESS_EQUAL:return out << "<=";
        case TokenType::IDENTIFIER:return out << "ID";
        case TokenType::STRING:return out << "STR";
        case TokenType::NUMBER:return out << "NUM";
        case TokenType::AND:return out << "AND";
        case TokenType::CLASS:return out << "CLASS";
        case TokenType::ELSE:return out << "ELSE";
        case TokenType::FALSE:return out << "FALSE";
        case TokenType::FUN:return out << "FUN";
        case TokenType::FOR:return out << "FOR";
        case TokenType::IF:return out << "IF";
        case TokenType::NIL:return out << "NIL";
        case TokenType::OR:return out << "OR";
        case TokenType::PRINT:return out << "PRINT";
        case TokenType::RETURN:return out << "RETURN";
        case TokenType::SUPER:return out << "SUPER";
        case TokenType::THIS:return out << "THIS";
        case TokenType::TRUE:return out << "TRUE";
        case TokenType::VAR:return out << "VAR";
        case TokenType::WHILE:return out << "WHILE";
        case TokenType::LOX_EOF:return out << "EOF";
        default: return out << "_UNKOWN_";
    }
}

std::ostream& operator<<(std::ostream& out, const Token& token) {
    return out << token.token_type << "|" << token.lexeme << "|" << token.line_number;
}