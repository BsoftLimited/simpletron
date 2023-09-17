#include "headers/processor.h"
#include "headers/parser.h"

int main(int length, char** args){
    /*simpletron::intro();

    simpletron::Processor processor;
    processor.load();
    processor.run();*/

    simpletron::assembler::Parser* parser = new simpletron::assembler::Parser("start: LD 43 RD 12 main: BRN start");
    while(parser->hasNext()){
        simpletron::assembler::Expression* init = parser->getNext();
        
        std::cout<<init<<std::endl;
    }

    return 0;
}