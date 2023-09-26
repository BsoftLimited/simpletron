#include "headers/processor.h"

simpletron::Processor::Processor(){
    this->clear();
}

void simpletron::Processor::add(std::vector<int> codes){
    for(int code: codes){
        this->memory[this->address] = code;
        this->address += 1;
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
    this->address = 0;
}

void simpletron::Processor::run(){
    this->instructionCounter = 0;
    // Run infinte loop through the instructions
    for(int i = 0; i < this->address; i++){   
        // get current instruction
        this->instructionRegister = this->memory[this->instructionCounter];

        // get opcode and this->operand
        this->operationCode = this->instructionRegister / 100;
        this->operand = this->instructionRegister % 100;
        
        switch (this->operationCode){
            case simpletron::Operands::READ:
                std::cout<<"? "<<std::endl;
                std::cin>>this->memory[ this->operand ];
                std::cout<<this->memory[ this->operand ]<<" loaded into memory address: "<<this->operand<<std::endl;
                ++this->instructionCounter;
                break;
            
            case simpletron::Operands::WRITE:
                std::cout<<"? "<<this->memory[ this->operand ]<<" from memory address: "<<this->operand<<std::endl;
                ++this->instructionCounter;
                break;
            
            case simpletron::Operands::LOAD:
                std::cout<<"Loaded "<<this->memory[ this->operand ]<<" into the accumulator."<<std::endl;
                this->accumulator = this->memory[ this->operand ];
                ++this->instructionCounter;
                break;
            
            case simpletron::Operands::STORE:
                std::cout<<"Copied "<<this->accumulator<<">>>> from the accumulator into memory address "<<this->operand<<std::endl;
                this->memory[ this->operand ] = this->accumulator;
                ++this->instructionCounter;
                break;
            
            case simpletron::Operands::ADD:
                std::cout<<"Add "<<this->memory[ this->operand ]<<" to the acummulator's value: "<<this->accumulator<<std::endl;                
                this->accumulator += this->memory[ this->operand ];
                ++this->instructionCounter;
                break;
            
            case simpletron::Operands::SUBSTRACT:
                std::cout<<"Substract "<<this->memory[ this->operand ]<<" from the acummulator's value: "<<this->accumulator<<std::endl;                             
                this->accumulator -= this->memory[ this->operand ];
                ++this->instructionCounter;
                break;

            case simpletron::Operands::DIVIDE:
                std::cout<<"Divide the acummulator's value: "<<this->accumulator<<" with "<<this->memory[ this->operand ]<<std::endl; 
                this->accumulator /= this->memory[ this->operand ];
                ++this->instructionCounter;
                break;

            case simpletron::Operands::MULTIPLY:
                std::cout<<"Multiply the accumulator's value: "<<this->accumulator<<" with "<<this->memory[ this->operand ]<<std::endl;
                this->accumulator *= this->memory[ this->operand ];
                ++this->instructionCounter;
                break;
            
            case simpletron::Operands::BRANCH:
                std::cout<<"Performed Jump to: "<<this->operand<<std::endl;
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
                //std::cout<<"%d Incorrect instruction \n", this->operationCode);
                break;
            
        }
    }
}