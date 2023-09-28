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

    template <typename T> struct ResultValue{
        T value;
        std::string message;
    };

    template <typename T> class Result{
        private:
            ResultValue<T> value;
            Result(ResultValue<T> value){
                this->value = value;
            }
        public:
            bool isError(){
                return this->value.message.length() > 0;
            }
            T unwrap(){ return this->value.value; }
            std::string getMessage(){ return this->value.message; }
            static Result<T>* Ok(T value){
                ResultValue<T> init;
                init.value = value;
                return new Result<T>(init);
            }
            static Result<T>* Error(std::string message){
                ResultValue<T> init;
                init.message = message;
                return new Result<T>(init); 
            }
    };

    std::string hex(int value);
    std::string stringToUpper(std::string s);
    bool is_nemonic(std::string name);
    Result<std::string>* readFile(std::string path);
    std::string format(int value, int count);
}

#endif