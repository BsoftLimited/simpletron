#ifndef PARSER
	#define PARSER

#include <iostream>
#include <string>
#include <vector>
#include <variant>

#include "utils.h"
#include "lexer.h"
#include "parser.h"

namespace simpletron::assembler{
    std::string NEMONICS[12] = {
        "RD", "WR", "LD", "STR", "ADD", "SUB", "DIV", "MUL", "BR", "BRN", "BRZ", "HLT"
    };

    enum ExpressionType{ Opcode, Branch,  Subroutine, ExpressionNone };
    
    struct BranchValue{
        int nemode;
        std::string address;
    };

    bool is_nemonic(std::string name){
        for(int i = 0; i < sizeof(NEMONICS); i++){
            if(NEMONICS[i] == name){
                return true;
            }
        }
        return false;
    };

    class Expression{
        private:
            ExpressionType exType;
            std::variant<int, std::string, BranchValue> value;
            Expression(ExpressionType exType, std::variant<int, std::string, BranchValue> value){
                this->exType = exType;
                this->value = value;
            }
        public:
            int getInt(){
                return std::get<int>(this->value);
            }
            std::string getString(){
                return std::get<std::string>(this->value);
            }
            BranchValue getBranDetails(){
                return std::get<BranchValue>(this->value);
            }
            static Expression* Opcode(int value){
                return new Expression(ExpressionType::Opcode, value);
            }
            static Expression* Opcode(int nemode, std::string address){
                BranchValue init;
                init.nemode = nemode;
                init.address = address;

                return new Expression(ExpressionType::Branch, init);
            }
            static Expression* Subroutine(std::string value){
                return new Expression(ExpressionType::Subroutine, value);
            }
            static Expression* None(){
                return new Expression(ExpressionType::ExpressionNone, nullptr);
            }
    };

    class Parser{
        private:
            simpletron::assembler::Lexer* lexer;
            std::vector<std::string> errors;
            simpletron::assembler::Token* current;
            simpletron::assembler::Token* popToken();
            Expression* initOpcode(int opcode);
            Expression* initBranch(int opcode);
            Expression* initSubroutine();
        public:
            Parser(std::string data);
            bool nextToken();
            Expression* getNext();
    };
}

#endif