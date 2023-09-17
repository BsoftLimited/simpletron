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
        Subroutine init = {0};
        init.name = sub;
        init.exps = codes;

        codes.clear();
        this->subroutines.push_back(init);
    }
}

/*std::vector<int> run(){

}*/