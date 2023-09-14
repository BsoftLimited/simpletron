#ifndef PARSER
	#define PARSER

#include <iostream>
#include <string>

#include "utils.h"
#include "lexer.h"
#include "parser.h"

namespace simpletron::assembler{
    std::string NEMONICS[] = [ 
        "RD", "WR", "LD", "STR", "ADD", "SUB", "DIV", "MUL", "BR", "BRN", "BRZ", "HLT"
    ];

    bool is_nemonic(std::string name){
        for(int i = 0; i < NEMONICS.length(); i++){
            if(NEMONICS[i] == name){
                return true;
            }
        }
        return false;
    }

    enum ExpressionType{ Opcode, Branch,  Subroutine, None }
    struct BranchValue{
        int nemode; std::string address
    }

    template <typename T> class Expression{
        Opcode(u16), Branch{ nemode: u16, address: String},  Subroutine{ name :String}, None
        private:
            Expression(ExpressionType exType, T* value);
        public:
            static Expression<int>* Opcode(int value){
                return new Expression<int>(ExpressionType::Opcode, value);
            }
            static Expression<BranchValue>* Opcode(int nemode, std::string address){
                return new Expression<BranchValue>(ExpressionType::Branch, {nemode, address });
            }
            static Expression<std::string>* Subroutine(std::string value){
                return new Expression<std::string>(ExpressionType::Subroutine, value);
            }
    }

    class Parser{
        private:
            simpletron::assembler::Lexer* lexer;
            std::string errors[];
            simpletron::assembler::Token* current;
    };
}

#endif