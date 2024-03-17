#include"./parse.h"
#include"./error.h"
ValuePtr Parser::parseTails() {
    if (tokens.size() == 0) {
        throw SyntaxError("Uncomplete");
    };
    if (tokens[0]->getType() == TokenType::RIGHT_PAREN) {
        return std::make_shared<NilValue>();
    }
    auto car = this->parse();
    tokens.pop_front();
    if (tokens[0]->getType() == TokenType::DOT) {
        tokens.pop_front();
        auto cdr = this->parse();
        tokens.pop_back();
        return std::make_shared<PairValue>(car, cdr);
    } 
        auto cdr = this->parseTails();
        return std::make_shared<PairValue>(car, cdr);
}
ValuePtr Parser::parse(){
        if (tokens.size() == 0) throw false;
    auto &token = tokens[0];
    if (token->getType() == TokenType::NUMERIC_LITERAL) {
        auto value = static_cast<NumericLiteralToken &>(*token).getValue();
        return std::make_shared<NumericValue>(value);
    }
    else if (token->getType() == TokenType::BOOLEAN_LITERAL) {
        auto value = static_cast<BooleanLiteralToken &>(*token).getValue();
        return std::make_shared<BooleanValue>(value);
    }
    else if (token->getType() == TokenType::STRING_LITERAL) {
        auto value = static_cast<StringLiteralToken &>(*token).getValue();
        return std::make_shared<StringValue>(value);
    }  
    else if (token->getType() == TokenType::IDENTIFIER) {
        auto value = static_cast<IdentifierToken &>(*token).getName();
        return std::make_shared<SymbolValue>(value);
    }
    else if (token->getType() == TokenType::LEFT_PAREN) {
        tokens.pop_front();
        return this->parseTails();
    }
    else if (token->getType() == TokenType::QUOTE) {
        tokens.pop_front();
        return std::make_shared<PairValue>(
            std::make_shared<SymbolValue>("quote"),
            std::make_shared<PairValue>(this->parse(),
                                        std::make_shared<NilValue>()));
    } 
    else if (token->getType() == TokenType::QUASIQUOTE) {
        tokens.pop_front();
        return std::make_shared<PairValue>(
            std::make_shared<SymbolValue>("quasiquote"),
            std::make_shared<PairValue>(this->parse(),
                                        std::make_shared<NilValue>()));
    } 
    else if (token->getType() == TokenType::UNQUOTE) {
        tokens.pop_front();
        return std::make_shared<PairValue>(
            std::make_shared<SymbolValue>("unquote"),
            std::make_shared<PairValue>(this->parse(),
                                        std::make_shared<NilValue>()));
    }
        else
            throw SyntaxError("Unimplemented");
    
}
