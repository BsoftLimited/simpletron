#include "headers/processor.h"
#include "headers/assembler.h"

int main(int length, char** args){
    if(length > 1){
        std::string command = args[1];
        if(command == "-h" || command == "--help"){
            simpletron::info();
        }else if(command == "-v" || command == "--version"){
            simpletron::version();
        }else if(args[1][0] == '-'){
            std::cout<<"unrecognized command or flag: "<<command<<std::endl;
        }
    }else{
        simpletron::intro();
    }
    /*

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
    }*/

    return 0;
}