#ifndef UTILS
	#define UTILS

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>

namespace simpletron::utils{
    class Character{
        private:
            char value;
        public:
            Character(char value){ this->value = value; }
            bool isAlphabetic();
            bool isNumeric();
            bool isAlphanumeric(){ return this->isAlphabetic() || this->isNumeric(); }
            bool isHexdigit();
            bool isWhitespace();
            char unwrap(){ return this->value; }
    };

    template <typename T> class Result{
        private:
            T value;
            std::string message;
            Result(T value, std::string message){
                this->value = value;
                this->message = message;
            }
        public:
            bool isError(){
                return this->message.length() > 0;
            }
            T unwrap(){ return this->value; }
            std::string getMessage(){ return this->message; }
            static Result<T>* Ok(T value){ return new Result<T>(value, ""); }
            static Result<T>* Error(std::string message){ return new Result<T>(nullptr, message ); }
    };

    std::string hex(int value);
    std::string stringToUpper(std::string s);
    bool is_nemonic(std::string name);
    Result<std::string>* readFile(std::string path);
}

#endif