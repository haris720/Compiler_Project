#include "lexer.h"
#include <cctype>

Lexer::Lexer(const std::string& src) : source(src), pos(0) {}

char Lexer::peek() {
    return pos < source.size() ? source[pos] : '\0';
}

char Lexer::get() {
    return pos < source.size() ? source[pos++] : '\0';
}

void Lexer::skipWhitespace() {
    while (isspace(peek())) get();
}

// Skip both single-line and multi-line comments
void Lexer::skipComments() {
    while (peek() == '/' && pos + 1 < source.size() &&
          (source[pos + 1] == '/' || source[pos + 1] == '*')) {
        if (source[pos + 1] == '/') {
            get(); get(); // skip //
        } else if (source[pos + 1] == '*') {
            get(); get(); // skip /*
        }
        skipWhitespace();
    }
}

Token Lexer::makeToken(TokenType type, const std::string& value) {
    return Token{type, value};
}

Token Lexer::nextToken() {
    skipWhitespace();
    skipComments();

    char c = get();
    if (c == '\0') return makeToken(TokenType::T_EOF);

    // Identifiers / keywords
    if (isalpha(c) || c == '_') {
        std::string id(1, c);
        while (isalnum(peek()) || peek() == '_')
            id += get();

        if (id == "int") return makeToken(TokenType::T_INT, id);
        if (id == "float") return makeToken(TokenType::T_FLOAT, id);
        if (id == "bool") return makeToken(TokenType::T_BOOL, id);
        if (id == "char") return makeToken(TokenType::T_CHAR, id);
        if (id == "string") return makeToken(TokenType::T_STRING, id);
        if (id == "if") return makeToken(TokenType::T_IF, id);
        if (id == "else") return makeToken(TokenType::T_ELSE, id);
        if (id == "while") return makeToken(TokenType::T_WHILE, id);
        if (id == "for") return makeToken(TokenType::T_FOR, id);
        if (id == "return") return makeToken(TokenType::T_RETURN, id);
        if (id == "fn") return makeToken(TokenType::T_IDENTIFIER, "fn");

        return makeToken(TokenType::T_IDENTIFIER, id);
    }