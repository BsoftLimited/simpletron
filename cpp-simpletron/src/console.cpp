#include "headers/console.h"

std::string combine(std::vector<std::string> inputs){
    std::string init = "";
    for(std::string datum : inputs){
        init += " " + datum;
    }
    return init;
}

void simpletron::intro(){
   std::cout<<"*** Welcome to Simpletron! ***"<<std::endl;
   std::cout<<"*** Please enter your program one instruction ***"<<std::endl;
   std::cout<<"*** (or data word) at a time. I will type the ***"<<std::endl;
   std::cout<<"*** location number and a question mark (?).  ***"<<std::endl;
   std::cout<<"*** You then type the word for that location. ***"<<std::endl;
   std::cout<<"*** Type the end to stop inputing code***"<<std::endl;
   std::cout<<"*** your program. ***"<<std::endl;
}

void simpletron::info(){
   std::cout<<"*** Welcome to Simpletron! ***"<<std::endl;
   std::cout<<"To run:"<<std::endl;
   std::cout<<"\tSingletron --help or -h: to display help options"<<std::endl;
   std::cout<<"\tSingletron file: to run from a file"<<std::endl;
   std::cout<<"\tSingletron --version or -v: to display version"<<std::endl;
   std::cout<<"\tSingletron: to input singletron commands manually"<<std::endl;
}

void simpletron::version(){
    std::cout<<"Simpletron version 0.1.0"<<std::endl;
}

simpletron::Console::Console(){
    this->processor = new simpletron::Processor();
    bool is_shell = IS_SHELL;
    system(is_shell ? "cls" : "clear");
}

void simpletron::Console::load(std::string data){
    simpletron::utils::Result<std::string>* file = simpletron::utils::readFile(data);
    if(file->isError()){
        std::cout<<file->getMessage()<<std::endl;
    }else{
        std::string content = file->unwrap();
        
        simpletron::assembler::Assembler* assembler = new simpletron::assembler::Assembler();
        assembler->init(content);

        this->processor->add(assembler->run());
        printf("*** Program loading completed ***\n");
    }
}

void simpletron::Console::read(){
    simpletron::assembler::Assembler assembler;
    std::vector<std::string> inputs;

    std::string input;
    while (input != "end"){
        std::cout<<"address "<<simpletron::utils::format(inputs.size(), 4)<<": >> ";
        std::getline(std::cin, input);
        if(input != "end"){
            std::string temp_data = combine(inputs) + " " + input;
            if(assembler.init(temp_data)){
                inputs.push_back(input);
            }
        }
    }

    if(input.length() > 0){
        this->processor->add(assembler.run());
        printf("*** Program loading completed ***\n");
    }
}

void simpletron::Console::run(){
   printf("\n\n*** Program execution begins  ***\n");
   this->processor->run();   
}