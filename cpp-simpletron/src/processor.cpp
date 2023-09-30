#include "headers/processor.h"

using namespace simpletron::utils;

simpletron::Processor::Processor(){
    this->clear();
}

void simpletron::Processor::add(std::vector<int> codes){
    for(int i = 0; i < codes.length(); i++){
        this->memory[this->memory->length() + i] = codes[i];
    }
}

void simpletron::Processor::clear(){
    for(int i = 0; i < SIZE; i++){
        this->memory[i] = 0;
    }

    this->accumulator = 0;
    this->instructionCounter = 0;
    this->instructionRegister = 0;
    this->operationCode = 0;
    this->operand = 0;
}

void simpletron::Processor::run(){
    this->instructionCounter = 0;
    // Run infinte loop through the instructions
    while(this->instructionCounter < this->memory->length()){   
        // get current instruction
        this->instructionRegister = this->memory[this->instructionCounter];
        if(this->instructionRegister == 9999){
            break;
        }

        // get opcode and this->operand
        this->operationCode = (this->instructionRegister) / 100;
        this->operand = (this->instructionRegister) % 100;
        
        switch (this->operationCode){
            case simpletron::Operands::READ:
                std::cout<<"Enter an input to be stored at mempry address "<<format(this->operand, 2)<<"? ";
                std::cin>>this->memory[ this->operand ];
                std::cout<<std::endl;

                std::cout<<"address "<<format(this->instructionCounter, 2)<<":"<<this->instructionRegister<<" >> "<<this->memory[ this->operand ]<<" loaded into memory address: "<<this->operand<<std::endl;
                ++this->instructionCounter;
                break;
            
            case simpletron::Operands::WRITE:
                std::cout<<"address "<<format(this->instructionCounter, 2)<<":"<<this->instructionRegister<<" >> "<<this->memory[ this->operand ]<<" from memory address: "<<this->operand<<std::endl;
                ++this->instructionCounter;
                break;
            
            case simpletron::Operands::LOAD:
                std::cout<<"address "<<format(this->instructionCounter, 2)<<":"<<this->instructionRegister<<" >> "<<"Loaded "<<this->memory[ this->operand ]<<" into the accumulator."<<std::endl;
                this->accumulator = this->memory[ this->operand ];
                ++this->instructionCounter;
                break;
            
            case simpletron::Operands::STORE:
                std::cout<<"address "<<format(this->instructionCounter, 2)<<":"<<this->instructionRegister<<" >> "<<"Copied "<<this->accumulator<<">>>> from the accumulator into memory address "<<this->operand<<std::endl;
                this->memory[ this->operand ] = this->accumulator;
                ++this->instructionCounter;
                break;
            
            case simpletron::Operands::ADD:
                std::cout<<"address "<<format(this->instructionCounter, 2)<<":"<<this->instructionRegister<<" >> "<<"Add "<<this->memory[ this->operand ]<<" to the acummulator's value: "<<this->accumulator<<std::endl;                
                this->accumulator += this->memory[ this->operand ];
                ++this->instructionCounter;
                break;
            
            case simpletron::Operands::SUBSTRACT:
                std::cout<<"address "<<format(this->instructionCounter, 2)<<":"<<this->instructionRegister<<" >> "<<"Substract "<<this->memory[ this->operand ]<<" from the acummulator's value: "<<this->accumulator<<std::endl;                             
                this->accumulator -= this->memory[ this->operand ];
                ++this->instructionCounter;
                break;

            case simpletron::Operands::DIVIDE:
                std::cout<<"address "<<format(this->instructionCounter, 2)<<":"<<this->instructionRegister<<" >> "<<"Divide the acummulator's value: "<<this->accumulator<<" with "<<this->memory[ this->operand ]<<std::endl; 
                this->accumulator /= this->memory[ this->operand ];
                ++this->instructionCounter;
                break;

            case simpletron::Operands::MULTIPLY:
                std::cout<<"address "<<format(this->instructionCounter, 2)<<":"<<this->instructionRegister<<" >> "<<"Multiply the accumulator's value: "<<this->accumulator<<" with "<<this->memory[ this->operand ]<<std::endl;
                this->accumulator *= this->memory[ this->operand ];
                ++this->instructionCounter;
                break;
            
            case simpletron::Operands::BRANCH:
                std::cout<<"address "<<format(this->instructionCounter, 2)<<":"<<this->instructionRegister<<" >> "<<"Performed Jump to: "<<this->operand<<std::endl;
                this->instructionCounter = this->operand;
                break;
            
            case simpletron::Operands::BRANCHNEG:
                if (this->accumulator < 0 )
                    this->instructionCounter = this->operand;
                break;
            
            case simpletron::Operands::BRANCHZERO:
                if (this->accumulator == 0)
                    this->instructionCounter = this->operand;
                break;

            default:
                std::cout<<this->operationCode<<" incorrect instruction "<<std::endl;
                break;
            
        }
    }
}