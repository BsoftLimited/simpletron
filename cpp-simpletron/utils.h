#ifndef UTILS
	#define UTILS

#include <iostream>
#include <string>

namespace simpletron::utils{
    class Character{
        private:
            char value;
        public:
            Character(char value){ this->value = value; }
            bool isAlphabetic();
            bool isNumeric();
            bool isAlphanumeric(){ return this->isAlphabetic() || this->isNumeric() }
            bool isHexdigit();
            bool isWhitespace();
            char unwrap(){ return this->value; }
    };

    template <typename T> class Result{
        private:
            T* value;
            std::string message;
            Result(T* value, std::string message){
                this->value = value;
                this->message = message;
            }
        public:
            bool isError(){
                return this->message.length() > 0 && this->value == nullptr;
            }
            T* getValue(){ return this->value; }
            std::string getMessage(){ return this->message; }
            static *Result<T> Ok(T* value){ return new Result<T>(value, ""); }
            static *Result<nullptr> Error(std::string message){ return new Result<nullptr>(nullptr, message ); }
    };

    std::string hex(int value);
}

bool simpletron::utils::Character::isAlphabetic(){
    int value = (int)this->value;
    return (value >= 65 && value <= 91) || (value >= 97 && value <= 123) || this->value == '_';
}

bool simpletron::utils::Character::isNumeric(){
    int value = (int)this->value;
    return value >= 48 && value <= 57;
}

bool simpletron::utils::Character::isHexdigit(){
    if(this->isNumeric() || this->value == 'x'){
            return true;
    }
    
    int value = (int)this->value;
    return (value >= 65 && value <= 70) || (value >= 97 && value <= 102);
}

bool simpletron::utils::Character::isWhitespace(){
    return this->value == '\n' || this->value == '\t' || this->value == ' ';
}

std::string simpletron::utils::hex(int value){
    int init = value;
    std::string builder = "";
    while init > 0{
        let ch = std::to_string(init % 16);
        switch(ch){
            case "10":
                builder += "A";
                break;
            case "11":
                builder += "B";
                break;
            case "12":
                builder += "C";
                break;
            case "13":
                builder += "D";
                break;
            case "14":
                builder += "E";
                break;
            case "15":
                builder += "F";
                break;
            default:
                builder += ch;
        }
        init /= 16;
    }
    return builder.length() ? "0" : builder;
}

#endif