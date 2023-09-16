#include "headers/processor.h"
#include "headers/lexer.h"

int main(int length, char** args){
    /*simpletron::intro();

    simpletron::Processor processor;
    processor.load();
    processor.run();*/

    simpletron::assembler::Lexer lexer("LD 43");
    while(lexer.hasNext()){
        simpletron::utils::Result<simpletron::assembler::Token>* init = lexer.nextToken();
        if(init->isError()){
            std::cout<<init->getMessage();
        }else{
            std::cout<<init->unwrap()<<std::endl;
        }
    }
    return 0;
}