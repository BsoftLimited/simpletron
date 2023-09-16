#include "headers/lexer.h"

using namespace simpletron::assembler;
using namespace simpletron::utils;

Lexer::Lexer(std::string data){
    this->data = data;
}

char Lexer::pop(){
    char init = this->data[this->index];
    this->index += 1;
    return init;
}

bool Lexer::hasNext(){
    while(this->index < this->data.length()){
        this->current = new utils::Character(this->data[this->index]);
        if(this->to_newline && this->current->unwrap() == '\n'){
            this->to_newline = false;
        }else if(!this->to_newline && !this->current->isWhitespace()){
            return true; 
        }
        this->index += 1;
    }
    return false;
}

Result<Token>* Lexer::getNameToken(){
    std::string builder = "";
    while(this->index < this->data.length()){
        this->current = new Character(this->data[this->index]);
        bool passable = !this->current->isAlphanumeric();
        if(passable){
            break;
        }else {
            builder += this->current->unwrap();
        }
        this->index += 1;
    }
    return Result<Token>::Ok(new Token(TokenType::Name, builder));
}

Result<Token>* Lexer::getNumberToken(){
    std::string builder = "";
    while(this->index < this->data.length()){
        this->current = new Character(this->data[this->index]);
        bool important = !this->current->isWhitespace() && this->current->isHexdigit();
        if(important){
            builder += this->current->unwrap();
        }else{
            break;
        };
        this->index += 1;
    }
    return Result<Token>::Ok(new Token(TokenType::Number, builder));
}

Result<Token>* Lexer::nextToken(){
    if(this->current->isAlphabetic()){
        return this->getNameToken();
    }else if(this->current->isNumeric()){
        return this->getNumberToken();
    }else if(this->current->unwrap() == ':'){
        this->pop();
        return Result<Token>::Ok(new Token(TokenType::Colon, ":"));
    }
    std::string s(1, this->pop());
    return Result<Token>::Error("unexpected token {" + s + "} encountered");
}