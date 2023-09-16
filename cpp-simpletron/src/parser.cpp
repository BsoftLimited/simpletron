#include "headers/parser.h"

using namespace simpletron::assembler;
using namespace simpletron::utils;

Parser::Parser(std::string data){
    this->lexer = new Lexer(data);
    this->errors = {};
    this->current = new Token(TokenType::TokenNone, "");
}

bool Parser::nextToken(){
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
    this->nextToken();
    return init;
}

Expression* Parser::initOpcode(int opcode){
    this->nextToken();
    if(this->current->getType() == TokenType::Number){
        int value =  std::stoi(this->current->getValue());
        return Expression::Opcode(opcode + value);
    }else{
        this->errors.push_back("expected a number, instead " + this->current->getValue() + " was provided");
    }
    return Expression::None();
}

Expression* Parser::initBranch(int opcode){
    this->nextToken();
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
        this->nextToken();
    }
    return Expression::None();
}

Expression* Parser::getNext(){
    while(this->current->getType() != TokenType::TokenNone){
        if(this->current->getType() == TokenType::Name){
            std::string name = stringToUpper(this->current->getValue());
            if(name.compare("RD")){
                return this->initOpcode(1000);
            }else if(name.compare("WR")){
                return this->initOpcode(1100);
            }else if(name.compare("LD")){
                return this->initOpcode(2000);
            }else if(name.compare("STR")){
                return this->initOpcode(2100);
            }else if(name.compare("ADD")){
                return this->initOpcode(3000);
            }else if(name.compare("SUB")){
                return this->initOpcode(3100);
            }else if(name.compare("DIV")){
                return this->initOpcode(3200);
            }else if(name.compare("MUL")){
                return this->initOpcode(3300);
            }else if(name.compare("BR")){
                return this->initOpcode(4000);
            }else if(name.compare("BRN")){
                return this->initOpcode(4100);
            }else if(name.compare("BRZ")){
                return this->initOpcode(4200);
            }else if(name.compare("HLT")){
                return this->initOpcode(4300);
            }
            return this->initSubroutine();
        }
        Token* token = this->popToken();
        this->errors.push_back("Unexpected token: " + token->getValue());
    }
    return Expression::None();
}