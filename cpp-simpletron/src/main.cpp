#include "headers/processor.h"
#include "headers/assembler.h"

int main(int length, char** args){
    simpletron::intro();

    simpletron::utils::Result<std::string>* file = simpletron::utils::readFile("./test.asm");
    if(file->isError()){
        std::cout<<file->getMessage()<<std::endl;
    }else{
        std::string content = file->unwrap();
        
        simpletron::assembler::Assembler* assembler = new simpletron::assembler::Assembler();
        assembler->init(content);

        std::vector<int> init = assembler->run();
        for(int code: init){
            std::cout<<code<<std::endl;
        }
    }

    return 0;
}