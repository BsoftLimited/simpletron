#include "headers/parser.h"

using namespace simpletron::assembler;

Parser::Parser(std::string data){
    this->lexer = new Lexer(data);
    this->errors = {};
    this->current = new Token(TokenType::TokenNone, "");
}

bool Parser::nextToken(){
    while(this->lexer->hasNext()){
        simpletron::utils::Result<simpletron::assembler::Token>* init = this->lexer->nextToken();
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

}

Expression* Parser::initBranch(int opcode){
    
}

Expression* Parser::initSubroutine(){

}

Expression* Parser::getNext(){
    while(this->current->getType() != TokenType::TokenNone){
        if(this->current->getType() == TokenType::Name){
            std::string name = this->current->getValue().;
                match name.to_uppercase().as_str(){
                    "RD"   => return self.init_opcode(1000),
                    "WR"   => return self.init_opcode(1100),

                    "LD"   => return self.init_opcode(2000),
                    "STR"  => return self.init_opcode(2100),

                    "ADD"  => return self.init_opcode(3000),
                    "SUB"  => return self.init_opcode(3100),
                    "DIV"  => return self.init_opcode(3200),
                    "MUL"  => return self.init_opcode(3300),

                    "BR"   => return self.init_branch(4000),
                    "BRN"  => return self.init_branch(4100),
                    "BRZ"  => return self.init_branch(4200),
                    "HLT"  => return Expression::Opcode(4300),

                    _ => return self.init_subroutine(),
                }
            }
            let token = self.pop_token();
            self.errors.push(format!("Unexpected token: {:?}", token));
        }
        return Expression::None;
}