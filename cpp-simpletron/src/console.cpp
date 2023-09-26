#include "headers/console.h"

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
}

void simpletron::Console::load(std::string data){

}

void simpletron::Console::read(){
    while (inp != -9999){
        std::cout<<n<<std::endl;
        std::cin>>inp;
        this->memory[n] = inp;
        ++n;
    }
    printf("*** Program loading completed ***\n");
    printf("*** Program execution begins  ***\n");
}

void simpletron::Console::run(){
    
}