#ifndef PARSER
	#define PARSER

#include <iostream>
#include <string>
#include <vector>
#include <variant>
#include <map>

#include "utils.h"
#include "lexer.h"
#include "parser.h"

namespace simpletron::assembler{
    enum ExpressionType{ OpcodeExpression, BranchExpression,  SubroutineExpression, NoneExpression };
    
    struct BranchValue{
        int nemode;
        std::string address;
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
            ExpressionType getType(){
                return this->exType;
            }
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
                return new Expression(ExpressionType::OpcodeExpression, value);
            }
            static Expression* Branch(int nemode, std::string address){
                BranchValue init;
                init.nemode = nemode;
                init.address = address;

                return new Expression(ExpressionType::BranchExpression, init);
            }
            static Expression* Subroutine(std::string value){
                return new Expression(ExpressionType::SubroutineExpression, value);
            }
            static Expression* None(){
                return new Expression(ExpressionType::NoneExpression, nullptr);
            }
            friend std::ostream& operator<<(std::ostream& os, const Expression* exp){
                std::string name = "";
                switch(exp->exType){
                    case ExpressionType::OpcodeExpression:
                        name = "Opcode";
                        break;
                    case ExpressionType::BranchExpression:
                        name = "Branch";
                        break;
                    case ExpressionType::SubroutineExpression:
                        name = "SubroutineExpression";
                        break;
                    case ExpressionType::NoneExpression:
                        name = "None";
                        break;
                }

                std::string value = "";
                if (std::holds_alternative<std::string>(exp->value)) {
                    value = std::get<std::string>(exp->value);
                }else if (std::holds_alternative<int>(exp->value)) {
                    value = std::to_string(std::get<int>(exp->value));
                }else if (std::holds_alternative<BranchValue>(exp->value)) {
                    BranchValue init = std::get<BranchValue>(exp->value);
                    value = "nemode:" + std::to_string(init.nemode) + ", address:" + init.address;
                }
                os << "Expression:" << name << "(" << value << ")" ;
                return os;
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
            bool hasNext();
            Expression* getNext();
    };
}

#endif