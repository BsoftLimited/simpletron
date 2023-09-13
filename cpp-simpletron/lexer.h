#ifndef LEXER
	#define LEXER

#include <iostream>
#include <string>

#include "utils.h";
namespace simpletron::assembler{
    enum TokenType{ Name, Number, Colon, None}

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
    };

    class Lexer{
        private:
            int index;
            utils::Character current;
            std::string data;
            bool to_newline;
            Token getNameToken();
            Token getNumberToken();
        public:
            Lexer(std::string data);
            char pop();
            bool hasNext();
            Token nextToken();
    };
}

#endif