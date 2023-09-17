#include "headers/processor.h"
#include "headers/assembler.h"

int main(int length, char** args){
    /*simpletron::intro();

    simpletron::Processor processor;
    processor.load();
    processor.run();*/

    /*simpletron::assembler::Parser* parser = new simpletron::assembler::Parser("start: LD 43 BRZ main RD 12 main: STR 32 BRN start");
    while(parser->hasNext()){
        simpletron::assembler::Expression* init = parser->getNext();
        
        std::cout<<init<<std::endl;
    }*/

    /*simpletron::assembler::Lexer* lexer = new simpletron::assembler::Lexer("start: LD 43 BRZ main RD 12 main: STR 32 BRN start");
    while(lexer->hasNext()){
        simpletron::utils::Result<simpletron::assembler::Token>* init = lexer->nextToken();
        if(init->isError()){
            std::cout<<init->getMessage()<<std::endl;
        }else{
            std::cout<<init->unwrap()<<std::endl;
        }
    }*/

    simpletron::assembler::Assembler* assembler = new simpletron::assembler::Assembler();
    assembler->init("start: LD 43 BRZ main RD 12 main: STR 32 BRN start");

    std::vector<int> init = assembler->run();
    for(int code: init){
        std::cout<<code<<std::endl;
    }

    return 0;
}