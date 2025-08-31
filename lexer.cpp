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

  
    // Numbers
    if (isdigit(c)) {
        std::string num(1, c);
        while (isdigit(peek())) num += get();

        if (peek() == '.') {
            num += get();
            while (isdigit(peek())) num += get();
        }
        return makeToken(TokenType::T_NUMBER, num);
    }

    // Strings
    if (c == '"') {
        std::string str;
        while (peek() != '"' && peek() != '\0')
            str += get();
        get(); // closing "
        return makeToken(TokenType::T_STRING_LITERAL, str);
    }

    // Chars
    if (c == '\'') {
        char val = get();
        get(); // closing '
        return makeToken(TokenType::T_CHAR_LITERAL, std::string(1, val));
    }

    // Operators / symbols
    switch (c) {
        case '+': return makeToken(TokenType::T_PLUS, "+");
        case '-': return makeToken(TokenType::T_MINUS, "-");
        case '*': return makeToken(TokenType::T_STAR, "*");
        case '/': return makeToken(TokenType::T_SLASH, "/");
        case '=': return (peek() == '=') ? (get(), makeToken(TokenType::T_EQ, "=="))
                                         : makeToken(TokenType::T_ASSIGN, "=");
        case '!': return (peek() == '=') ? (get(), makeToken(TokenType::T_NEQ, "!="))
                                         : makeToken(TokenType::T_NOT, "!");
        case '<': return (peek() == '=') ? (get(), makeToken(TokenType::T_LTE, "<="))
                                         : makeToken(TokenType::T_LT, "<");
        case '>': return (peek() == '=') ? (get(), makeToken(TokenType::T_GTE, ">="))
                                         : makeToken(TokenType::T_GT, ">");
        case '&': if (peek() == '&') { get(); return makeToken(TokenType::T_AND, "&&"); } break;
        case '|': if (peek() == '|') { get(); return makeToken(TokenType::T_OR, "||"); } break;
        case '(': return makeToken(TokenType::T_LPAREN, "(");
        case ')': return makeToken(TokenType::T_RPAREN, ")");
        case '{': return makeToken(TokenType::T_LBRACE, "{");
        case '}': return makeToken(TokenType::T_RBRACE, "}");
        case ';': return makeToken(TokenType::T_SEMI, ";");
        case ',': return makeToken(TokenType::T_COMMA, ",");
    }

    return makeToken(TokenType::T_UNKNOWN, std::string(1, c));
}