#ifndef PARSE_H
#define PARSE_H
#include<deque>
#include"./token.h"
#include"./value.h"
class Parser {
    std::deque<TokenPtr> tokens;

public:
    Parser(std::deque<TokenPtr> tokens):tokens(std::move(tokens)) {};
    ValuePtr parse();
    ValuePtr parseTails();
};
#endif
