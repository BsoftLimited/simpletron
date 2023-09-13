#ifndef UTILS
	#define UTILS

#include <iostream>

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

#endif