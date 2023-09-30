#include "headers/console.h"

int main(int length, char** args){
    simpletron::Console console;
    if(length > 1){
        std::string command = args[1];
        if(command == "-h" || command == "--help"){
            simpletron::info();
        }else if(command == "-v" || command == "--version"){
            simpletron::version();
        }else if(args[1][0] == '-'){
            std::cout<<"unrecognized command or flag: "<<command<<std::endl;
        }else{
            console.load(args[1]);
        }
    }else{
        simpletron::intro();
        console.read();
    }

    return 0;
}