#include "headers/assembler.h"

using namespace simpletron::assembler;

void Assembler::init(std::string data){
    Parser* parser = new Parser(data);

    std::string sub = "";
    std::vector<Expression> codes = {};
    while(parser->hasNext()){
        Expression* init = parser->getNext();
        if(init->getType() == ExpressionType::SubroutineExpression){
            this->insert(sub, codes);
            sub = init->getString();
            codes.clear();
        }else{
            codes.push_back(*init);
        }
    }
    this->insert(sub, codes);
}

void Assembler::insert(std::string sub, std::vector<Expression> codes){
    if(sub.length() > 0 && codes.size() > 0){
        Subroutine init = {};
        init.name = sub;
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