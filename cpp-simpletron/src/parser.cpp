#include "headers/parser.h"

using namespace simpletron::assembler;
using namespace simpletron::utils;

Parser::Parser(std::string data){
    this->lexer = new Lexer(data);
    this->errors = {};
    this->current = new Token(TokenType::TokenNone, "");
}

bool Parser::hasNext(){
    while(this->lexer->hasNext()){
        Result<Token>* init = this->lexer->nextToken();
        if(init->isError()){
            this->errors.push_back(init->getMessage());
        }else{
            this->current = init->unwrap();
            return true;
        }
    }
    this->current = new Token(TokenType::TokenNone, "");
    return false;
}

simpletron::assembler::Token* Parser::popToken(){
    Token* init = this->current;
    this->hasNext();
    return init;
}

Expression* Parser::initOpcode(int opcode){
    this->hasNext();
    if(this->current->getType() == TokenType::Number){
        int value =  std::stoi(this->current->getValue());
        return Expression::Opcode(opcode + value);
    }else{
        this->errors.push_back("expected a number, instead " + this->current->getValue() + " was provided");
    }
    return Expression::None();
}

Expression* Parser::initBranch(int opcode){
    this->hasNext();
    if(this->current->getType() == TokenType::Name){
        std::string name = this->current->getValue();
        if(!is_nemonic(name)){
            return Expression::Branch(opcode, name);
        }
    }
    return Expression::None();
}

Expression* Parser::initSubroutine(){
    std::string name = "";
    while(this->current->getType() != TokenType::TokenNone){
        if(this->current->getType() == TokenType::Name){
            name = this->current->getValue();
        }else if(this->current->getType() == TokenType::Colon){
            return Expression::Subroutine(name);
        }
        this->hasNext();
    }
    return Expression::None();
}

Expression* Parser::getNext(){
    while(this->current->getType() != TokenType::TokenNone){
        if(this->current->getType() == TokenType::Name){
            std::string name = stringToUpper(this->current->getValue());
            if(name == "RD"){
                return this->initOpcode(1000);
            }else if(name == "WR"){
                return this->initOpcode(1100);
            }else if(name == "LD"){
                return this->initOpcode(2000);
            }else if(name == "STR"){
                return this->initOpcode(2100);
            }else if(name == "ADD"){
                return this->initOpcode(3000);
            }else if(name == "SUB"){
                return this->initOpcode(3100);
            }else if(name == "DIV"){
                return this->initOpcode(3200);
            }else if(name == "MUL"){
                return this->initOpcode(3300);
            }else if(name == "BR"){
                return this->initBranch(4000);
            }else if(name == "BRN"){
                return this->initBranch(4100);
            }else if(name == "BRZ"){
                return this->initBranch(4200);
            }else if(name == "HLT"){
                return this->initBranch(4300);
            }
            return this->initSubroutine();
        }
        Token* token = this->popToken();
        this->errors.push_back("Unexpected token: " + token->getValue());
    }
    return Expression::None();
}