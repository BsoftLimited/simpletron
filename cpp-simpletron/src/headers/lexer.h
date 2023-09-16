#ifndef LEXER
	#define LEXER

#include <iostream>
#include <string>

#include "utils.h"

namespace simpletron::assembler{
    enum TokenType{ Name = 0, Number, Colon, TokenNone };

    class Token{
        private:
            TokenType ttype;
            std::string value;
        public:
            Token(TokenType ttype, std::string value){
                this->ttype = ttype;
                this->value = value;
            }
            std::string getValue(){ return this->value; }
            TokenType getType(){ return this->ttype; }
            friend std::ostream& operator<<(std::ostream& os, const Token& token){
                std::string name = "";
                switch(token.ttype){
                    case TokenType::Name:
                        name = "Name";
                        break;
                    case TokenType::Number:
                        name = "Number";
                        break;
                    case TokenType::Colon:
                        name = "Colon";
                        break;
                }
                os << "Token:" << name << "(" << token.value << ")" ;
                return os;
            }
            friend std::ostream& operator<<(std::ostream& os, const Token* token){
                std::string name = "";
                switch(token->ttype){
                    case TokenType::Name:
                        name = "Name";
                        break;
                    case TokenType::Number:
                        name = "Number";
                        break;
                    case TokenType::Colon:
                        name = "Colon";
                        break;
                }
                os << "Token:" << name << "(" << token->value << ")" ;
                return os;
            }
    };

    class Lexer{
        private:
            int index;
            utils::Character* current;
            std::string data;
            bool to_newline;
            simpletron::utils::Result<Token>* getNameToken();
            simpletron::utils::Result<Token>* getNumberToken();
        public:
            Lexer(std::string data);
            char pop();
            bool hasNext();
            simpletron::utils::Result<Token>* nextToken();
    };
}

#endif