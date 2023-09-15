#ifndef LEXER
	#define LEXER

#include <iostream>
#include <string>

#include "utils.h"

namespace simpletron::assembler{
    enum TokenType{ Name, Number, Colon, TokenNone};

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