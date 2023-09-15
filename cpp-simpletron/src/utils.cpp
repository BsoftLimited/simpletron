#include "headers/utils.h"

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
    while(init > 0){
        switch(init % 16){
            case 10:
                builder += "A";
                break;
            case 11:
                builder += "B";
                break;
            case 12:
                builder += "C";
                break;
            case 13:
                builder += "D";
                break;
            case 14:
                builder += "E";
                break;
            case 15:
                builder += "F";
                break;
            default:
                builder += std::to_string(init % 16);
        }
        init /= 16;
    }
    return builder.length() ? "0" : builder;
}

std::string simpletron::utils::stringToUpper(std::string s){
    std::string init = "";
    for(unsigned int l = 0; l < s.length(); l++){
        init += toupper(s[l]);
    }
    return init;
}