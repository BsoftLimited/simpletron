#include "headers/assembler.h"

using namespace simpletron::utils;
using namespace simpletron::assembler;

bool Assembler::init(std::string data){
    this->subroutines.clear();
    Parser* parser = new Parser(data);

    std::string sub = "";
    std::vector<Expression> codes = {};
    while(parser->hasNext()){
        Result<Expression*>* result = parser->getNext();
        if(!result->isError()){
            Expression* init = result->unwrap();
            if(init->getType() == ExpressionType::SubroutineExpression){
                this->insert(sub, codes);
                sub = init->getString();
                codes.clear();
            }else{
                codes.push_back(*init);
            }
        }else{
            std::cout<<result->getMessage()<<std::endl;
            return false;
        }
    }
    this->insert(sub, codes);
    return true;
}

void Assembler::insert(std::string sub, std::vector<Expression> codes){
    if(sub.length() > 0 && codes.size() > 0){
        Subroutine init = {};
        init.name = sub;
        init.exps = codes;

        this->subroutines.push_back(init);
    }else if(this->subroutines.empty() && codes.size() > 0){
        Subroutine init = {};
        init.name = "_start";
        init.exps = codes;

        this->subroutines.push_back(init);
    }
}

std::vector<int> Assembler::run(){
    std::vector<int> codes = {};
    std::map<std::string, int> addresses = {};

    int current = 0000;
    for(Subroutine subroutine: this->subroutines){
        addresses[subroutine.name] = current;
        
        current += subroutine.exps.size();
    }

    for(Subroutine subroutine: this->subroutines){
        for(Expression exp: subroutine.exps){
            if(exp.getType() == ExpressionType::OpcodeExpression){
                codes.push_back(exp.getInt());
            }else if(exp.getType() == ExpressionType::BranchExpression){
                BranchValue value = exp.getBranDetails();

                int init = value.nemode + addresses[value.address];
                codes.push_back(init);
            }
        }
    }
    return codes;
}